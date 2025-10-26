#include "WaveManager.h"
#include "SQR_TD/Data/DA_Wave.h"

AWaveManager::AWaveManager()
{
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;
}

void AWaveManager::BeginPlay()
{
	Super::BeginPlay();
}

void AWaveManager::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	// Add replicated properties here
}
