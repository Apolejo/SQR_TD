#include "TowerBase.h"

ATowerBase::ATowerBase()
{
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;
}

void ATowerBase::BeginPlay()
{
	Super::BeginPlay();
}

void ATowerBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	// Add replicated properties here
}
