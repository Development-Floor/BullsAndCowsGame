#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "MyGameState.generated.h"

class AMyPlayerController;

UCLASS()
class BASEBALL_API AMyGameState : public AGameStateBase
{
	GENERATED_BODY()
	
private:
	FString Number;
	AMyPlayerController* CurrentPlayer;
	AMyPlayerController* OtherPlayer;
	TMap<int32, int32> PlayerRemainTurn;

public:
	void AddPlayerRemainTurn(const int32& PlayerId, const int32& TurnCount);
	void DecreaseRemainTurn(const int32& PlayerId);
	void SwapPlayerController();
	void SetNumber(const FString& GeneratedNumber);
	FString GetNumber();
	int32 GetRemainTurn(const int32& PlayerId);
	void SetCurrentPlayer(AMyPlayerController* PlayerController);
	AMyPlayerController* GetCurrentPlayer();
	void SetOtherPlayer(AMyPlayerController* PlayerController);
	AMyPlayerController* GetOtherPlayer();
};
