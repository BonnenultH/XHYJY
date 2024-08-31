// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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

public:
	UPROPERTY(meta=(BindWidget))
	UBaseWidget* WBP_PersonTitle;
	
};
