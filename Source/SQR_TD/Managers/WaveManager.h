#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Net/UnrealNetwork.h"
#include "SQR_TD/Data/DA_Wave.h"
#include "WaveManager.generated.h"

/**
 * WaveManager - Server-authoritative wave management
 * Handles wave progression, timing, and enemy spawning coordination
 */
UCLASS()
class SQR_TD_API AWaveManager : public AActor
{
	GENERATED_BODY()

public:
	AWaveManager();

protected:
	virtual void BeginPlay() override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
	// Wave management functions (to be implemented)
	// StartWave, EndWave, GetCurrentWave, etc.
};
