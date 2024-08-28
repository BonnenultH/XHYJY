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
public:
	virtual void InitWidget() override;

	UFUNCTION()
	void CreateOrbits();

public:
	UPROPERTY(meta=(BindWidget))
	UButton* Button_Ok;
};
