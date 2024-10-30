// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UMG/BaseWidget.h"
#include "WStates.generated.h"

/**
 * 
 */
UCLASS()
class XHYJY_API UWStates : public UBaseWidget
{
	GENERATED_BODY()

public:
	virtual void InitWidget() override;

protected:
	UPROPERTY(meta=(BindWidget))
	UTextBlock* HTQName;
	UPROPERTY(meta=(BindWidget))
	UTextBlock* Orbit;
	UPROPERTY(meta=(BindWidget))
	UTextBlock* RocketName;
	UPROPERTY(meta=(BindWidget))
	UTextBlock* FirePlace;

	UPROPERTY(meta=(BindWidget))
	UImage* Image_Rocket;
	UPROPERTY(meta=(BindWidget))
	UImage* Image_FirePlace;
	
};
