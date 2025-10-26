#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"
#include "DA_Wave.generated.h"

/**
 * DA_Wave - Data asset for wave configuration
 * Defines wave properties, enemy types, and timing
 */
UCLASS()
class SQR_TD_API UDA_Wave : public UDataAsset
{
	GENERATED_BODY()

public:
	UDA_Wave();

	// Wave properties (to be implemented)
	// Wave number, enemy types, spawn timing, etc.
};
