#include "SQR_TDGameState.h"

ATDGameState::ATDGameState()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ATDGameState::BeginPlay()
{
	Super::BeginPlay();
}

void ATDGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME(ATDGameState, CurrentWave);
	DOREPLIFETIME(ATDGameState, AliveEnemies);
	DOREPLIFETIME(ATDGameState, MaxConcurrentEnemies);
	DOREPLIFETIME(ATDGameState, WaveTimeRemaining);
	DOREPLIFETIME(ATDGameState, IntermissionTimeRemaining);
	DOREPLIFETIME(ATDGameState, PlayersReadyCount);
	DOREPLIFETIME(ATDGameState, TotalPlayers);
	DOREPLIFETIME(ATDGameState, TeamLives);
}

void ATDGameState::OnRep_CurrentWave()
{
	OnWaveStarted.Broadcast(CurrentWave);
}

void ATDGameState::OnRep_AliveEnemies()
{
	OnAliveEnemiesChanged.Broadcast(AliveEnemies);
}

void ATDGameState::OnRep_TeamLives()
{
	OnTeamLivesChanged.Broadcast(TeamLives);
}

void ATDGameState::SetCurrentWave(int32 NewWave)
{
	if (HasAuthority())
	{
		CurrentWave = NewWave;
		OnRep_CurrentWave();
	}
}

void ATDGameState::SetAliveEnemies(int32 NewCount)
{
	if (HasAuthority())
	{
		AliveEnemies = NewCount;
		OnRep_AliveEnemies();
	}
}

void ATDGameState::SetTeamLives(int32 NewLives)
{
	if (HasAuthority())
	{
		TeamLives = NewLives;
		OnRep_TeamLives();
	}
}

void ATDGameState::UpdatePlayersReadyCount()
{
	if (HasAuthority())
	{
		PlayersReadyCount = 0;
		TotalPlayers = PlayerArray.Num();
		
		// Count ready players (implementation depends on PlayerState)
		for (APlayerState* Player : PlayerArray)
		{
			// Check if player is ready
			// PlayersReadyCount++;
		}
	}
}
