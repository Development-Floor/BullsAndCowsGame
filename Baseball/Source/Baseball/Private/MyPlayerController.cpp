#include "MyPlayerController.h"
#include "MyGameMode.h"
#include "MyGameState.h"
#include "MyWidget.h"

void AMyPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (IsLocalController())
	{
		if (GameWidget)
		{
			GameWidget->AddToViewport();
			GameWidget->SetVisibility(ESlateVisibility::Visible);
			GameWidget->OnPlayerTextChanged.AddUObject(this, &AMyPlayerController::ServerUpdatePlayerNum);
			GameWidget->OnPlayerTextSubmitted.AddUObject(this, &AMyPlayerController::ServerSubmitPlayerNum);
		}
	}
}

void AMyPlayerController::UpdateRemainTurn(const int32& RemainTurn)
{
	if (GameWidget)
	{
		GameWidget->UpdateRemainTurn(RemainTurn);
	}
}

void AMyPlayerController::ClientUpdateTimer_Implementation(const int32& RemainTime)
{
	if (GameWidget)
	{
		GameWidget->UpdateTimerText(RemainTime);
	}
}

void AMyPlayerController::ClientInitializeGame_Implementation()
{
	if (GameWidget)
	{
		GameWidget->InitializeWidget();
	}
}

void AMyPlayerController::ClientPlayerDraw_Implementation()
{
	if (GameWidget)
	{
		GameWidget->UpdateGameResultText("DRAW");
	}
}

void AMyPlayerController::ClientPlayerWin_Implementation()
{
	if (GameWidget)
	{
		GameWidget->UpdateGameResultText("WIN");
	}
}

void AMyPlayerController::ClientPlayerLose_Implementation()
{
	if (GameWidget)
	{
		GameWidget->UpdateGameResultText("LOSE");
	}
}

void AMyPlayerController::ClientUpdateSubmitResult_Implementation(const int32& StrikeCount, const int32& BallCount)
{
	if (GameWidget)
	{
		GameWidget->UpdateResultText(StrikeCount, BallCount);
	}
}

void AMyPlayerController::ClientEndTurn_Implementation(const int32 CurrentTurn)
{
	if (GameWidget)
	{
		GameWidget->DisableButtons();
		UpdateRemainTurn(CurrentTurn);
	}
}

void AMyPlayerController::ClientStartTurn_Implementation()
{
	if (GameWidget)
	{
		GameWidget->InitializePlayerNum();
		GameWidget->EnableButtons();
	}
}


void AMyPlayerController::ServerSubmitPlayerNum_Implementation(const FString& PlayerNumString)
{
	if (AMyGameMode* GameMode = Cast<AMyGameMode>(GetWorld()->GetAuthGameMode()))
	{
		GameMode->GotSubmitFromClient(GetUniqueID(), PlayerNumString);
	}
}

void AMyPlayerController::ServerUpdatePlayerNum_Implementation(const FString& PlayerNumString)
{
	if (AMyGameMode* GameMode = Cast<AMyGameMode>(GetWorld()->GetAuthGameMode()))
	{
		GameMode->GotPlayerNumFromClient(GetUniqueID(), PlayerNumString);
	}
}

void AMyPlayerController::ClientUpdateOtherPlayerNum_Implementation(const FString& PlayerNumString)
{
	if (GameWidget)
	{
		GameWidget->UpdateOtherPlayerNum(PlayerNumString);
	}
}