#include "DA_Tower.h"
#include "Engine/Engine.h"
#include "Engine/Texture2D.h"
#include "Particles/ParticleSystem.h"
#include "Sound/SoundBase.h"

int32 UDA_Tower::GetUpgradeCost(int32 CurrentLevel) const
{
	if (CurrentLevel < 0 || CurrentLevel >= UpgradeCosts.Num())
	{
		return 0;
	}
	
	return UpgradeCosts[CurrentLevel];
}

int32 UDA_Tower::GetSellValue(int32 CurrentLevel) const
{
	int32 TotalCost = BuildCost;
	
	// Add all previous upgrade costs
	for (int32 i = 0; i < CurrentLevel && i < UpgradeCosts.Num(); i++)
	{
		TotalCost += UpgradeCosts[i];
	}
	
	return FMath::RoundToInt(TotalCost * SellRefundPercent);
}

float UDA_Tower::GetScaledDamage(int32 Level) const
{
	float BaseDamage = AttackConfig.BaseDamage;
	
	// Find level data for scaling
	for (const FTowerLevelData& LevelInfo : LevelData)
	{
		if (LevelInfo.Level == Level)
		{
			BaseDamage *= LevelInfo.DamageMultiplier;
			break;
		}
	}
	
	return BaseDamage;
}

float UDA_Tower::GetScaledRange(int32 Level) const
{
	float BaseRange = TargetingConfig.Range;
	
	// Find level data for scaling
	for (const FTowerLevelData& LevelInfo : LevelData)
	{
		if (LevelInfo.Level == Level)
		{
			BaseRange *= LevelInfo.RangeMultiplier;
			break;
		}
	}
	
	return BaseRange;
}

float UDA_Tower::GetScaledAttackRate(int32 Level) const
{
	float BaseRate = TargetingConfig.AttackRate;
	
	// Find level data for scaling
	for (const FTowerLevelData& LevelInfo : LevelData)
	{
		if (LevelInfo.Level == Level)
		{
			BaseRate *= LevelInfo.AttackRateMultiplier;
			break;
		}
	}
	
	return BaseRate;
}

UStaticMesh* UDA_Tower::GetLevelMesh(int32 Level) const
{
	// Find level data for mesh
	for (const FTowerLevelData& LevelInfo : LevelData)
	{
		if (LevelInfo.Level == Level)
		{
			return LevelInfo.LevelMesh.LoadSynchronous();
		}
	}
	
	// Fallback to base mesh
	return TowerMesh.LoadSynchronous();
}

UTexture2D* UDA_Tower::GetLevelIcon(int32 Level) const
{
	// Find level data for icon
	for (const FTowerLevelData& LevelInfo : LevelData)
	{
		if (LevelInfo.Level == Level)
		{
			return LevelInfo.LevelIcon.LoadSynchronous();
		}
	}
	
	// Fallback to base icon
	return TowerIcon.LoadSynchronous();
}

float UDA_Tower::GetSynergyValue(FGameplayTag SynergyTag) const
{
	for (const FTowerSynergy& Synergy : Synergies)
	{
		if (Synergy.SynergyTag == SynergyTag)
		{
			return Synergy.SynergyValue;
		}
	}
	
	return 0.0f;
}

bool UDA_Tower::HasTag(FGameplayTag Tag) const
{
	return TowerTags.HasTag(Tag);
}

bool UDA_Tower::CanTargetEnemyType(FGameplayTag EnemyTag) const
{
	// Check if tower can target this enemy type based on targeting priorities
	for (const FGameplayTag& PriorityTag : TargetingConfig.TargetPriorities)
	{
		if (PriorityTag == EnemyTag)
		{
			return true;
		}
	}
	
	return false;
}