// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UMG/BaseWidget.h"
#include "WBookLaunch.generated.h"

/**
 * 
 */
UCLASS()
class XHYJY_API UWBookLaunch : public UBaseWidget
{
	GENERATED_BODY()

public:
	virtual void InitWidget() override;


protected:
	UPROPERTY(meta=(BindWidget))
	UBaseWidget* WBP_PersonTitle;
	

	UPROPERTY(meta=(BindWidget))
	UTextBlock* TextBlock_Time;
	UPROPERTY(meta=(BindWidget))
	UTextBlock* TextBlock_HTQ;
	UPROPERTY(meta=(BindWidget))
	UTextBlock* TextBlock_Rocket;
	UPROPERTY(meta=(BindWidget))
	UTextBlock* TextBlock_Fireplace;

	UPROPERTY(meta=(BindWidget))
	UImage* Image_Level;
	

	
	
	
};
