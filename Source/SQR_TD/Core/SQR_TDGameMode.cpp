#include "SQR_TDGameMode.h"
#include "SQR_TD/Managers/WaveManager.h"
#include "SQR_TDPlayerState.h"
#include "SQR_TDGameState.h"
#include "GameFramework/GameState.h"

ATDGameMode::ATDGameMode()
{
	PrimaryActorTick.bCanEverTick = false;
	bMatchActive = false;
}

void ATDGameMode::BeginPlay()
{
	Super::BeginPlay();
}

void ATDGameMode::StartMatch()
{
	if (bMatchActive)
	{
		return;
	}

	bMatchActive = true;
	UE_LOG(LogTemp, Warning, TEXT("Match Started"));
	// Give starting gold to all players
	if (AGameStateBase* GS = GetGameState<AGameStateBase>())
	{
		for (APlayerState* Player : GS->PlayerArray)
		{
			ApplyGoldToPlayer(Player, StartingGoldPerPlayer);
			UE_LOG(LogTemp, Warning, TEXT("Gold Added to Player"));
		}
	}
}

void ATDGameMode::EndMatch(bool bVictory)
{
	if (!bMatchActive)
	{
		return;
	}

	bMatchActive = false;
	
	// Handle match end logic here
	UE_LOG(LogTemp, Warning, TEXT("Match ended. Victory: %s"), bVictory ? TEXT("True") : TEXT("False"));
}

void ATDGameMode::Server_StartNextWave()
{
	// Find and call WaveManager
	ATDWaveManager* WaveManager = FindObject<ATDWaveManager>(GetWorld(), TEXT("WaveManager"));
	if (WaveManager)
	{
		// Call WaveManager's start wave method
		WaveManager->StartWave();
	}
	else
	{
		// Spawn WaveManager if it doesn't exist
		WaveManager = GetWorld()->SpawnActor<ATDWaveManager>();
		if (WaveManager)
		{
			WaveManager->StartWave();
		}
	}
}

bool ATDGameMode::ValidateBuild(const FBuildRequest& BuildRequest)
{
	// Basic validation logic
	if (!BuildRequest.TowerClass)
	{
		return false;
	}

	// Check if location is valid (not overlapping with other towers)
	// Check if player has enough gold
	// Check if location is within buildable area
	
	return true;
}

void ATDGameMode::ApplyGoldToPlayer(APlayerState* Player, int32 Amount)
{
	if (ATDPlayerState* TDPlayerState = Cast<ATDPlayerState>(Player))
	{
		TDPlayerState->AddGold(Amount);
	}
}

void ATDGameMode::HandleEnemyReachedGoal(AActor* Enemy)
{
	if (bLoseOnLivesZero)
	{
		// Decrease team lives
		// Check if game should end
	}
	
	// Broadcast event
	OnEnemyReachedGoal.Broadcast(Enemy);
}
