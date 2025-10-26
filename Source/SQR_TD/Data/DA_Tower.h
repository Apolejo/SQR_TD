#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "TDDataStructures.h"
#include "DA_Tower.generated.h"

/**
 * Tower Data Asset
 * Contains comprehensive tower-specific data and configuration
 */
UCLASS(BlueprintType)
class SQR_TD_API UDA_Tower : public UDataAsset
{
	GENERATED_BODY()

public:
	// Basic tower information
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Basic Info")
	FText TowerName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Basic Info")
	FText Description;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Basic Info")
	TSoftObjectPtr<UTexture2D> TowerIcon;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Basic Info")
	TSoftObjectPtr<UStaticMesh> TowerMesh;

	// Gameplay tags
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Gameplay Tags")
	FGameplayTag CategoryTag;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Gameplay Tags")
	FGameplayTagContainer TowerTags;

	// Economic data
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Economics")
	int32 BuildCost = 100;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Economics")
	TArray<int32> UpgradeCosts;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Economics")
	float SellRefundPercent = 0.75f;

	// Targeting configuration
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Targeting")
	FTargetingConfig TargetingConfig;

	// Attack configuration
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attack")
	FAttackConfig AttackConfig;

	// Level progression data
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Level Progression")
	TArray<FTowerLevelData> LevelData;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Level Progression")
	int32 MaxLevel = 3;

	// Synergies with other towers
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Synergies")
	TArray<FTowerSynergy> Synergies;

	// Visual effects per level
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Visual Effects")
	TSoftObjectPtr<UParticleSystem> MuzzleFlashEffect;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Visual Effects")
	TSoftObjectPtr<UParticleSystem> ImpactEffect;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Visual Effects")
	TSoftObjectPtr<UParticleSystem> UpgradeEffect;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Visual Effects")
	TSoftObjectPtr<UParticleSystem> SellEffect;

	// Audio
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Audio")
	TSoftObjectPtr<USoundBase> BuildSound;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Audio")
	TSoftObjectPtr<USoundBase> AttackSound;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Audio")
	TSoftObjectPtr<USoundBase> UpgradeSound;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Audio")
	TSoftObjectPtr<USoundBase> SellSound;

	// Blueprint functions
	UFUNCTION(BlueprintCallable, Category = "Tower Data")
	int32 GetUpgradeCost(int32 CurrentLevel) const;

	UFUNCTION(BlueprintCallable, Category = "Tower Data")
	int32 GetSellValue(int32 CurrentLevel) const;

	UFUNCTION(BlueprintCallable, Category = "Tower Data")
	float GetScaledDamage(int32 Level) const;

	UFUNCTION(BlueprintCallable, Category = "Tower Data")
	float GetScaledRange(int32 Level) const;

	UFUNCTION(BlueprintCallable, Category = "Tower Data")
	float GetScaledAttackRate(int32 Level) const;

	UFUNCTION(BlueprintCallable, Category = "Tower Data")
	UStaticMesh* GetLevelMesh(int32 Level) const;

	UFUNCTION(BlueprintCallable, Category = "Tower Data")
	UTexture2D* GetLevelIcon(int32 Level) const;

	UFUNCTION(BlueprintCallable, Category = "Tower Data")
	float GetSynergyValue(FGameplayTag SynergyTag) const;

	UFUNCTION(BlueprintCallable, Category = "Tower Data")
	bool HasTag(FGameplayTag Tag) const;

	UFUNCTION(BlueprintCallable, Category = "Tower Data")
	bool CanTargetEnemyType(FGameplayTag EnemyTag) const;
};