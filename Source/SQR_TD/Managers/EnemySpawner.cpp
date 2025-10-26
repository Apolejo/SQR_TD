#include "EnemySpawner.h"
#include "SQR_TD/Data/DA_Enemy.h"
#include "SQR_TD/Managers/WaveManager.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "Engine/Engine.h"
#include "EngineUtils.h"

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

	bPausedByCap = bPaused;
	
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
}

void ATDEnemySpawner::StopSpawning()
{
	if (!HasAuthority())
	{
		return;
	}

	GetWorld()->GetTimerManager().ClearTimer(SpawnTimerHandle);
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

	AActor* SpawnedEnemy = GetWorld()->SpawnActor<AActor>(EnemyClass, SpawnPoint.GetLocation(), SpawnPoint.GetRotation().Rotator(), SpawnParams);
	
	if (SpawnedEnemy)
	{
		// Bind to destruction event
		SpawnedEnemy->OnDestroyed.AddDynamic(this, &ATDEnemySpawner::OnEnemyDestroyed);
		
		// Notify wave manager
		if (WaveManager)
		{
			WaveManager->OnEnemySpawned();
		}
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
		int32 TokensGranted = WaveManager->TryGrantTokens(RemainingInBurst);
		if (TokensGranted > 0)
		{
			SetPaused(false);
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
