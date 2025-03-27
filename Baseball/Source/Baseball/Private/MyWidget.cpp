#include "MyWidget.h"
#include "Blueprint/WidgetTree.h"
#include "Components/Button.h"
#include "Components/HorizontalBox.h"
#include "Components/TextBlock.h"

void UMyWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (SubmitButton)SubmitButton->OnClicked.AddDynamic(this, &UMyWidget::OnClickedSubmitButton);
	if (BackspaceButton)BackspaceButton->OnClicked.AddDynamic(this, &UMyWidget::OnClickedBackspaceButton);
	if (NumButton1)NumButton1->OnClicked.AddDynamic(this, &UMyWidget::OnClickedNumButton1);
	if (NumButton2)NumButton2->OnClicked.AddDynamic(this, &UMyWidget::OnClickedNumButton2);
	if (NumButton3)NumButton3->OnClicked.AddDynamic(this, &UMyWidget::OnClickedNumButton3);
	if (NumButton4)NumButton4->OnClicked.AddDynamic(this, &UMyWidget::OnClickedNumButton4);
	if (NumButton5)NumButton5->OnClicked.AddDynamic(this, &UMyWidget::OnClickedNumButton5);
	if (NumButton6)NumButton6->OnClicked.AddDynamic(this, &UMyWidget::OnClickedNumButton6);
	if (NumButton7)NumButton7->OnClicked.AddDynamic(this, &UMyWidget::OnClickedNumButton7);
	if (NumButton8)NumButton8->OnClicked.AddDynamic(this, &UMyWidget::OnClickedNumButton8);
	if (NumButton9)NumButton9->OnClicked.AddDynamic(this, &UMyWidget::OnClickedNumButton9);

	InitializeWidget();

	TotalTurn = 3;
	CurrentTurn = 0;
}

void UMyWidget::InitializeWidget()
{
	CurrentTurn = 0;

	GameResultText->SetText(FText::FromString(""));

	InitializePlayerNum();
	UpdateOtherPlayerNum(PlayerNumString);
	DisableButtons();
	UpdateResultText(0, 0);
	UpdateRemainTurn(3);
	ResultText->SetText(FText::FromString("Start"));
	TimerText->SetText(FText::FromString("99"));
}

void UMyWidget::UpdateOtherPlayerNum(const FText& Text)
{
	if (OtherNumText)
	{
		OtherNumText->SetText(Text);
	}
}

void UMyWidget::UpdateOtherPlayerNum(const FString& String)
{
	UpdateOtherPlayerNum(FText::FromString(String));
}

void UMyWidget::UpdatePlayerNum(const FText& Text)
{
	if (PlayerNumText)
	{
		PlayerNumText->SetText(Text);
	}
	//OnPlayerTextChanged.Broadcast(Text.ToString());
}

void UMyWidget::UpdatePlayerNum(const FString& String)
{
	UpdatePlayerNum(FText::FromString(String));
}

void UMyWidget::UpdateResultText(const int32& StrikeCount, const int32& BallCount)
{
	if (ResultText)
	{
		if (StrikeCount == 0 && BallCount == 0)
		{
			ResultText->SetText(FText::FromString("OUT"));
		}
		else
		{
			ResultText->SetText(FText::Format(FText::FromString("{0}S{1}B"), FText::AsNumber(StrikeCount), FText::AsNumber(BallCount)));
		}
	}
}

void UMyWidget::UpdateRemainTurn(const int32& RemainTurn)
{
	if (RemainTurnBox)
	{
		CurrentTurn++;

		if (CurrentTurn > TotalTurn)
		{
			RemainTurnBox->SetText(FText::FromString("OUT"));
		}
		else
		{
			RemainTurnBox->SetText(FText::Format(FText::FromString("{0} Turn"), FText::AsNumber(CurrentTurn)));
		}
	}
}

void UMyWidget::UpdateTimerText(const int32& RemainTime)
{
	if (TimerText)
	{
		TimerText->SetText(FText::AsNumber(RemainTime));
	}
}

void UMyWidget::DisableButtons()
{
	if (WidgetTree)
	{
		TArray<UWidget*> AllWidgets;
		WidgetTree->GetAllWidgets(AllWidgets);

		for (UWidget* Widget : AllWidgets)
		{
			if (UButton* Button = Cast<UButton>(Widget))
			{
				Button->SetIsEnabled(false);
			}
		}
	}
}

void UMyWidget::EnableButtons()
{
	if (WidgetTree)
	{
		TArray<UWidget*> AllWidgets;
		WidgetTree->GetAllWidgets(AllWidgets);

		for (UWidget* Widget : AllWidgets)
		{
			if (UButton* Button = Cast<UButton>(Widget))
			{
				Button->SetIsEnabled(true);
			}
		}
	}
}

void UMyWidget::OnClickedSubmitButton()
{
	OnPlayerTextChanged.Broadcast(PlayerNumText->GetText().ToString());
	DisableButtons();
	OnPlayerTextSubmitted.Broadcast(PlayerNumString);
}

void UMyWidget::OnClickedBackspaceButton()
{
	for (int i = 2; i >= 0; i--)
	{
		if (PlayerNumString[i] != ' ')
		{
			PlayerNumString[i] = ' ';
			break;
		}
	}
	UpdatePlayerNum(PlayerNumString);
}

void UMyWidget::OnClickedNumButton1()
{
	AddPlayerNum(1);
}

void UMyWidget::OnClickedNumButton2()
{
	AddPlayerNum(2);
}

void UMyWidget::OnClickedNumButton3()
{
	AddPlayerNum(3);
}

void UMyWidget::OnClickedNumButton4()
{
	AddPlayerNum(4);
}

void UMyWidget::OnClickedNumButton5()
{
	AddPlayerNum(5);
}

void UMyWidget::OnClickedNumButton6()
{
	AddPlayerNum(6);
}

void UMyWidget::OnClickedNumButton7()
{
	AddPlayerNum(7);
}

void UMyWidget::OnClickedNumButton8()
{
	AddPlayerNum(8);
}

void UMyWidget::OnClickedNumButton9()
{
	AddPlayerNum(9);
}

void UMyWidget::AddPlayerNum(const int32 Num)
{
	for (int i = 0; i < 3; i++)
	{
		if (PlayerNumString[i] == ' ')
		{
			PlayerNumString[i] = Num + '0';
			break;
		}
	}
	UpdatePlayerNum(PlayerNumString);
}

void UMyWidget::InitializePlayerNum()
{
	PlayerNumString = "   ";
	UpdatePlayerNum(PlayerNumString);
}

void UMyWidget::UpdateGameResultText(const FText& Text)
{
	GameResultText->SetText(Text);
}

void UMyWidget::UpdateGameResultText(const FString& Text)
{
	UpdateGameResultText(FText::FromString(Text));
}
