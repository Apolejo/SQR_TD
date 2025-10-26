#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SQR_TDGameMode.generated.h"

/**
 * Main GameMode for Square Tower Defense
 * Handles game state initialization and player spawning
 */
UCLASS()
class SQR_TD_API ASQR_TDGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ASQR_TDGameMode();
};
