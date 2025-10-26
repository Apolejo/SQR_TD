#include "BuildSystemComponent.h"

UBuildSystemComponent::UBuildSystemComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	SetIsReplicatedByDefault(true);
}

void UBuildSystemComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UBuildSystemComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	// Add replicated properties here
}
