// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UMG/BaseWidget.h"
#include "WTakeTasks.generated.h"

/**
 * 
 */
UCLASS()
class XHYJY_API UWTakeTasks : public UBaseWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	void UpdateProgressState();
	
public:
	virtual void InitWidget() override;

	UFUNCTION()
	void CreateOrbits();

protected:
	UPROPERTY(meta=(BindWidget))
	UButton* Button_Ok;

	UPROPERTY(meta=(BindWidget))
	UBaseWidget* WBP_PersonTitle;
	
	UPROPERTY(meta=(BindWidget))
	UBaseWidget* WBP_Timing;

	float Interval;
};
