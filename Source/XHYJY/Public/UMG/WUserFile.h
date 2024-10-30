// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UMG/BaseWidget.h"
#include "WUserFile.generated.h"

/**
 * 
 */
UCLASS()
class XHYJY_API UWUserFile : public UBaseWidget
{
	GENERATED_BODY()

protected:
	UFUNCTION()
	void CreatHistoryTasks();

	UFUNCTION()
	void CreatRules();

	UFUNCTION()
	void CreatTakeTasks();

public:
	virtual void InitWidget() override;

	void InitUserFileInfo();
	
protected:
	UPROPERTY(meta=(BindWidget))
	UButton* Button_Task;
	UPROPERTY(meta=(BindWidget))
	UButton* Button_History;
	UPROPERTY(meta=(BindWidget))
	UButton* Button_Rules;
	UPROPERTY(meta=(BindWidget))
	UTextBlock* IDName;
	UPROPERTY(meta=(BindWidget))
	UTextBlock* Gender;
	UPROPERTY(meta=(BindWidget))
	UTextBlock* Accomplishment;
	UPROPERTY(meta=(BindWidget))
	UTextBlock* Grades;
	UPROPERTY(meta=(BindWidget))
	UTextBlock* HTQNumbers;
};	
