#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "SQR_TD/Enemies/EnemyAIController.generated.h"

/**
 * EnemyAIController - AI controller for enemy behavior
 * Handles pathfinding and enemy AI logic
 */
UCLASS()
class SQR_TD_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()

public:
	AEnemyAIController();

protected:
	virtual void BeginPlay() override;

public:
	// AI behavior functions (to be implemented)
	// SetTarget, UpdatePath, HandleDamage, etc.
};
