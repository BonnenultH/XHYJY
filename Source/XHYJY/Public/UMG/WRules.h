// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UMG/BaseWidget.h"
#include "WRules.generated.h"

/**
 * 
 */
UCLASS()
class XHYJY_API UWRules : public UBaseWidget
{
	GENERATED_BODY()

public:
	virtual void InitWidget() override;

	UFUNCTION()
	void ReturnUserFile();

	UFUNCTION()
	void CreateTakeTasks();

public:
	UPROPERTY(meta=(BindWidget))
	UButton* Button_Return;

	UPROPERTY(meta=(BindWidget))
	UButton* Button_TakeTasks;
};
