#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "SQR_TDHUD.generated.h"

/**
 * HUD for Square Tower Defense
 * Blueprint placeholder - UI implementation will be done in Blueprint
 */
UCLASS(Blueprintable, BlueprintType)
class SQR_TD_API ATDHUD : public AHUD
{
	GENERATED_BODY()

public:
	ATDHUD();

protected:
	virtual void BeginPlay() override;

public:
	// Blueprint hooks for UI management
	UFUNCTION(BlueprintImplementableEvent, Category = "UI")
	void OnWaveStarted(int32 WaveNumber);

	UFUNCTION(BlueprintImplementableEvent, Category = "UI")
	void OnWaveEnded(int32 WaveNumber);

	UFUNCTION(BlueprintImplementableEvent, Category = "UI")
	void OnGoldChanged(int32 NewGold);

	UFUNCTION(BlueprintImplementableEvent, Category = "UI")
	void OnScoreChanged(int32 NewScore);

	UFUNCTION(BlueprintImplementableEvent, Category = "UI")
	void OnTeamLivesChanged(int32 NewLives);

	UFUNCTION(BlueprintImplementableEvent, Category = "UI")
	void OnAliveEnemiesChanged(int32 NewCount);

	UFUNCTION(BlueprintImplementableEvent, Category = "UI")
	void ShowError(const FText& ErrorMessage);

	UFUNCTION(BlueprintImplementableEvent, Category = "UI")
	void PlayPing(const FVector& PingLocation);
};
