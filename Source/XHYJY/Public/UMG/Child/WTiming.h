// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UMG/BaseWidget.h"
#include "WTiming.generated.h"

/**
 * 
 */
UCLASS()
class XHYJY_API UWTiming : public UBaseWidget
{
	GENERATED_BODY()
protected:
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	void UpdateTime();

	FString TimeFormat(float time);

public:
	virtual void InitWidget() override;

public:
	UPROPERTY(meta=(BindWidget))
	UTextBlock* Minute;
	UPROPERTY(meta=(BindWidget))
	UTextBlock* Second;
	UPROPERTY(meta=(BindWidget))
	UTextBlock* colon;

	FString _Minute;
	FString _Second;
};
