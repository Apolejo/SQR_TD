#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"
#include "SQR_TD/Data/DA_Enemy.generated.h"

/**
 * DA_Enemy - Data asset for enemy configuration
 * Defines enemy properties, stats, and behavior
 */
UCLASS()
class SQR_TD_API UDA_Enemy : public UDataAsset
{
	GENERATED_BODY()

public:
	UDA_Enemy();

	// Enemy properties (to be implemented)
	// Health, speed, damage, tags, etc.
};
