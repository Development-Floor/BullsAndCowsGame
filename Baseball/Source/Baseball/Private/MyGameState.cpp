#include "MyGameState.h"

void AMyGameState::AddPlayerRemainTurn(const int32& PlayerId, const int32& TurnCount)
{
	PlayerRemainTurn.Add(PlayerId, TurnCount);
}

void AMyGameState::DecreaseRemainTurn(const int32& PlayerId)
{
	if (PlayerRemainTurn.Contains(PlayerId))
	{
		PlayerRemainTurn[PlayerId]--;
	}
}

void AMyGameState::SwapPlayerController()
{
	Swap(CurrentPlayer, OtherPlayer);
}

void AMyGameState::SetNumber(const FString& GeneratedNumber)
{
	Number = GeneratedNumber;
}

FString AMyGameState::GetNumber()
{
	return Number;
}

int32 AMyGameState::GetRemainTurn(const int32& PlayerId)
{
	return PlayerRemainTurn[PlayerId];
}

void AMyGameState::SetCurrentPlayer(AMyPlayerController* PlayerController)
{
	CurrentPlayer = PlayerController;
}

AMyPlayerController* AMyGameState::GetCurrentPlayer()
{
	return CurrentPlayer;
}

void AMyGameState::SetOtherPlayer(AMyPlayerController* PlayerController)
{
	OtherPlayer = PlayerController;
}

AMyPlayerController* AMyGameState::GetOtherPlayer()
{
	return OtherPlayer;
}
