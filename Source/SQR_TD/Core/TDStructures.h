#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "TDStructures.generated.h"

/**
 * Build request structure for tower placement validation
 */
USTRUCT(BlueprintType)
struct SQR_TD_API FBuildRequest
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FVector Location;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FRotator Rotation;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<AActor> TowerClass;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 Cost;

	FBuildRequest()
		: Location(FVector::ZeroVector)
		, Rotation(FRotator::ZeroRotator)
		, TowerClass(nullptr)
		, Cost(0)
	{
	}
};

/**
 * Tower build specification for construction
 */
USTRUCT(BlueprintType)
struct SQR_TD_API FTowerBuildSpec
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FVector Location;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FRotator Rotation;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<AActor> TowerClass;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 Cost;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FName TowerID;

	FTowerBuildSpec()
		: Location(FVector::ZeroVector)
		, Rotation(FRotator::ZeroRotator)
		, TowerClass(nullptr)
		, Cost(0)
		, TowerID(NAME_None)
	{
	}
};
