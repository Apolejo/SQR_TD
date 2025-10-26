#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Net/UnrealNetwork.h"
#include "SQR_TD/Building/BuildSystemComponent.generated.h"

/**
 * BuildSystemComponent - Handles tower placement and building
 * Server-authoritative building validation and placement
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SQR_TD_API UBuildSystemComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UBuildSystemComponent();

protected:
	virtual void BeginPlay() override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
	// Building system functions (to be implemented)
	// CanPlaceTower, PlaceTower, ValidatePlacement, etc.
};
