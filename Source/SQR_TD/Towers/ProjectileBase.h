#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Net/UnrealNetwork.h"
#include "GameplayTagContainer.h"
#include "SQR_TD/Towers/ProjectileBase.generated.h"

/**
 * ProjectileBase - Base class for all projectile types
 * Handles projectile movement and collision
 */
UCLASS()
class SQR_TD_API AProjectileBase : public AActor
{
	GENERATED_BODY()

public:
	AProjectileBase();

protected:
	virtual void BeginPlay() override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
	// Projectile properties and behavior (to be implemented)
	// Speed, damage, effects, collision handling, etc.
};
