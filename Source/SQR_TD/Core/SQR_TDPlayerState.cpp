#include "SQR_TDPlayerState.h"

ATDPlayerState::ATDPlayerState()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ATDPlayerState::BeginPlay()
{
	Super::BeginPlay();
}

void ATDPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME(ATDPlayerState, Gold);
	DOREPLIFETIME(ATDPlayerState, TDScore);
	DOREPLIFETIME(ATDPlayerState, Kills);
	DOREPLIFETIME(ATDPlayerState, Assists);
}

void ATDPlayerState::OnRep_Gold()
{
	OnGoldChanged.Broadcast(Gold);
	UE_LOG(LogTemp, Warning, TEXT("Gold Received"));
}

void ATDPlayerState::OnRep_TDScore()
{
	OnTDScoreChanged.Broadcast(TDScore);
}

void ATDPlayerState::AddGold(int32 Amount)
{
	if (HasAuthority())
	{
		Gold += Amount;
		OnRep_Gold();
	}
}

bool ATDPlayerState::SpendGold(int32 Amount)
{
	if (HasAuthority() && Gold >= Amount)
	{
		Gold -= Amount;
		OnRep_Gold();
		return true;
	}
	return false;
}

void ATDPlayerState::AddTDScore(int32 Amount)
{
	if (HasAuthority())
	{
		TDScore += Amount;
		OnRep_TDScore();
	}
}

void ATDPlayerState::AddKill()
{
	if (HasAuthority())
	{
		Kills++;
		AddTDScore(10); // Give score for kill
	}
}

void ATDPlayerState::AddAssist()
{
	if (HasAuthority())
	{
		Assists++;
		AddTDScore(5); // Give score for assist
	}
}
