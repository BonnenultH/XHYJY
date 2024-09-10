// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UMG/BaseWidget.h"
#include "WRocketSelect.generated.h"

/**
 * 
 */
UCLASS()
class XHYJY_API UWRocketSelect : public UBaseWidget
{
	GENERATED_BODY()
	
public:
	virtual void InitWidget() override;

	UFUNCTION(BlueprintCallable)
	void SelectRocketItem(UObject* objItem);

	UFUNCTION()
	void CreateLaunch();

protected:
	void InitRocketView();

public:
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
	
	uint8 SelectNum = 0;

	
	
};
