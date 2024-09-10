// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "UMG/BaseWidget.h"
#include "WRocketSelect.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FChangeModeDelegate, bool)

/**
 * 
 */
UCLASS()
class XHYJY_API UWRocketSelect : public UBaseWidget
{
	GENERATED_BODY()

protected:
	void InitRocketView();

	void CheckSelectRocket();
	
public:
	virtual void InitWidget() override;

	UFUNCTION(BlueprintCallable)
	void SelectRocketItem(UObject* objItem);

	UFUNCTION()
	void CreateLaunch();

protected:
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
	UHorizontalBox* ImageBox;
	
	uint8 SelectNum = 0;
	TArray<ERocketType> RightRocketArry;

public:
	FChangeModeDelegate ChangeMode;
	
};
