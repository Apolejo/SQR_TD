#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "Net/UnrealNetwork.h"
#include "SQR_TDPlayerState.generated.h"

/**
 * PlayerState for Square Tower Defense
 * Manages individual player resources and state
 */
UCLASS()
class SQR_TD_API ASQR_TDPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	ASQR_TDPlayerState();

protected:
	virtual void BeginPlay() override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
	// Player resources and state (to be implemented)
	// Currency, lives, score, etc.
};
