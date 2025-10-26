#include "EnemyBase.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/Engine.h"

AEnemyBase::AEnemyBase()
{
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;

	// Create dummy mesh component
	DummyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DummyMesh"));
	RootComponent = DummyMesh;
	
	// Set up basic collision
	DummyMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	DummyMesh->SetCollisionObjectType(ECollisionChannel::ECC_Pawn);
	DummyMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	DummyMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
	DummyMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Ignore);

	// Set default mesh (basic cube)
	static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMesh(TEXT("/Engine/BasicShapes/Cube"));
	if (CubeMesh.Succeeded())
	{
		DummyMesh->SetStaticMesh(CubeMesh.Object);
	}

	// Scale down the cube to make it look more like an enemy
	DummyMesh->SetRelativeScale3D(FVector(0.5f, 0.5f, 1.0f));
}

void AEnemyBase::BeginPlay()
{
	Super::BeginPlay();
	
	// Broadcast spawn event
	OnEnemySpawned();
}

void AEnemyBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME(AEnemyBase, Health);
	DOREPLIFETIME(AEnemyBase, MaxHealth);
	DOREPLIFETIME(AEnemyBase, Speed);
	DOREPLIFETIME(AEnemyBase, LaneID);
}

void AEnemyBase::SetLaneID(int32 NewLaneID)
{
	if (HasAuthority())
	{
		LaneID = NewLaneID;
	}
}

float AEnemyBase::TakeDamage(float DamageAmount, const FDamageEvent& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	if (!HasAuthority() || !IsAlive())
	{
		return 0.0f;
	}

	float OldHealth = Health;
	Health = FMath::Max(0.0f, Health - DamageAmount);
	
	// Broadcast damage event
	OnEnemyDamaged(Health, DamageAmount);
	
	// Check if enemy died
	if (Health <= 0.0f && OldHealth > 0.0f)
	{
		// Broadcast destroy event
		OnEnemyDestroyed();
		
		// Destroy the actor
		Destroy();
	}
	
	return DamageAmount;
}

bool AEnemyBase::IsAlive() const
{
	return Health > 0.0f;
}
