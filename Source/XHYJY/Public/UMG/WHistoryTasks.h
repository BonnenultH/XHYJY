// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UMG/BaseWidget.h"
#include "WHistoryTasks.generated.h"

/**
 * 
 */
UCLASS()
class XHYJY_API UWHistoryTasks : public UBaseWidget
{
	GENERATED_BODY()

protected:
	UFUNCTION()
	void ReturnWidget();
	
public:
	virtual void InitWidget() override;

public:
	UPROPERTY(meta=(BindWidget))
	UButton* Button_Return;
	
	
};
