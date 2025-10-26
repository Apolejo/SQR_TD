#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Net/UnrealNetwork.h"
#include "GameplayTagContainer.h"
#include "TowerBase.generated.h"

/**
 * TowerBase - Base class for all tower types
 * Server-authoritative tower behavior and targeting
 */
UCLASS()
class SQR_TD_API ATowerBase : public AActor
{
	GENERATED_BODY()

public:
	ATowerBase();

protected:
	virtual void BeginPlay() override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
	// Tower properties and behavior (to be implemented)
	// Range, damage, fire rate, targeting, etc.
};
