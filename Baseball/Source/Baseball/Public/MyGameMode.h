#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MyGameMode.generated.h"

class AMyPlayerController;

UCLASS()
class BASEBALL_API AMyGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditDefaultsOnly)
	float TurnTime;

	UPROPERTY(EditDefaultsOnly)
	float GameStartDuration;

	UPROPERTY(EditDefaultsOnly)
	float GameOverDuration;

	FTimerHandle TurnTimer;
	float RemainTime;

public:
	AMyGameMode();
	void virtual BeginPlay() override;

	void GotPlayerNumFromClient(const int32& PlayerId, const FString& PlayerNumString);
	void GotSubmitFromClient(const int32& PlayerId, const FString& PlayerNumString);

protected:
	void InitializeGame();
	FString GenerateNumber();
	void EndTurn(const int32& StrikeCount = 0, const int32& BallCount = 0);
	bool PlayerStartTurn(AMyPlayerController* PlayerController);
	void PlayerEndTurn(AMyPlayerController* PlayerController);
	void TurnTimerLoop();
	void UpdateRemainTimePlayers();
	void GameOver();
};
