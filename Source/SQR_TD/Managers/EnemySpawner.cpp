#include "EnemySpawner.h"
#include "SQR_TD/Data/DA_Enemy.h"
#include "SQR_TD/Managers/WaveManager.h"
#include "SQR_TD/Enemies/EnemyBase.h"
#include "Engine/World.h"
#include "EngineUtils.h"
#include "TimerManager.h"

ATDEnemySpawner::ATDEnemySpawner()
{
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;
}

void ATDEnemySpawner::BeginPlay()
{
	Super::BeginPlay();
	
	// Find wave manager
	if (HasAuthority())
	{
		// Try to find existing wave manager first
		for (TActorIterator<ATDWaveManager> ActorItr(GetWorld()); ActorItr; ++ActorItr)
		{
			WaveManager = *ActorItr;
			break;
		}
		
		// If not found, spawn one
		if (!WaveManager)
		{
			WaveManager = GetWorld()->SpawnActor<ATDWaveManager>();
		}
	}
}

void ATDEnemySpawner::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME(ATDEnemySpawner, LaneID);
	DOREPLIFETIME(ATDEnemySpawner, SpawnPoint);
	DOREPLIFETIME(ATDEnemySpawner, bPausedByCap);
	DOREPLIFETIME(ATDEnemySpawner, BurstSize);
	DOREPLIFETIME(ATDEnemySpawner, SpawnInterval);
}

void ATDEnemySpawner::SetSpawnGroups(const TArray<FSpawnGroup>& Groups)
{
	if (!HasAuthority())
	{
		return;
	}

	// Clear existing queue
	SpawnQueue.Empty();

	// Add new groups to queue
	SpawnQueue = Groups;

	// Start with first group
	CurrentGroupIndex = 0;
	if (SpawnQueue.Num() > 0)
	{
		CurrentGroup = SpawnQueue[0];
		RemainingInGroup = CurrentGroup.Count;
		RemainingInBurst = FMath::Min(CurrentGroup.BurstSize, RemainingInGroup);
	}
}

void ATDEnemySpawner::SetPaused(bool bPaused)
{
	if (!HasAuthority())
	{
		return;
	}

	bool bWasPaused = bPausedByCap;
	bPausedByCap = bPaused;
	
	// Broadcast pause/resume events
	if (bPaused && !bWasPaused)
	{
		OnSpawningPaused(LaneID);
	}
	else if (!bPaused && bWasPaused)
	{
		OnSpawningResumed(LaneID);
	}
	
	if (bPaused)
	{
		GetWorld()->GetTimerManager().PauseTimer(SpawnTimerHandle);
	}
	else
	{
		GetWorld()->GetTimerManager().UnPauseTimer(SpawnTimerHandle);
	}
}

bool ATDEnemySpawner::IsGroupFinished() const
{
	return RemainingInGroup <= 0 && CurrentGroupIndex >= SpawnQueue.Num() - 1;
}

void ATDEnemySpawner::StartSpawning()
{
	if (!HasAuthority() || bPausedByCap)
	{
		return;
	}

	// Start timer-driven spawning
	GetWorld()->GetTimerManager().SetTimer(SpawnTimerHandle, this, &ATDEnemySpawner::TickSpawn, SpawnInterval, true);
	
	// Broadcast spawning started event
	OnSpawningStarted(LaneID);
}

void ATDEnemySpawner::StopSpawning()
{
	if (!HasAuthority())
	{
		return;
	}

	GetWorld()->GetTimerManager().ClearTimer(SpawnTimerHandle);
	
	// Broadcast spawning stopped event
	OnSpawningStopped(LaneID);
}

