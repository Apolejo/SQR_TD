#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "SQR_TDHUD.generated.h"

/**
 * HUD for Square Tower Defense
 * Manages UI display and Blueprint integration
 */
UCLASS()
class SQR_TD_API ASQR_TDHUD : public AHUD
{
	GENERATED_BODY()

public:
	ASQR_TDHUD();

protected:
	virtual void BeginPlay() override;

public:
	// UI management and Blueprint hooks (to be implemented)
};
