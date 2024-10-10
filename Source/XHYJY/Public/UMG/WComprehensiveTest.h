// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UMG/BaseWidget.h"
#include "WComprehensiveTest.generated.h"

/**
 * 
 */
UCLASS()
class XHYJY_API UWComprehensiveTest : public UBaseWidget
{
	GENERATED_BODY()


protected:
	void InitTroubles();

	UFUNCTION()
	void InitQuestions();

	UFUNCTION()
	void ClickedButtonA();
	UFUNCTION()
	void ClickedButtonB();
	UFUNCTION()
	void ClickedButtonC();
	UFUNCTION()
	void ClickedButtonD();

	void CheckSelectRight(UTextBlock* CurButton, EAnswer ButtonType);
	
	void ButtonToWhite();
	
	void SelectRight();

	void SelectWrong();

	void ShowNextQue();
	

public:
	virtual void InitWidget() override;
	
protected:
	UPROPERTY(meta=(BindWidget))
	UBaseWidget* WBP_PersonTitle;
	UPROPERTY(meta=(BindWidget))
	UBaseWidget* WBP_Timing;
	UPROPERTY(meta=(BindWidget))
	UBaseWidget* WBP_States;
	
	UPROPERTY(meta=(BindWidget))
	UBorder* Border_BG;
	UPROPERTY(meta=(BindWidget))
	UHorizontalBox* HorizontalBox_Troubles;
	UPROPERTY(meta=(BindWidget))
	UImage* Image_Scan;
	UPROPERTY(meta=(BindWidget))
	UButton* Button_Troubles;

	UPROPERTY(Transient, meta=(BindWidgetAnim))
	UWidgetAnimation* QuestionShow;
	UPROPERTY(meta=(BindWidget))
	UTextBlock* TextBlock_TestTitle;
	UPROPERTY(meta=(BindWidget))
	UButton* Button_A;
	UPROPERTY(meta=(BindWidget))
	UTextBlock* TextBlock_A;
	UPROPERTY(meta=(BindWidget))
	UButton* Button_B;
	UPROPERTY(meta=(BindWidget))
	UTextBlock* TextBlock_B;
	UPROPERTY(meta=(BindWidget))
	UButton* Button_C;
	UPROPERTY(meta=(BindWidget))
	UTextBlock* TextBlock_C;
	UPROPERTY(meta=(BindWidget))
	UButton* Button_D;
	UPROPERTY(meta=(BindWidget))
	UTextBlock* TextBlock_D;
	
	int32 QuesNum = 0;
	
	bool bButtonAble = true;
	
};
