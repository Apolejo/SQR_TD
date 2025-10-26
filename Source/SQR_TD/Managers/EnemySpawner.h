#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Net/UnrealNetwork.h"
#include "SQR_TD/Data/DA_Enemy.h"
#include "SQR_TD/Core/TDSpawningStructures.h"
#include "EnemySpawner.generated.h"

class ATDWaveManager;

/**
 * EnemySpawner - Server-authoritative enemy spawning
 * Manages enemy instantiation with timer-driven spawning and token bucket system
 */
UCLASS()
class SQR_TD_API ATDEnemySpawner : public AActor
{
	GENERATED_BODY()

public:
	ATDEnemySpawner();

protected:
	virtual void BeginPlay() override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
	// Spawner properties
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Spawner Settings")
	int32 LaneID = 0;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Spawner Settings")
	FTransform SpawnPoint;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Spawner Settings")
	bool bPausedByCap = false;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Spawner Settings")
	int32 BurstSize = 1;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Spawner Settings")
	float SpawnInterval = 1.0f;

	// Spawn queue
	UPROPERTY(BlueprintReadOnly, Category = "Spawn Data")
	TArray<FSpawnGroup> SpawnQueue;

	// Spawner methods
	UFUNCTION(BlueprintCallable, Category = "Spawner Management")
	void SetSpawnGroups(const TArray<FSpawnGroup>& Groups);

	UFUNCTION(BlueprintCallable, Category = "Spawner Management")
	void SetPaused(bool bPaused);

	UFUNCTION(BlueprintCallable, Category = "Spawner Management")
	bool IsGroupFinished() const;

	UFUNCTION(BlueprintCallable, Category = "Spawner Management")
	void StartSpawning();

	UFUNCTION(BlueprintCallable, Category = "Spawner Management")
	void StopSpawning();

	// Timer-driven spawning
	UFUNCTION()
	void TickSpawn();

	// Spawn methods
	UFUNCTION(BlueprintCallable, Category = "Spawning")
	void SpawnEnemyGroup(const FSpawnGroup& Group);

	UFUNCTION(BlueprintCallable, Category = "Spawning")
	void SpawnEnemy(TSubclassOf<AActor> EnemyClass);

	// Callbacks
	UFUNCTION()
	void OnEnemyDestroyed(AActor* DestroyedEnemy);

private:
	// Timer handle
	FTimerHandle SpawnTimerHandle;

	// Current spawn group
	FSpawnGroup CurrentGroup;
	int32 RemainingInGroup = 0;
	int32 RemainingInBurst = 0;
	int32 CurrentGroupIndex = 0;

	// Wave manager reference
	UPROPERTY()
	TObjectPtr<ATDWaveManager> WaveManager;

	// Helper methods
	void RequestTokens();
	void NotifyWaveManager();
};
