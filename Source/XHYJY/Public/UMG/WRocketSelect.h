// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "UMG/BaseWidget.h"
#include "WRocketSelect.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FChangeModeDelegate, ERSMode)

/**
 * 
 */
UCLASS()
class XHYJY_API UWRocketSelect : public UBaseWidget
{
	GENERATED_BODY()

protected:
	void InitRocketView();

	void InitHintInfos();
	
	UFUNCTION()
	void CheckSelectRocket();

	void SelectRocketError();

	void SelectRocketRight();

	void ReInitialRocketView();

	void SelectPRocketError();
	
	void CreateLaunch();

	void PlayWrongSound();
	
	UFUNCTION(BlueprintCallable)
	void SelectRocketItem(UObject* ObjItem);

public:
	virtual void InitWidget() override;
	
	ERSMode GetCurMode()
	{
		return CurMode;
	}
	
protected:
	UPROPERTY(meta=(BindWidget))
	UCanvasPanel* CanvasPanel;
	UPROPERTY(meta=(BindWidget))
	UWidgetSwitcher* SwitchLeft;
	UPROPERTY(meta=(BindWidget))
	UWidgetSwitcher* SwitchRight;
	
	UPROPERTY(meta=(BindWidget))
	UBaseWidget* WBP_PersonTitle;
	UPROPERTY(meta=(BindWidget))
	UBaseWidget* WBP_Timing;
	UPROPERTY(meta=(BindWidget))
	UBaseWidget* WBP_States;

	UPROPERTY(meta=(BindWidget))
	UListView* RocketListView;
	UPROPERTY(meta=(BindWidget))
	UButton* Button_Ok;
	UPROPERTY(meta=(BindWidget))
	UTextBlock* Chosen;
	UPROPERTY(meta=(BindWidget))
	UTextBlock* ToChosen;
	UPROPERTY(meta=(BindWidget))
	UTextBlock* TextBlock_CapacityRange;
	UPROPERTY(meta=(BindWidget))
	UTextBlock* TextBlock_HintInfo;
	
	
	UPROPERTY(meta=(BindWidget))
	UHorizontalBox* SeletedBox;
	
	UPROPERTY(Transient, meta=(BindWidgetAnim))
	UWidgetAnimation* ShowTwoSlide;

	TArray<UImage*> SeletedBoxArry;
	TArray<FTaskRocket> RightRocketArry;
	TArray<UItemRocket*> SelectedRocketArry;
	TMap<ERSMode, FString> HintInfoMap;
	FTimerHandle TimerHandle;

	ERSMode CurMode = ERSMode::ERSM_Capacity;

public:
	FChangeModeDelegate ChangeMode;
	
};
