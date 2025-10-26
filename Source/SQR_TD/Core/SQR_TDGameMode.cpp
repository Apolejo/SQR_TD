#include "SQR_TDGameMode.h"
#include "SQR_TD/Managers/WaveManager.h"
#include "SQR_TDPlayerState.h"
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
	
	// Give starting gold to all players
	if (AGameState* GS = GetGameState<AGameState>())
	{
		for (APlayerState* Player : GS->PlayerArray)
		{
			ApplyGoldToPlayer(Player, StartingGoldPerPlayer);
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
	AWaveManager* WaveManager = FindObject<AWaveManager>(GetWorld(), TEXT("WaveManager"));
	if (WaveManager)
	{
		// Call WaveManager's start wave method
		// WaveManager->StartNextWave();
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
