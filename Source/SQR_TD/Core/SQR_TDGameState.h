#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "Net/UnrealNetwork.h"
#include "SQR_TDGameState.generated.h"

/**
 * Main GameState for Square Tower Defense
 * Server-authoritative state management for co-op gameplay
 */
UCLASS()
class SQR_TD_API ASQR_TDGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	ASQR_TDGameState();

protected:
	virtual void BeginPlay() override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
	// Game state properties (to be implemented)
	// Wave management, enemy counts, player resources, etc.
};
