#include "SQR_TDPlayerController.h"

ASQR_TDPlayerController::ASQR_TDPlayerController()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ASQR_TDPlayerController::BeginPlay()
{
	Super::BeginPlay();
}

void ASQR_TDPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	// Setup input bindings here
}
