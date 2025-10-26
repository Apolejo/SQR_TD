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
	DOREPLIFETIME(ATDPlayerState, Score);
	DOREPLIFETIME(ATDPlayerState, Kills);
	DOREPLIFETIME(ATDPlayerState, Assists);
}

void ATDPlayerState::OnRep_Gold()
{
	OnGoldChanged.Broadcast(Gold);
}

void ATDPlayerState::OnRep_Score()
{
	OnScoreChanged.Broadcast(Score);
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

void ATDPlayerState::AddScore(int32 Amount)
{
	if (HasAuthority())
	{
		Score += Amount;
		OnRep_Score();
	}
}

void ATDPlayerState::AddKill()
{
	if (HasAuthority())
	{
		Kills++;
		AddScore(10); // Give score for kill
	}
}

void ATDPlayerState::AddAssist()
{
	if (HasAuthority())
	{
		Assists++;
		AddScore(5); // Give score for assist
	}
}
