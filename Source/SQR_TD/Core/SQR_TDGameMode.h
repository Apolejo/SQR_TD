#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SQR_TD/Core/TDStructures.h"
#include "SQR_TDGameMode.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEnemyReachedGoal, AActor*, Enemy);

/**
 * Main GameMode for Square Tower Defense
 * Server-only authority for match management and validation
 */
UCLASS()
class SQR_TD_API ATDGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ATDGameMode();

protected:
	virtual void BeginPlay() override;

public:
	// Match state
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Match Settings")
	bool bMatchActive;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Match Settings")
	bool bLoseOnLivesZero = true;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Match Settings")
	int32 StartingGoldPerPlayer = 100;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Match Settings")
	int32 TeamLives = 20;

	// Events
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnEnemyReachedGoal OnEnemyReachedGoal;

	// Server-only methods
	UFUNCTION(BlueprintCallable, Category = "Match Management")
	void StartMatch();

	UFUNCTION(BlueprintCallable, Category = "Match Management")
	void EndMatch(bool bVictory);

	UFUNCTION(BlueprintCallable, Category = "Wave Management")
	void Server_StartNextWave();

	UFUNCTION(BlueprintCallable, Category = "Building")
	bool ValidateBuild(const FBuildRequest& BuildRequest);

	UFUNCTION(BlueprintCallable, Category = "Player Management")
	void ApplyGoldToPlayer(APlayerState* Player, int32 Amount);

	UFUNCTION(BlueprintCallable, Category = "Enemy Management")
	void OnEnemyReachedGoal(AActor* Enemy);
};
