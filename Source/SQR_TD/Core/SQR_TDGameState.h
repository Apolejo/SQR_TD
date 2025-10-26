#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "Net/UnrealNetwork.h"
#include "SQR_TDGameState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnWaveStarted, int32, WaveNumber);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnWaveEnded, int32, WaveNumber);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAliveEnemiesChanged, int32, NewCount);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTeamLivesChanged, int32, NewLives);

/**
 * Main GameState for Square Tower Defense
 * Replicates shared state to all clients
 */
UCLASS()
class SQR_TD_API ATDGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	ATDGameState();

protected:
	virtual void BeginPlay() override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	// RepNotify functions
	UFUNCTION()
	void OnRep_CurrentWave();
	
	UFUNCTION()
	void OnRep_AliveEnemies();
	
	UFUNCTION()
	void OnRep_TeamLives();

public:
	// Replicated properties
	UPROPERTY(ReplicatedUsing = OnRep_CurrentWave, BlueprintReadOnly, Category = "Wave State")
	int32 CurrentWave = 0;

	UPROPERTY(ReplicatedUsing = OnRep_AliveEnemies, BlueprintReadOnly, Category = "Enemy State")
	int32 AliveEnemies = 0;

	UPROPERTY(Replicated, BlueprintReadOnly, Category = "Enemy State")
	int32 MaxConcurrentEnemies = 50;

	UPROPERTY(Replicated, BlueprintReadOnly, Category = "Wave State")
	float WaveTimeRemaining = 0.0f;

	UPROPERTY(Replicated, BlueprintReadOnly, Category = "Wave State")
	float IntermissionTimeRemaining = 0.0f;

	UPROPERTY(Replicated, BlueprintReadOnly, Category = "Player State")
	int32 PlayersReadyCount = 0;

	UPROPERTY(Replicated, BlueprintReadOnly, Category = "Player State")
	int32 TotalPlayers = 0;

	UPROPERTY(ReplicatedUsing = OnRep_TeamLives, BlueprintReadOnly, Category = "Team State")
	int32 TeamLives = 20;

	// Events
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnWaveStarted OnWaveStarted;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnWaveEnded OnWaveEnded;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnAliveEnemiesChanged OnAliveEnemiesChanged;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnTeamLivesChanged OnTeamLivesChanged;

	// Server-only methods
	UFUNCTION(BlueprintCallable, Category = "Wave Management")
	void SetCurrentWave(int32 NewWave);

	UFUNCTION(BlueprintCallable, Category = "Enemy Management")
	void SetAliveEnemies(int32 NewCount);

	UFUNCTION(BlueprintCallable, Category = "Team Management")
	void SetTeamLives(int32 NewLives);

	UFUNCTION(BlueprintCallable, Category = "Player Management")
	void UpdatePlayersReadyCount();
};
