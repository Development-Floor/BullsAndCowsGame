#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerController.generated.h"

class UMyWidget;

UCLASS()
class BASEBALL_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditAnywhere, Category = "Widget")
	UMyWidget* GameWidget;

public:
	virtual void BeginPlay() override;
	void UpdateRemainTurn(const int32& RemainTurn);

public:
	UFUNCTION(Client, Unreliable)
	void ClientUpdateOtherPlayerNum(const FString& PlayerNumString);

	UFUNCTION(Client, Unreliable)
	void ClientUpdateTimer(const int32& RemainTime);

	UFUNCTION(Client, Reliable)
	void ClientUpdateSubmitResult(const int32& StrikeCount, const int32& BallCount);

	UFUNCTION(Client, Reliable)
	void ClientStartTurn();

	UFUNCTION(Client, Reliable)
	void ClientEndTurn(const int32 CurrentTurn);

	UFUNCTION(Client, Reliable)
	void ClientPlayerLose();

	UFUNCTION(Client, Reliable)
	void ClientPlayerWin();

	UFUNCTION(Client, Reliable)
	void ClientPlayerDraw();

	UFUNCTION(Client, Reliable)
	void ClientInitializeGame();

private:
	UFUNCTION(Server, Unreliable)
	void ServerUpdatePlayerNum(const FString& PlayerNumString);

	UFUNCTION(Server, Reliable)
	void ServerSubmitPlayerNum(const FString& PlayerNumString);
};
