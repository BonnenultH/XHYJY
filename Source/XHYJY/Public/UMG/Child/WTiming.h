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
	
public:
	virtual void InitWidget() override;
	
public:
	UPROPERTY(meta=(BindWidget))
	UTextBlock* Minute;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* Second;
};