void ATDEnemySpawner::TickSpawn()
{
	if (!HasAuthority() || bPausedByCap || IsGroupFinished())
	{
		return;
	}

	// Request tokens from wave manager
	if (WaveManager)
	{
		int32 TokensGranted = WaveManager->TryGrantTokens(RemainingInBurst);
		
		if (TokensGranted > 0)
		{
			// Spawn enemies
			for (int32 i = 0; i < TokensGranted && RemainingInGroup > 0; i++)
			{
				SpawnEnemy(CurrentGroup.EnemyClass);
				RemainingInGroup--;
				RemainingInBurst--;
			}

			// Check if burst is complete
			if (RemainingInBurst <= 0)
			{
				RemainingInBurst = FMath::Min(CurrentGroup.BurstSize, RemainingInGroup);
			}

			// Check if group is complete
			if (RemainingInGroup <= 0)
			{
				// Broadcast group finished event
				OnGroupFinished(CurrentGroupIndex, LaneID);
				
				// Move to next group
				CurrentGroupIndex++;
				if (CurrentGroupIndex < SpawnQueue.Num())
				{
					CurrentGroup = SpawnQueue[CurrentGroupIndex];
					RemainingInGroup = CurrentGroup.Count;
					RemainingInBurst = FMath::Min(CurrentGroup.BurstSize, RemainingInGroup);
				}
				else
				{
					// All groups finished
					OnAllGroupsFinished(LaneID);
					NotifyWaveManager();
					StopSpawning();
				}
			}
		}
		else
		{
			// No tokens available, pause spawning
			SetPaused(true);
		}
	}
}

void ATDEnemySpawner::SpawnEnemyGroup(const FSpawnGroup& Group)
{
	if (!HasAuthority())
	{
		return;
	}

	CurrentGroup = Group;
	RemainingInGroup = Group.Count;
	RemainingInBurst = FMath::Min(Group.BurstSize, RemainingInGroup);
	
	// Broadcast group started event
	OnGroupStarted(CurrentGroupIndex, LaneID);
	
	StartSpawning();
}

void ATDEnemySpawner::SpawnEnemy(TSubclassOf<AActor> EnemyClass)
{
	if (!HasAuthority() || !EnemyClass)
	{
		return;
	}

	// Spawn enemy at spawn point
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.Instigator = GetInstigator();
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	AEnemyBase* SpawnedEnemy = GetWorld()->SpawnActor<AEnemyBase>(AEnemyBase::StaticClass(), SpawnPoint.GetLocation(), SpawnPoint.GetRotation().Rotator(), SpawnParams);
	
	if (SpawnedEnemy)
	{
		// Set lane ID for the enemy
		SpawnedEnemy->SetLaneID(LaneID);
		
		// Bind to destruction event
		SpawnedEnemy->OnDestroyed.AddDynamic(this, &ATDEnemySpawner::OnEnemyDestroyed);
		
		// Notify wave manager
		if (WaveManager)
		{
			WaveManager->OnEnemySpawned();
		}
		
		// Broadcast enemy spawned event
		OnEnemySpawned(SpawnedEnemy, LaneID);
	}
}

void ATDEnemySpawner::OnEnemyDestroyed(AActor* DestroyedEnemy)
{
	if (!HasAuthority())
	{
		return;
	}

	// Notify wave manager
	if (WaveManager)
	{
		WaveManager->OnEnemyGone();
	}

	// Check if we can resume spawning
	if (bPausedByCap && WaveManager)
	{
		// Try to resume spawning
		SetPaused(false);
	}
}

void ATDEnemySpawner::RequestTokens()
{
	if (WaveManager && !bPausedByCap)
	{
		// Broadcast token request event
		OnTokenRequested(RemainingInBurst, LaneID);
		
		int32 TokensGranted = WaveManager->TryGrantTokens(RemainingInBurst);
		if (TokensGranted > 0)
		{
			// Broadcast tokens granted event
			OnTokensGranted(TokensGranted, LaneID);
			SetPaused(false);
		}
		else
		{
			// Broadcast tokens denied event
			OnTokensDenied(RemainingInBurst, LaneID);
		}
	}
}

void ATDEnemySpawner::NotifyWaveManager()
{
	if (WaveManager)
	{
		WaveManager->OnGroupFinished(this);
	}
}
