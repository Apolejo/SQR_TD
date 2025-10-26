#include "SQR_TDPlayerState.h"

ASQR_TDPlayerState::ASQR_TDPlayerState()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ASQR_TDPlayerState::BeginPlay()
{
	Super::BeginPlay();
}

void ASQR_TDPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	// Add replicated properties here
}
