#include "DA_Wave.h"
#include "Engine/Engine.h"
#include "Particles/ParticleSystem.h"
#include "Sound/SoundBase.h"

int32 UDA_Wave::GetScaledEnemyCount(int32 PlayerCount) const
{
	float BaseCount = TotalEnemies;
	
	// Apply player scaling
	if (EnemyCountPerPlayerCurve)
	{
		BaseCount *= EnemyCountPerPlayerCurve->GetFloatValue(PlayerCount);
	}
	
	return FMath::Max(1, FMath::RoundToInt(BaseCount));
}

float UDA_Wave::GetScaledEnemyHealth(int32 PlayerCount) const
{
	float BaseHealth = EnemyHealthMultiplier;
	
	// Apply player scaling
	if (EnemyHealthPerPlayerCurve)
	{
		BaseHealth *= EnemyHealthPerPlayerCurve->GetFloatValue(PlayerCount);
	}
	
	return FMath::Max(0.1f, BaseHealth);
}

float UDA_Wave::GetScaledEnemySpeed(int32 PlayerCount) const
{
	float BaseSpeed = EnemySpeedMultiplier;
	
	// Apply player scaling
	if (EnemySpeedPerPlayerCurve)
	{
		BaseSpeed *= EnemySpeedPerPlayerCurve->GetFloatValue(PlayerCount);
	}
	
	return FMath::Max(0.1f, BaseSpeed);
}

int32 UDA_Wave::GetScaledGoldReward(int32 PlayerCount) const
{
	float BaseGold = 0.0f;
	
	// Calculate base gold from wave groups
	for (const FWaveGroupData& Group : WaveGroups)
	{
		BaseGold += Group.Count * 10; // Base gold per enemy
	}
	
	// Apply player scaling
	if (GoldRewardPerPlayerCurve)
	{
		BaseGold *= GoldRewardPerPlayerCurve->GetFloatValue(PlayerCount);
	}
	
	// Apply gold multiplier
	BaseGold *= GoldRewardMultiplier;
	
	return FMath::Max(1, FMath::RoundToInt(BaseGold));
}

TArray<FWaveGroupData> UDA_Wave::GetGroupsForSpawner(int32 SpawnerID) const
{
	TArray<FWaveGroupData> GroupsForSpawner;
	
	for (const FWaveGroupData& Group : WaveGroups)
	{
		// If no specific spawner assigned or matches the requested spawner
		if (Group.AssignedSpawnerID == -1 || Group.AssignedSpawnerID == SpawnerID)
		{
			GroupsForSpawner.Add(Group);
		}
	}
	
	return GroupsForSpawner;
}

bool UDA_Wave::IsBossWave() const
{
	return BossInfo.bIsBossWave;
}

bool UDA_Wave::HasModifier(FGameplayTag ModifierTag) const
{
	return GlobalModifiers.Contains(ModifierTag);
}

float UDA_Wave::GetTotalWaveDuration() const
{
	float TotalDuration = 0.0f;
	
	for (const FWaveGroupData& Group : WaveGroups)
	{
		// Calculate duration for this group
		float GroupDuration = Group.StartDelay;
		GroupDuration += (Group.Count / Group.BurstSize) * Group.SpawnInterval;
		GroupDuration += Group.SpawnInterval; // Final spawn
		
		TotalDuration = FMath::Max(TotalDuration, GroupDuration);
	}
	
	return TotalDuration;
}

int32 UDA_Wave::GetTotalEnemyCount() const
{
	int32 TotalCount = 0;
	
	for (const FWaveGroupData& Group : WaveGroups)
	{
		TotalCount += Group.Count;
	}
	
	return TotalCount;
}