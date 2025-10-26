#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Net/UnrealNetwork.h"
#include "GameplayTagContainer.h"
#include "EnemyBase.generated.h"

/**
 * EnemyBase - Base class for all enemy types
 * Server-authoritative enemy behavior and state
 */
UCLASS()
class SQR_TD_API AEnemyBase : public ACharacter
{
	GENERATED_BODY()

public:
	AEnemyBase();

protected:
	virtual void BeginPlay() override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
	// Enemy properties and behavior (to be implemented)
	// Health, speed, damage, effects, etc.
};
