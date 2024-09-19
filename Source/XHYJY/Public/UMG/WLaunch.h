// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UMG/BaseWidget.h"
#include "WLaunch.generated.h"

/**
 * 
 */
UCLASS()
class XHYJY_API UWLaunch : public UBaseWidget
{
	GENERATED_BODY()

protected:
	UFUNCTION()
	void ClickedJQ();

	UFUNCTION()
	void ClickedTY();
	
	UFUNCTION()
	void ClickedXC();
	
	UFUNCTION()
	void ClickedWC();

	UFUNCTION()
	void CreateAnim();

	UFUNCTION()
	void WrongAgain();

	UFUNCTION()
	void CreateHoisting();

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
	UImage* ImageBG;
	
	UPROPERTY(meta=(BindWidget))
	UButton* Button_JQ;
	UPROPERTY(meta=(BindWidget))
	UButton* Button_XC;
	UPROPERTY(meta=(BindWidget))
	UButton* Button_WC;
	UPROPERTY(meta=(BindWidget))
	UButton* Button_TY;

	UPROPERTY(meta=(BindWidget))
	UButton* Button_Ok;
	UPROPERTY(meta=(BindWidget))
	UButton* Button_Again;
	UPROPERTY(meta=(BindWidget))
	UButton* Button_GoHoist;

	UPROPERTY(Transient, meta=(BindWidgetAnim))
	UWidgetAnimation* RightAnswer;
	UPROPERTY(Transient, meta=(BindWidgetAnim))
	UWidgetAnimation* WrongAnswer;

	
	
};
