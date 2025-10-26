#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "TDDataStructures.h"
#include "DA_Enemy.generated.h"

/**
 * Enemy Data Asset
 * Contains comprehensive enemy-specific data and configuration
 */
UCLASS(BlueprintType)
class SQR_TD_API UDA_Enemy : public UDataAsset
{
	GENERATED_BODY()

public:
	// Basic enemy information
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Basic Info")
	FText EnemyName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Basic Info")
	FText Description;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Basic Info")
	TSoftObjectPtr<UStaticMesh> EnemyMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Basic Info")
	TSoftObjectPtr<UStaticMesh> DeathMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Basic Info")
	TSoftObjectPtr<UStaticMesh> HitMesh;

	// Gameplay tags
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Gameplay Tags")
	FGameplayTagContainer EnemyTags;

	// Core stats
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Core Stats")
	float BaseHealth = 100.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Core Stats")
	float BaseMoveSpeed = 300.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Core Stats")
	int32 BountyGold = 10;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Core Stats")
	int32 DamageToCore = 1;

	// Resistances
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Resistances")
	TArray<FResistanceData> Resistances;

	// Scaling curves
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Scaling")
	UCurveFloat* HealthPerWaveCurve;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Scaling")
	UCurveFloat* HealthPerPlayerCurve;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Scaling")
	UCurveFloat* SpeedPerWaveCurve;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Scaling")
	UCurveFloat* GoldPerWaveCurve;

	// AI Profile
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AI Profile")
	FAIProfile AIProfile;

	// Visual effects
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Visual Effects")
	TSoftObjectPtr<UParticleSystem> SpawnEffect;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Visual Effects")
	TSoftObjectPtr<UParticleSystem> DeathEffect;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Visual Effects")
	TSoftObjectPtr<UParticleSystem> HitEffect;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Visual Effects")
	TSoftObjectPtr<UParticleSystem> TrailEffect;

	// Audio
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Audio")
	TSoftObjectPtr<USoundBase> SpawnSound;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Audio")
	TSoftObjectPtr<USoundBase> DeathSound;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Audio")
	TSoftObjectPtr<USoundBase> HitSound;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Audio")
	TSoftObjectPtr<USoundBase> MoveSound;

	// Blueprint functions
	UFUNCTION(BlueprintCallable, Category = "Enemy Data")
	float GetScaledHealth(int32 WaveNumber, int32 PlayerCount) const;

	UFUNCTION(BlueprintCallable, Category = "Enemy Data")
	float GetScaledSpeed(int32 WaveNumber) const;

	UFUNCTION(BlueprintCallable, Category = "Enemy Data")
	int32 GetScaledGold(int32 WaveNumber) const;

	UFUNCTION(BlueprintCallable, Category = "Enemy Data")
	float GetResistanceValue(FGameplayTag DamageType) const;

	UFUNCTION(BlueprintCallable, Category = "Enemy Data")
	bool HasTag(FGameplayTag Tag) const;
};