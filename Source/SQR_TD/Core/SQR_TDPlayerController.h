#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SQR_TD/Core/TDStructures.h"
#include "SQR_TD/Building/BuildSystemComponent.h"
#include "SQR_TDPlayerController.generated.h"

/**
 * PlayerController for Square Tower Defense
 * Handles input and client-server communication
 */
UCLASS()
class SQR_TD_API ATDPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ATDPlayerController();

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

public:
	// Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UBuildSystemComponent* BuildSystem;

	// Server RPCs (Client -> Server)
	UFUNCTION(BlueprintCallable, Server, Reliable, Category = "Building")
	void Server_RequestBuildTower(const FTowerBuildSpec& TowerSpec);

	UFUNCTION(BlueprintCallable, Server, Reliable, Category = "Building")
	void Server_RequestUpgradeTower(AActor* Tower);

	UFUNCTION(BlueprintCallable, Server, Reliable, Category = "Building")
	void Server_RequestSellTower(AActor* Tower);

	UFUNCTION(BlueprintCallable, Server, Reliable, Category = "Player State")
	void Server_SetPlayerReady(bool bReady);

	// Client RPCs (Server -> Client)
	UFUNCTION(BlueprintCallable, Client, Reliable, Category = "UI")
	void Client_ShowError(const FText& ErrorMessage);

	UFUNCTION(BlueprintCallable, Client, Reliable, Category = "UI")
	void Client_PlayPing(const FVector& PingLocation);

	// Server-side validation
	UFUNCTION(BlueprintCallable, Category = "Building")
	bool CanAffordTower(int32 Cost) const;

	UFUNCTION(BlueprintCallable, Category = "Building")
	bool IsValidBuildLocation(const FVector& Location) const;
};
