// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UMG/BaseWidget.h"
#include "WPersonTitle.generated.h"

/**
 * 
 */
UCLASS()
class XHYJY_API UWPersonTitle : public UBaseWidget
{
	GENERATED_BODY()

protected:
	UFUNCTION()
	void UpdateProgressState();
	
public:
	virtual void InitWidget() override;

protected:
	TArray<UImage*> ImageArry;
	
	UPROPERTY(meta=(BindWidget))
	UTextBlock* IDName;
	UPROPERTY(meta=(BindWidget))
	UTextBlock* Accomplishment;
	UPROPERTY(meta=(BindWidget))
	UImage* Head;
	UPROPERTY(meta=(BindWidget))
	UImage* Progress1;
	UPROPERTY(meta=(BindWidget))
	UImage* Progress2;
	UPROPERTY(meta=(BindWidget))
	UImage* Progress3;
	UPROPERTY(meta=(BindWidget))
	UImage* Progress4;
	UPROPERTY(meta=(BindWidget))
	UImage* Progress5;
	UPROPERTY(meta=(BindWidget))
	UImage* Progress6;
	UPROPERTY(meta=(BindWidget))
	UImage* Progress7;
};
