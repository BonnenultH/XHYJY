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
	
protected:
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	void InitTaskView();
	
	UFUNCTION(BlueprintCallable)
	void OnSelectTask(UObject* Item);

	void InitRightInfo(UItemTask* ItemData);
	
public:
	virtual void InitWidget() override;

	UFUNCTION()
	void CreateOrbits();

protected:
	UPROPERTY()
	class UWItemTask* CurItemWidget;
	
	UPROPERTY(meta=(BindWidget))
	UBaseWidget* WBP_PersonTitle;
	UPROPERTY(meta=(BindWidget))
	UBaseWidget* WBP_Timing;

	UPROPERTY(meta=(BindWidget))
	UTileView* TaskView;
	UPROPERTY(meta=(BindWidget))
	UButton* Button_Ok;
	UPROPERTY(meta=(BindWidget))
	UVerticalBox* Right;
	UPROPERTY(meta=(BindWidget))
	UImage* RightImage;
	UPROPERTY(meta=(BindWidget))
	UTextBlock* RightName;
	UPROPERTY(meta=(BindWidget))
	UTextBlock* RightForAppFunc;
	UPROPERTY(meta=(BindWidget))
	UTextBlock* RightDes;
	
	
	FTimerHandle TimerHandle;
};
