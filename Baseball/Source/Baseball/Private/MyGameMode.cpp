#include "MyGameMode.h"
#include "MyGameState.h"
#include "MyPlayerController.h"

AMyGameMode::AMyGameMode()
{
	PlayerControllerClass = AMyPlayerController::StaticClass();
	GameStateClass = AMyGameState::StaticClass();

	TurnTime = 30.0f;
	GameStartDuration = 2.0f;
	GameOverDuration = 5.0f;
}

void AMyGameMode::BeginPlay()
{
	Super::BeginPlay();
	
	FTimerHandle TimerHandle;
	GetWorldTimerManager().SetTimer(TimerHandle, this, &AMyGameMode::InitializeGame, GameStartDuration, false);
}

void AMyGameMode::GotPlayerNumFromClient(const int32& PlayerId, const FString& PlayerNumString)
{
	if (AMyGameState* MyGameState = GetGameState<AMyGameState>())
	{
		if (AMyPlayerController* OtherPlayerController = MyGameState->GetOtherPlayer())
		{
			OtherPlayerController->ClientUpdateOtherPlayerNum(PlayerNumString);
		}
	}
}

void AMyGameMode::GotSubmitFromClient(const int32& PlayerId, const FString& PlayerNumString)
{
	if (AMyGameState* MyGameState = GetGameState<AMyGameState>())
	{
		if (MyGameState->GetCurrentPlayer()->GetUniqueID() != PlayerId)
		{
			return;
		}

		if (PlayerNumString[2] == ' ' || PlayerNumString[0] == PlayerNumString[1] || PlayerNumString[0] == PlayerNumString[2] || PlayerNumString[1] == PlayerNumString[2])
		{
			EndTurn(0, 0);
			return;
		}

		int32 StrikeCount = 0, BallCount = 0;
		FString Number = MyGameState->GetNumber();

		for (int32 i = 0; i < Number.Len(); i++)
		{
			if (Number[i] == PlayerNumString[i])
			{
				StrikeCount++;
				continue;
			}

			for (int32 j = 0; j < Number.Len(); j++)
			{
				if (Number[i] == PlayerNumString[j])
				{
					BallCount++;
					break;
				}
			}
		}

		EndTurn(StrikeCount, BallCount);
	}
}

void AMyGameMode::InitializeGame()
{
	if (AMyGameState* MyGameState = GetGameState<AMyGameState>())
	{
		MyGameState->SetNumber(GenerateNumber());

		for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
		{
			if (AMyPlayerController* PlayerController = Cast<AMyPlayerController>(*It))
			{
				PlayerController->ClientInitializeGame();
				int32 PlayerId = PlayerController->GetUniqueID();
				MyGameState->AddPlayerRemainTurn(PlayerId, 3);
				
				if (!MyGameState->GetCurrentPlayer())
				{
					MyGameState->SetCurrentPlayer(PlayerController);
				}

				else if (!MyGameState->GetOtherPlayer())
				{
					MyGameState->SetOtherPlayer(PlayerController);
				}
			}
		}

		if (FMath::RandBool())
		{
			MyGameState->SwapPlayerController();
		}
		
		PlayerStartTurn(MyGameState->GetCurrentPlayer());
	}
}

FString AMyGameMode::GenerateNumber()
{
	TArray<int32> Nums;

	while (Nums.Num() < 3)
	{
		int32 RandNum = FMath::RandRange(1, 9);

		if (!Nums.Contains(RandNum))
		{
			Nums.Add(RandNum);
		}
	}

	// 숫자들을 문자열로 변환하여 반환
	return FString::Printf(TEXT("%d%d%d"), Nums[0], Nums[1], Nums[2]);
}


void AMyGameMode::EndTurn(const int32& StrikeCount, const int32& BallCount)
{
	if (TurnTimer.IsValid())
	{
		GetWorldTimerManager().ClearTimer(TurnTimer);
	}

	if (AMyGameState* MyGameState = GetGameState<AMyGameState>())
	{
		bool bIsTurnStarted = false;
		AMyPlayerController* CurrentPlayerController = MyGameState->GetCurrentPlayer();
		AMyPlayerController* OtherPlayerController = MyGameState->GetOtherPlayer();

		if (CurrentPlayerController && OtherPlayerController)
		{
			CurrentPlayerController->ClientUpdateSubmitResult(StrikeCount, BallCount);
			OtherPlayerController->ClientUpdateSubmitResult(StrikeCount, BallCount);

			if (StrikeCount < 3)
			{
				PlayerEndTurn(CurrentPlayerController);
				bIsTurnStarted = PlayerStartTurn(OtherPlayerController);
			}
			else
			{
				CurrentPlayerController->ClientPlayerWin();
				OtherPlayerController->ClientPlayerLose();
				GameOver();
				return;
			}

			if (bIsTurnStarted == false)
			{
				CurrentPlayerController->ClientPlayerDraw();
				OtherPlayerController->ClientPlayerDraw();
				GameOver();
			}
		}
	}
}

bool AMyGameMode::PlayerStartTurn(AMyPlayerController* PlayerController)
{
	if (AMyGameState* MyGameState = GetGameState<AMyGameState>())
	{
		if (MyGameState->GetRemainTurn(PlayerController->GetUniqueID()) > 0)
		{
			PlayerController->ClientStartTurn();

			RemainTime = TurnTime;
			UpdateRemainTimePlayers();

			GetWorldTimerManager().SetTimer(
				TurnTimer,
				this,
				&AMyGameMode::TurnTimerLoop,
				1.0f,
				true
			);

			return true;
		}
	}
	return false;
}

void AMyGameMode::PlayerEndTurn(AMyPlayerController* PlayerController)
{
	if (AMyGameState* MyGameState = GetGameState<AMyGameState>())
	{
		const int32 PlayerId = PlayerController->GetUniqueID();
		MyGameState->DecreaseRemainTurn(PlayerId);

		PlayerController->ClientEndTurn(MyGameState->GetRemainTurn(PlayerId));

		MyGameState->SwapPlayerController();
	}
}

void AMyGameMode::TurnTimerLoop()
{
	if (RemainTime > 0)
	{
		RemainTime -= 1.0f;
		UpdateRemainTimePlayers();
	}
	else
	{
		GetWorldTimerManager().ClearTimer(TurnTimer);
		EndTurn();
	}
}

void AMyGameMode::UpdateRemainTimePlayers()
{
	for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
	{
		if (AMyPlayerController* PlayerController = Cast<AMyPlayerController>(*It))
		{
			PlayerController->ClientUpdateTimer(RemainTime);
		}
	}
}

void AMyGameMode::GameOver()
{
	FTimerHandle TimerHandle;
	GetWorldTimerManager().SetTimer(TimerHandle, this, &AMyGameMode::InitializeGame, GameOverDuration, false);
}
