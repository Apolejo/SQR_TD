#include "DA_Enemy.h"
#include "Engine/Engine.h"
#include "Particles/ParticleSystem.h"
#include "Sound/SoundBase.h"

float UDA_Enemy::GetScaledHealth(int32 WaveNumber, int32 PlayerCount) const
{
	float BaseValue = BaseHealth;
	
	// Apply wave scaling
	if (HealthPerWaveCurve)
	{
		BaseValue *= HealthPerWaveCurve->GetFloatValue(WaveNumber);
	}
	
	// Apply player scaling
	if (HealthPerPlayerCurve)
	{
		BaseValue *= HealthPerPlayerCurve->GetFloatValue(PlayerCount);
	}
	
	return FMath::Max(1.0f, BaseValue);
}

float UDA_Enemy::GetScaledSpeed(int32 WaveNumber) const
{
	float BaseValue = BaseMoveSpeed;
	
	// Apply wave scaling
	if (SpeedPerWaveCurve)
	{
		BaseValue *= SpeedPerWaveCurve->GetFloatValue(WaveNumber);
	}
	
	return FMath::Max(1.0f, BaseValue);
}

int32 UDA_Enemy::GetScaledGold(int32 WaveNumber) const
{
	float BaseValue = BountyGold;
	
	// Apply wave scaling
	if (GoldPerWaveCurve)
	{
		BaseValue *= GoldPerWaveCurve->GetFloatValue(WaveNumber);
	}
	
	return FMath::Max(1, FMath::RoundToInt(BaseValue));
}

float UDA_Enemy::GetResistanceValue(FGameplayTag DamageType) const
{
	for (const FResistanceData& Resistance : Resistances)
	{
		if (Resistance.DamageType == DamageType)
		{
			return Resistance.ResistanceValue;
		}
	}
	
	return 0.0f;
}

bool UDA_Enemy::HasTag(FGameplayTag Tag) const
{
	return EnemyTags.HasTag(Tag);
}