#include "SQR_TDGameState.h"

ASQR_TDGameState::ASQR_TDGameState()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ASQR_TDGameState::BeginPlay()
{
	Super::BeginPlay();
}

void ASQR_TDGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	// Add replicated properties here
}
