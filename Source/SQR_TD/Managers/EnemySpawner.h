#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Net/UnrealNetwork.h"
#include "SQR_TD/Data/DA_Enemy.h"
#include "EnemySpawner.generated.h"

/**
 * EnemySpawner - Server-authoritative enemy spawning
 * Manages enemy instantiation and token bucket system
 */
UCLASS()
class SQR_TD_API AEnemySpawner : public AActor
{
	GENERATED_BODY()

public:
	AEnemySpawner();

protected:
	virtual void BeginPlay() override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
	// Enemy spawning functions (to be implemented)
	// SpawnEnemy, CanSpawnEnemy, GetEnemyCount, etc.
};
