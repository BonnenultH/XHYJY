// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UMG/BaseWidget.h"
#include "WHoisting.generated.h"

/**
 * 
 */
UCLASS()
class XHYJY_API UWHoisting : public UBaseWidget
{
	GENERATED_BODY()

protected:

	void LoadLevelAssets();
public:
	virtual void InitWidget() override;

protected:
	UPROPERTY(meta=(BindWidget))
	UBaseWidget* WBP_PersonTitle;
	UPROPERTY(meta=(BindWidget))
	UBaseWidget* WBP_Timing;
	UPROPERTY(meta=(BindWidget))
	UBaseWidget* WBP_States;
};
