#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "TDDataStructures.h"
#include "DA_Wave.generated.h"

/**
 * Wave Data Asset
 * Contains comprehensive wave-specific data and configuration
 */
UCLASS(BlueprintType)
class SQR_TD_API UDA_Wave : public UDataAsset
{
	GENERATED_BODY()

public:
	// Basic wave information
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Basic Info")
	int32 WaveIndex = 1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Basic Info")
	FText WaveName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Basic Info")
	FText WaveDescription;

	// Wave timing and limits
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Wave Settings")
	float IntermissionDuration = 30.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Wave Settings")
	int32 MaxConcurrentEnemies = 50;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Wave Settings")
	float WaveTimeLimit = 300.0f;

	// Wave composition
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Wave Composition")
	int32 BudgetPoints = 100;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Wave Composition")
	int32 TotalEnemies = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Wave Composition")
	TArray<FWaveGroupData> WaveGroups;

	// Boss information
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Boss")
	FBossInfo BossInfo;

	// Scaling curves
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Scaling")
	UCurveFloat* EnemyCountPerPlayerCurve;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Scaling")
	UCurveFloat* EnemyHealthPerPlayerCurve;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Scaling")
	UCurveFloat* EnemySpeedPerPlayerCurve;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Scaling")
	UCurveFloat* GoldRewardPerPlayerCurve;

	// Wave modifiers
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Modifiers")
	TArray<FGameplayTag> GlobalModifiers;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Modifiers")
	float EnemySpeedMultiplier = 1.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Modifiers")
	float EnemyHealthMultiplier = 1.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Modifiers")
	float EnemyDamageMultiplier = 1.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Modifiers")
	float GoldRewardMultiplier = 1.0f;

	// Visual effects
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Visual Effects")
	TSoftObjectPtr<UParticleSystem> WaveStartEffect;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Visual Effects")
	TSoftObjectPtr<UParticleSystem> WaveEndEffect;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Visual Effects")
	TSoftObjectPtr<UParticleSystem> BossSpawnEffect;

	// Audio
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Audio")
	TSoftObjectPtr<USoundBase> WaveStartSound;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Audio")
	TSoftObjectPtr<USoundBase> WaveEndSound;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Audio")
	TSoftObjectPtr<USoundBase> BossSpawnSound;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Audio")
	TSoftObjectPtr<USoundBase> IntermissionSound;

	// Blueprint functions
	UFUNCTION(BlueprintCallable, Category = "Wave Data")
	int32 GetScaledEnemyCount(int32 PlayerCount) const;

	UFUNCTION(BlueprintCallable, Category = "Wave Data")
	float GetScaledEnemyHealth(int32 PlayerCount) const;

	UFUNCTION(BlueprintCallable, Category = "Wave Data")
	float GetScaledEnemySpeed(int32 PlayerCount) const;

	UFUNCTION(BlueprintCallable, Category = "Wave Data")
	int32 GetScaledGoldReward(int32 PlayerCount) const;

	UFUNCTION(BlueprintCallable, Category = "Wave Data")
	TArray<FWaveGroupData> GetGroupsForSpawner(int32 SpawnerID) const;

	UFUNCTION(BlueprintCallable, Category = "Wave Data")
	bool IsBossWave() const;

	UFUNCTION(BlueprintCallable, Category = "Wave Data")
	bool HasModifier(FGameplayTag ModifierTag) const;

	UFUNCTION(BlueprintCallable, Category = "Wave Data")
	float GetTotalWaveDuration() const;

	UFUNCTION(BlueprintCallable, Category = "Wave Data")
	int32 GetTotalEnemyCount() const;
};