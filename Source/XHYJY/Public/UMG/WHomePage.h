// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "UMG/BaseWidget.h"
#include "WHomePage.generated.h"

/**
 * 
 */
UCLASS()
class XHYJY_API UWHomePage : public UBaseWidget
{
	GENERATED_BODY()

protected:
	UFUNCTION()
	void CreatUserFile();
	
public:
	virtual void InitWidget() override;

public:
	UPROPERTY(meta=(BindWidget))
	UOverlay* Overlay_Start;
	
	UPROPERTY(meta=(BindWidget))
	UButton* StartButton;
};
