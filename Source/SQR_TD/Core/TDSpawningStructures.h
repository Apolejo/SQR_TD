#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "TDSpawningStructures.generated.h"

/**
 * Spawn group data for enemy spawning
 */
USTRUCT(BlueprintType)
struct SQR_TD_API FSpawnGroup
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<AActor> EnemyClass;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 Count = 1;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float SpawnInterval = 1.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 BurstSize = 1;

	FSpawnGroup()
		: EnemyClass(nullptr)
		, Count(1)
		, SpawnInterval(1.0f)
		, BurstSize(1)
	{
	}
};

/**
 * Wave spawn data
 */
USTRUCT(BlueprintType)
struct SQR_TD_API FWaveSpawnData
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<FSpawnGroup> SpawnGroups;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float WaveDuration = 60.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 MaxConcurrentEnemies = 50;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 WaveBudget = 100;

	FWaveSpawnData()
		: WaveDuration(60.0f)
		, MaxConcurrentEnemies(50)
		, WaveBudget(100)
	{
	}
};
