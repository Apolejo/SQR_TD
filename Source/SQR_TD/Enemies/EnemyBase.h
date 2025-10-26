#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Net/UnrealNetwork.h"
#include "GameplayTagContainer.h"
#include "Components/StaticMeshComponent.h"
#include "EnemyBase.generated.h"

/**
 * EnemyBase - Base class for all enemy types
 * Simple dummy enemy for testing spawning system
 */
UCLASS(Blueprintable, BlueprintType)
class SQR_TD_API AEnemyBase : public APawn
{
	GENERATED_BODY()

public:
	AEnemyBase();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	// Dummy mesh component for visual representation
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* DummyMesh;

	// Basic enemy properties
	UPROPERTY(Replicated, BlueprintReadOnly, Category = "Enemy Stats")
	float Health = 100.0f;

	UPROPERTY(Replicated, BlueprintReadOnly, Category = "Enemy Stats")
	float MaxHealth = 100.0f;

	UPROPERTY(Replicated, BlueprintReadOnly, Category = "Enemy Stats")
	float Speed = 300.0f;

	UPROPERTY(Replicated, BlueprintReadOnly, Category = "Enemy Stats")
	int32 LaneID = 0;

	// Movement properties
	UPROPERTY(Replicated, BlueprintReadOnly, Category = "Movement")
	FVector MoveDirection = FVector::ForwardVector;

	UPROPERTY(Replicated, BlueprintReadOnly, Category = "Movement")
	bool bIsMoving = true;

	UPROPERTY(Replicated, BlueprintReadOnly, Category = "Movement")
	FVector TargetLocation = FVector::ZeroVector;

public:
	// Basic enemy functions
	UFUNCTION(BlueprintCallable, Category = "Enemy")
	void SetLaneID(int32 NewLaneID);

	// Override base class TakeDamage
	virtual float TakeDamage(float DamageAmount, const FDamageEvent& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	UFUNCTION(BlueprintCallable, Category = "Enemy")
	bool IsAlive() const;

	// Movement functions
	UFUNCTION(BlueprintCallable, Category = "Movement")
	void SetMoveDirection(const FVector& NewDirection);

	UFUNCTION(BlueprintCallable, Category = "Movement")
	void SetTargetLocation(const FVector& NewTarget);

	UFUNCTION(BlueprintCallable, Category = "Movement")
	void SetIsMoving(bool bNewMoving);

	UFUNCTION(BlueprintCallable, Category = "Movement")
	void StopMovement();

	UFUNCTION(BlueprintCallable, Category = "Movement")
	void ResumeMovement();

	// Blueprint events
	UFUNCTION(BlueprintImplementableEvent, Category = "Enemy Events")
	void OnEnemySpawned();

	UFUNCTION(BlueprintImplementableEvent, Category = "Enemy Events")
	void OnEnemyDestroyed();

	UFUNCTION(BlueprintImplementableEvent, Category = "Enemy Events")
	void OnEnemyDamaged(float NewHealth, float DamageAmount);
};
