#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SQR_TDPlayerController.generated.h"

/**
 * PlayerController for Square Tower Defense
 * Handles input and client-server communication
 */
UCLASS()
class SQR_TD_API ASQR_TDPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ASQR_TDPlayerController();

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

public:
	// Input handling and RPCs (to be implemented)
};
