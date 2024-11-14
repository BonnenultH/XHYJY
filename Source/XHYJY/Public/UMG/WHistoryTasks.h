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
	
	UFUNCTION()
	void CreateTakeTasks();

	void InitHistoryView();

	UFUNCTION(BlueprintCallable)
	void OnSelectTask(UObject* Item);

	void InitRightInfo(UItemTask* ItemData);
	
public:
	virtual void InitWidget() override;
	

protected:
	UPROPERTY()
	class UWItemTask* CurItemWidget;
	
	UPROPERTY(meta=(BindWidget))
	UButton* Button_Return;
	UPROPERTY(meta=(BindWidget))
	UButton* Button_TakeTasks;

	UPROPERTY(meta=(BindWidget))
	UBaseWidget* WBP_PersonTitle;
	
	UPROPERTY(meta=(BindWidget))
	UTileView* TileView_History;
	UPROPERTY(meta=(BindWidget))
	UOverlay* Right;
	UPROPERTY(meta=(BindWidget))
	UImage* Image_HTQ;
	UPROPERTY(meta=(BindWidget))
	UTextBlock* HTQ_Name;
	UPROPERTY(meta=(BindWidget))
	UTextBlock* LockFunc;
	UPROPERTY(meta=(BindWidget))
	UTextBlock* HTQ_Description;
	UPROPERTY(meta=(BindWidget))
	UTextBlock* finishtime;
	UPROPERTY(meta=(BindWidget))
	UTextBlock* TextBlock_Grade;
	UPROPERTY(meta=(BindWidget))
	UTextBlock* TextBlock_UnlockNum;
	
	
};
