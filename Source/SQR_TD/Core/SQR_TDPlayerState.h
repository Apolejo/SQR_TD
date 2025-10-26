#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "Net/UnrealNetwork.h"
#include "SQR_TDPlayerState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGoldChanged, int32, NewGold);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnScoreChanged, int32, NewScore);

/**
 * PlayerState for Square Tower Defense
 * Manages individual player resources and state
 */
UCLASS()
class SQR_TD_API ATDPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	ATDPlayerState();

protected:
	virtual void BeginPlay() override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	// RepNotify functions
	UFUNCTION()
	void OnRep_Gold();
	
	UFUNCTION()
	void OnRep_Score();

public:
	// Replicated properties
	UPROPERTY(ReplicatedUsing = OnRep_Gold, BlueprintReadOnly, Category = "Player Resources")
	int32 Gold = 0;

	UPROPERTY(ReplicatedUsing = OnRep_Score, BlueprintReadOnly, Category = "Player Stats")
	int32 Score = 0;

	UPROPERTY(Replicated, BlueprintReadOnly, Category = "Player Stats")
	int32 Kills = 0;

	UPROPERTY(Replicated, BlueprintReadOnly, Category = "Player Stats")
	int32 Assists = 0;

	// Events
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnGoldChanged OnGoldChanged;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnScoreChanged OnScoreChanged;

	// Server-only methods
	UFUNCTION(BlueprintCallable, Category = "Player Resources")
	void AddGold(int32 Amount);

	UFUNCTION(BlueprintCallable, Category = "Player Resources")
	bool SpendGold(int32 Amount);

	UFUNCTION(BlueprintCallable, Category = "Player Stats")
	void AddScore(int32 Amount);

	UFUNCTION(BlueprintCallable, Category = "Player Stats")
	void AddKill();

	UFUNCTION(BlueprintCallable, Category = "Player Stats")
	void AddAssist();
};
