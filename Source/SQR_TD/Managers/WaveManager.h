#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Net/UnrealNetwork.h"
#include "Curves/CurveFloat.h"
#include "SQR_TD/Data/DA_Wave.h"
#include "SQR_TD/Core/TDSpawningStructures.h"
#include "WaveManager.generated.h"

class ATDEnemySpawner;
class ATDGameState;

/**
 * WaveManager - Server-authoritative wave management
 * Handles wave progression, timing, and enemy spawning coordination with token-bucket system
 */
UCLASS()
class SQR_TD_API ATDWaveManager : public AActor
{
	GENERATED_BODY()

public:
	ATDWaveManager();

protected:
	virtual void BeginPlay() override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
	// Wave data
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Wave Data")
	TArray<UDataAsset*> Waves;

	UPROPERTY(Replicated, BlueprintReadOnly, EditAnywhere, Category = "Wave State")
	int32 CurrentWaveIndex = 0;

	UPROPERTY(Replicated, BlueprintReadOnly, EditAnywhere, Category = "Enemy State")
	int32 AliveEnemies = 0;

	UPROPERTY(Replicated, BlueprintReadOnly, EditAnywhere, Category = "Enemy State")
	int32 MaxConcurrentEnemies = 50;

	UPROPERTY(Replicated, BlueprintReadOnly, EditAnywhere, Category = "Token System")
	int32 AvailableTokens = 0;

	UPROPERTY(Replicated, BlueprintReadOnly, EditAnywhere, Category = "Wave State")
	bool bWaveRunning = false;

	UPROPERTY(Replicated, BlueprintReadOnly, EditAnywhere, Category = "Wave State")
	int32 WaveBudgetRemaining = 0;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Wave Settings")
	float IntermissionDuration = 10.0f;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Scaling")
	UCurveFloat* PlayerCountScalingCurve = nullptr;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Spawners")
	TArray<TObjectPtr<ATDEnemySpawner>> SpawnerRefs;

	// Wave management methods
	UFUNCTION(BlueprintCallable, Category = "Wave Management")
	void InitWave(int32 WaveIndex);

	UFUNCTION(BlueprintCallable, Category = "Wave Management")
	void StartWave();

	UFUNCTION(BlueprintCallable, Category = "Wave Management")
	void PauseSpawning();

	UFUNCTION(BlueprintCallable, Category = "Wave Management")
	void ResumeSpawning();

	UFUNCTION(BlueprintCallable, Category = "Token System")
	int32 TryGrantTokens(int32 Requested);

	UFUNCTION(BlueprintCallable, Category = "Enemy Management")
	void OnEnemySpawned();

	UFUNCTION(BlueprintCallable, Category = "Enemy Management")
	void OnEnemyGone();

	UFUNCTION(BlueprintCallable, Category = "Spawner Management")
	void OnGroupFinished(ATDEnemySpawner* Spawner);

	UFUNCTION(BlueprintCallable, Category = "Wave Management")
	void EndWave();

	UFUNCTION(BlueprintCallable, Category = "Scaling")
	int32 ScaleForPlayers(int32 Base, int32 Players);

	// Timer callbacks
	UFUNCTION()
	void OnWaveTimerExpired();

	UFUNCTION()
	void OnIntermissionTimerExpired();

	// Blueprint Events - Important Game Moments
	UFUNCTION(BlueprintImplementableEvent, Category = "Wave Events")
	void OnWaveInitialized(int32 WaveIndex);

	UFUNCTION(BlueprintImplementableEvent, Category = "Wave Events")
	void OnWaveStarted(int32 WaveIndex);

	UFUNCTION(BlueprintImplementableEvent, Category = "Wave Events")
	void OnWaveEnded(int32 WaveIndex);

	UFUNCTION(BlueprintImplementableEvent, Category = "Wave Events")
	void OnWavePaused(int32 WaveIndex);

	UFUNCTION(BlueprintImplementableEvent, Category = "Wave Events")
	void OnWaveResumed(int32 WaveIndex);

	UFUNCTION(BlueprintImplementableEvent, Category = "Enemy Events")
	void OnEnemySpawnedGlobal(int32 TotalAliveEnemies);

	UFUNCTION(BlueprintImplementableEvent, Category = "Enemy Events")
	void OnEnemyDestroyedGlobal(int32 TotalAliveEnemies);

	UFUNCTION(BlueprintImplementableEvent, Category = "Token Events")
	void OnTokensGranted(int32 TokensGranted, int32 RemainingTokens);

	UFUNCTION(BlueprintImplementableEvent, Category = "Token Events")
	void OnTokensExhausted();

	UFUNCTION(BlueprintImplementableEvent, Category = "Intermission Events")
	void OnIntermissionStarted(float Duration);

	UFUNCTION(BlueprintImplementableEvent, Category = "Intermission Events")
	void OnIntermissionEnded(int32 NextWaveIndex);

	UFUNCTION(BlueprintImplementableEvent, Category = "Spawner Events")
	void OnAllSpawnersFinished(int32 WaveIndex);

private:
	// Timer handles
	FTimerHandle WaveTimerHandle;
	FTimerHandle IntermissionTimerHandle;

	// Helper methods
	void UpdateGameState();
	void DistributeSpawnGroups();
};
