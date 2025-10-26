#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Curves/CurveFloat.h"
#include "GameplayTagContainer.h"
#include "Engine/StaticMesh.h"
#include "Engine/Texture2D.h"
#include "TDDataStructures.generated.h"

/**
 * Resistance mapping for damage types
 */
USTRUCT(BlueprintType)
struct SQR_TD_API FResistanceData
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Resistance")
	FGameplayTag DamageType;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Resistance", meta = (ClampMin = "0.0", ClampMax = "1.0"))
	float ResistanceValue = 0.0f;

	FResistanceData()
	{
		ResistanceValue = 0.0f;
	}
};

/**
 * AI Profile flags for enemy behavior
 */
USTRUCT(BlueprintType)
struct SQR_TD_API FAIProfile
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AI Profile")
	bool bFlying = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AI Profile")
	bool bBoss = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AI Profile")
	bool bCanSwarm = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AI Profile")
	bool bCanPhase = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AI Profile")
	bool bCanRegenerate = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AI Profile")
	bool bCanShield = false;

	FAIProfile()
	{
		bFlying = false;
		bBoss = false;
		bCanSwarm = false;
		bCanPhase = false;
		bCanRegenerate = false;
		bCanShield = false;
	}
};

/**
 * Targeting configuration for towers
 */
USTRUCT(BlueprintType)
struct SQR_TD_API FTargetingConfig
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Targeting")
	float Range = 1000.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Targeting")
	float AttackRate = 1.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Targeting")
	TArray<FGameplayTag> TargetPriorities;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Targeting")
	bool bCanTargetFlying = true;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Targeting")
	bool bCanTargetGround = true;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Targeting")
	bool bCanTargetBosses = true;

	FTargetingConfig()
	{
		Range = 1000.0f;
		AttackRate = 1.0f;
		bCanTargetFlying = true;
		bCanTargetGround = true;
		bCanTargetBosses = true;
	}
};

/**
 * Attack configuration for towers
 */
USTRUCT(BlueprintType)
struct SQR_TD_API FAttackConfig
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attack")
	FGameplayTag AttackType;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attack")
	TSubclassOf<class AActor> ProjectileClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attack")
	float BaseDamage = 10.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attack")
	TArray<FGameplayTag> DamageEffects;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attack")
	float SplashRadius = 0.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attack")
	int32 PierceCount = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attack")
	float ProjectileSpeed = 1000.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attack")
	bool bIsHitscan = false;

	FAttackConfig()
	{
		BaseDamage = 10.0f;
		SplashRadius = 0.0f;
		PierceCount = 0;
		ProjectileSpeed = 1000.0f;
		bIsHitscan = false;
	}
};

/**
 * Tower level data
 */
USTRUCT(BlueprintType)
struct SQR_TD_API FTowerLevelData
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Level Data")
	int32 Level = 1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Level Data")
	int32 UpgradeCost = 100;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Level Data")
	float DamageMultiplier = 1.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Level Data")
	float RangeMultiplier = 1.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Level Data")
	float AttackRateMultiplier = 1.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Level Data")
	TSoftObjectPtr<UStaticMesh> LevelMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Level Data")
	TSoftObjectPtr<UTexture2D> LevelIcon;

	FTowerLevelData()
	{
		Level = 1;
		UpgradeCost = 100;
		DamageMultiplier = 1.0f;
		RangeMultiplier = 1.0f;
		AttackRateMultiplier = 1.0f;
	}
};

/**
 * Tower synergy data
 */
USTRUCT(BlueprintType)
struct SQR_TD_API FTowerSynergy
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Synergy")
	FGameplayTag SynergyTag;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Synergy")
	float SynergyValue = 0.0f;

	FTowerSynergy()
	{
		SynergyValue = 0.0f;
	}
};

/**
 * Wave group data for wave composition
 */
USTRUCT(BlueprintType)
struct SQR_TD_API FWaveGroupData
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Wave Group")
	FGameplayTag EnemyType;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Wave Group")
	int32 Count = 1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Wave Group")
	int32 BurstSize = 1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Wave Group")
	float SpawnInterval = 1.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Wave Group")
	float StartDelay = 0.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Wave Group")
	int32 AssignedSpawnerID = -1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Wave Group")
	float Weight = 1.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Wave Group")
	TArray<FGameplayTag> Modifiers;

	FWaveGroupData()
	{
		Count = 1;
		BurstSize = 1;
		SpawnInterval = 1.0f;
		StartDelay = 0.0f;
		AssignedSpawnerID = -1;
		Weight = 1.0f;
	}
};

/**
 * Boss information for special waves
 */
USTRUCT(BlueprintType)
struct SQR_TD_API FBossInfo
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Boss")
	bool bIsBossWave = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Boss")
	FGameplayTag BossType;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Boss")
	int32 BossCount = 1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Boss")
	float BossHealthMultiplier = 2.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Boss")
	float BossSpeedMultiplier = 0.5f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Boss")
	TArray<FGameplayTag> BossAbilities;

	FBossInfo()
	{
		bIsBossWave = false;
		BossCount = 1;
		BossHealthMultiplier = 2.0f;
		BossSpeedMultiplier = 0.5f;
	}
};
