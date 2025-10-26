#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"
#include "DA_Tower.generated.h"

/**
 * DA_Tower - Data asset for tower configuration
 * Defines tower properties, stats, and behavior
 */
UCLASS()
class SQR_TD_API UDA_Tower : public UDataAsset
{
	GENERATED_BODY()

public:
	UDA_Tower();

	// Tower properties (to be implemented)
	// Range, damage, fire rate, cost, tags, etc.
};
