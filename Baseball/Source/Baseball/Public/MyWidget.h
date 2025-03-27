#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MyWidget.generated.h"

class UHorizontalBox;
class UTextBlock;
class UButton;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnPlayerTextChanged, const FString&)
DECLARE_MULTICAST_DELEGATE_OneParam(FOnPlayerTextSubmitted, const FString&)

UCLASS()
class BASEBALL_API UMyWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	FOnPlayerTextChanged OnPlayerTextChanged;
	FOnPlayerTextSubmitted OnPlayerTextSubmitted;

private:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* PlayerNumText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* OtherNumText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* ResultText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* GameResultText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* TimerText;

	UPROPERTY(meta = (BindWidget))
	UButton* SubmitButton;

	UPROPERTY(meta = (BindWidget))
	UButton* BackspaceButton;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* RemainTurnBox;

	UPROPERTY(meta = (BindWidget))
	UButton* NumButton1;

	UPROPERTY(meta = (BindWidget))
	UButton* NumButton2;

	UPROPERTY(meta = (BindWidget))
	UButton* NumButton3;

	UPROPERTY(meta = (BindWidget))
	UButton* NumButton4;

	UPROPERTY(meta = (BindWidget))
	UButton* NumButton5;

	UPROPERTY(meta = (BindWidget))
	UButton* NumButton6;

	UPROPERTY(meta = (BindWidget))
	UButton* NumButton7;

	UPROPERTY(meta = (BindWidget))
	UButton* NumButton8;

	UPROPERTY(meta = (BindWidget))
	UButton* NumButton9;

	FString PlayerNumString;

public:
	virtual void NativeConstruct() override;
	void InitializeWidget();
	void UpdateOtherPlayerNum(const FText& Text);
	void UpdateOtherPlayerNum(const FString& String);
	void UpdatePlayerNum(const FText& Text);
	void UpdatePlayerNum(const FString& String);
	void UpdateResultText(const int32& StrikeCount, const int32& BallCount);
	void UpdateRemainTurn(const int32& RemainTurn);
	void DisableButtons();
	void EnableButtons();
	void InitializePlayerNum();
	void UpdateGameResultText(const FText& Text);
	void UpdateGameResultText(const FString& Text);
	void UpdateTimerText(const int32& RemainTime);

private:
	UFUNCTION()
	void OnClickedSubmitButton();
	UFUNCTION()
	void OnClickedBackspaceButton();
	UFUNCTION()
	void OnClickedNumButton1();
	UFUNCTION()
	void OnClickedNumButton2();
	UFUNCTION()
	void OnClickedNumButton3();
	UFUNCTION()
	void OnClickedNumButton4();
	UFUNCTION()
	void OnClickedNumButton5();
	UFUNCTION()
	void OnClickedNumButton6();
	UFUNCTION()
	void OnClickedNumButton7();
	UFUNCTION()
	void OnClickedNumButton8();
	UFUNCTION()
	void OnClickedNumButton9();

	void AddPlayerNum(const int32 Num);

	int32 TotalTurn;
	int32 CurrentTurn;
};
