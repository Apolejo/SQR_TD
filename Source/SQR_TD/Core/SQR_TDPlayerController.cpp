#include "SQR_TDPlayerController.h"
#include "SQR_TD/Core/ATDPlayerState.h"
#include "SQR_TD/Core/ATDGameMode.h"
#include "SQR_TD/Core/ATDGameState.h"

ATDPlayerController::ATDPlayerController()
{
	PrimaryActorTick.bCanEverTick = false;
	
	// Create BuildSystem component
	BuildSystem = CreateDefaultSubobject<UBuildSystemComponent>(TEXT("BuildSystem"));
}

void ATDPlayerController::BeginPlay()
{
	Super::BeginPlay();
}

void ATDPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	// Setup input bindings here
}

void ATDPlayerController::Server_RequestBuildTower_Implementation(const FTowerBuildSpec& TowerSpec)
{
	// Validate request
	if (!CanAffordTower(TowerSpec.Cost))
	{
		Client_ShowError(FText::FromString(TEXT("Not enough gold!")));
		return;
	}

	if (!IsValidBuildLocation(TowerSpec.Location))
	{
		Client_ShowError(FText::FromString(TEXT("Invalid build location!")));
		return;
	}

	// Get GameMode for validation
	if (ATDGameMode* GameMode = Cast<ATDGameMode>(GetWorld()->GetAuthGameMode()))
	{
		FBuildRequest BuildRequest;
		BuildRequest.Location = TowerSpec.Location;
		BuildRequest.Rotation = TowerSpec.Rotation;
		BuildRequest.TowerClass = TowerSpec.TowerClass;
		BuildRequest.Cost = TowerSpec.Cost;

		if (!GameMode->ValidateBuild(BuildRequest))
		{
			Client_ShowError(FText::FromString(TEXT("Build validation failed!")));
			return;
		}
	}

	// Deduct gold
	if (ATDPlayerState* PlayerState = Cast<ATDPlayerState>(GetPlayerState()))
	{
		if (PlayerState->SpendGold(TowerSpec.Cost))
		{
			// Spawn tower
			// Implementation depends on tower spawning system
			UE_LOG(LogTemp, Warning, TEXT("Tower build request approved"));
		}
	}
}

void ATDPlayerController::Server_RequestUpgradeTower_Implementation(AActor* Tower)
{
	// Validate upgrade request
	if (!Tower)
	{
		Client_ShowError(FText::FromString(TEXT("Invalid tower!")));
		return;
	}

	// Check if player can afford upgrade
	// Implementation depends on upgrade system
	UE_LOG(LogTemp, Warning, TEXT("Tower upgrade request received"));
}

void ATDPlayerController::Server_RequestSellTower_Implementation(AActor* Tower)
{
	// Validate sell request
	if (!Tower)
	{
		Client_ShowError(FText::FromString(TEXT("Invalid tower!")));
		return;
	}

	// Refund gold and destroy tower
	// Implementation depends on tower system
	UE_LOG(LogTemp, Warning, TEXT("Tower sell request received"));
}

void ATDPlayerController::Server_SetPlayerReady_Implementation(bool bReady)
{
	// Update player ready state
	// Implementation depends on ready system
	UE_LOG(LogTemp, Warning, TEXT("Player ready state: %s"), bReady ? TEXT("True") : TEXT("False"));
}

void ATDPlayerController::Client_ShowError_Implementation(const FText& ErrorMessage)
{
	// Show error message to player
	UE_LOG(LogTemp, Warning, TEXT("Error: %s"), *ErrorMessage.ToString());
}

void ATDPlayerController::Client_PlayPing_Implementation(const FVector& PingLocation)
{
	// Play ping effect at location
	UE_LOG(LogTemp, Warning, TEXT("Ping at location: %s"), *PingLocation.ToString());
}

bool ATDPlayerController::CanAffordTower(int32 Cost) const
{
	if (ATDPlayerState* PlayerState = Cast<ATDPlayerState>(GetPlayerState()))
	{
		return PlayerState->Gold >= Cost;
	}
	return false;
}

bool ATDPlayerController::IsValidBuildLocation(const FVector& Location) const
{
	// Basic validation - check if location is within bounds
	// More complex validation would check for overlaps, terrain, etc.
	return true;
}
