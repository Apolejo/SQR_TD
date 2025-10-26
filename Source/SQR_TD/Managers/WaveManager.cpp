#include "WaveManager.h"
#include "SQR_TD/Data/DA_Wave.h"
#include "SQR_TD/Core/SQR_TDGameState.h"
#include "SQR_TD/Managers/EnemySpawner.h"
#include "Engine/World.h"
#include "TimerManager.h"

ATDWaveManager::ATDWaveManager()
{
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;
}

void ATDWaveManager::BeginPlay()
{
	Super::BeginPlay();
	
	// Initialize with first wave
	InitWave(0);
}

void ATDWaveManager::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME(ATDWaveManager, CurrentWaveIndex);
	DOREPLIFETIME(ATDWaveManager, AliveEnemies);
	DOREPLIFETIME(ATDWaveManager, MaxConcurrentEnemies);
	DOREPLIFETIME(ATDWaveManager, AvailableTokens);
	DOREPLIFETIME(ATDWaveManager, bWaveRunning);
	DOREPLIFETIME(ATDWaveManager, WaveBudgetRemaining);
}

void ATDWaveManager::InitWave(int32 WaveIndex)
{
	if (!HasAuthority())
	{
		return;
	}

	CurrentWaveIndex = WaveIndex;
	AliveEnemies = 0;
	AvailableTokens = MaxConcurrentEnemies;
	WaveBudgetRemaining = 100; // Default budget
	bWaveRunning = false;

	// Scale for player count
	if (AGameStateBase* GS = GetWorld()->GetGameState())
	{
		int32 PlayerCount = GS->PlayerArray.Num();
		MaxConcurrentEnemies = ScaleForPlayers(50, PlayerCount);
		WaveBudgetRemaining = ScaleForPlayers(100, PlayerCount);
	}

	UpdateGameState();
	
	// Broadcast wave initialized event
	OnWaveInitialized(CurrentWaveIndex);
}

void ATDWaveManager::StartWave()
{
	if (!HasAuthority() || bWaveRunning)
	{
		return;
	}

	bWaveRunning = true;
	AvailableTokens = MaxConcurrentEnemies;
	WaveBudgetRemaining = ScaleForPlayers(100, GetWorld()->GetGameState()->PlayerArray.Num());

	// Distribute spawn groups to spawners
	DistributeSpawnGroups();

	// Start wave timer (default 60 seconds)
	GetWorld()->GetTimerManager().SetTimer(WaveTimerHandle, this, &ATDWaveManager::OnWaveTimerExpired, 60.0f, false);

	UpdateGameState();
	
	// Broadcast wave started event
	OnWaveStarted(CurrentWaveIndex);
}

void ATDWaveManager::PauseSpawning()
{
	if (!HasAuthority())
	{
		return;
	}

	// Pause all spawners
	for (ATDEnemySpawner* Spawner : SpawnerRefs)
	{
		if (Spawner)
		{
			Spawner->SetPaused(true);
		}
	}
	
	// Broadcast wave paused event
	OnWavePaused(CurrentWaveIndex);
}

void ATDWaveManager::ResumeSpawning()
{
	if (!HasAuthority())
	{
		return;
	}

	// Resume all spawners
	for (ATDEnemySpawner* Spawner : SpawnerRefs)
	{
		if (Spawner)
		{
			Spawner->SetPaused(false);
		}
	}
	
	// Broadcast wave resumed event
	OnWaveResumed(CurrentWaveIndex);
}

int32 ATDWaveManager::TryGrantTokens(int32 Requested)
{
	if (!HasAuthority())
	{
		return 0;
	}

	int32 Granted = FMath::Min(Requested, AvailableTokens);
	AvailableTokens -= Granted;
	
	// Broadcast token events
	if (Granted > 0)
	{
		OnTokensGranted(Granted, AvailableTokens);
	}
	else
	{
		OnTokensExhausted();
	}
	
	return Granted;
}

void ATDWaveManager::OnEnemySpawned()
{
	if (!HasAuthority())
	{
		return;
	}

	AliveEnemies++;
	UpdateGameState();
	
	// Broadcast enemy spawned event
	OnEnemySpawnedGlobal(AliveEnemies);
}

void ATDWaveManager::OnEnemyGone()
{
	if (!HasAuthority())
	{
		return;
	}

	AliveEnemies = FMath::Max(0, AliveEnemies - 1);
	AvailableTokens = FMath::Min(MaxConcurrentEnemies, AvailableTokens + 1);
	UpdateGameState();
	
	// Broadcast enemy destroyed event
	OnEnemyDestroyedGlobal(AliveEnemies);
}

void ATDWaveManager::OnGroupFinished(ATDEnemySpawner* Spawner)
{
	if (!HasAuthority())
	{
		return;
	}

	// Check if all spawners are finished
	bool bAllFinished = true;
	for (ATDEnemySpawner* SpawnerRef : SpawnerRefs)
	{
		if (SpawnerRef && !SpawnerRef->IsGroupFinished())
		{
			bAllFinished = false;
			break;
		}
	}

	if (bAllFinished && AliveEnemies == 0)
	{
		// Broadcast all spawners finished event
		OnAllSpawnersFinished(CurrentWaveIndex);
		EndWave();
	}
}

void ATDWaveManager::EndWave()
{
	if (!HasAuthority())
	{
		return;
	}

	bWaveRunning = false;
	GetWorld()->GetTimerManager().ClearTimer(WaveTimerHandle);

	// Start intermission timer
	GetWorld()->GetTimerManager().SetTimer(IntermissionTimerHandle, this, &ATDWaveManager::OnIntermissionTimerExpired, IntermissionDuration, false);

	UpdateGameState();
	
	// Broadcast wave ended and intermission started events
	OnWaveEnded(CurrentWaveIndex);
	OnIntermissionStarted(IntermissionDuration);
}

int32 ATDWaveManager::ScaleForPlayers(int32 Base, int32 Players)
{
	if (PlayerCountScalingCurve)
	{
		float ScaleFactor = PlayerCountScalingCurve->GetFloatValue(Players);
		return FMath::RoundToInt(Base * ScaleFactor);
	}
	
	// Default scaling: 1.0x for 1 player, 1.5x for 2 players, 2.0x for 3+ players
	float ScaleFactor = FMath::Clamp(1.0f + (Players - 1) * 0.5f, 1.0f, 2.0f);
	return FMath::RoundToInt(Base * ScaleFactor);
}

void ATDWaveManager::OnWaveTimerExpired()
{
	if (HasAuthority())
	{
		EndWave();
	}
}

void ATDWaveManager::OnIntermissionTimerExpired()
{
	if (HasAuthority())
	{
		// Start next wave
		InitWave(CurrentWaveIndex + 1);
		StartWave();
		
		// Broadcast intermission ended event
		OnIntermissionEnded(CurrentWaveIndex);
	}
}

void ATDWaveManager::UpdateGameState()
{
	if (ATDGameState* GS = Cast<ATDGameState>(GetWorld()->GetGameState()))
	{
		GS->SetCurrentWave(CurrentWaveIndex);
		GS->SetAliveEnemies(AliveEnemies);
	}
}

void ATDWaveManager::DistributeSpawnGroups()
{
	// This would distribute spawn groups from the current wave data to spawners
	// Implementation depends on how wave data is structured
	for (ATDEnemySpawner* Spawner : SpawnerRefs)
	{
		if (Spawner)
		{
			// Spawner->SetSpawnGroups(CurrentWaveSpawnGroups);
		}
	}
}
