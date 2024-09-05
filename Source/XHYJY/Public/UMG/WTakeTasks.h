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
	void InitTaskView();
	
	UFUNCTION(BlueprintCallable)
	void OnSelectTask(UObject* Item);

	void InitRightInfo(UItemTask* ItemData);

	UFUNCTION()
	void OnSelectedSatellite();

	UFUNCTION()
	void OnSelectedNavigation();

	UFUNCTION()
	void OnSelectedCommunication();

	UFUNCTION()
	void OnSelectedRemoteSensing();

	UFUNCTION()
	void OnSelectedScientificExploration();
	
	UFUNCTION()
	void OnSelectedSpaceship();

	UFUNCTION()
	void OnSelectedDeepSpaceProbes();
	
	UFUNCTION()
	void OnSelectedSpaceStation();

	UFUNCTION()
    void PlayPoppingAni();

	UFUNCTION()
	void CreateOrbits();

public:
	virtual void InitWidget() override;



protected:
	UPROPERTY()
	class UWItemTask* CurItemWidget;
	
	UPROPERTY(meta=(BindWidget))
	UBaseWidget* WBP_PersonTitle;
	UPROPERTY(meta=(BindWidget))
	UBaseWidget* WBP_Timing;
	
	UPROPERTY(meta=(BindWidget))
	UButton* Button_Satellite;
	UPROPERTY(meta=(BindWidget))
	UVerticalBox* Satellite;

	UPROPERTY(meta=(BindWidget))
	UButton* Button_Navigation;
	UPROPERTY(meta=(BindWidget))
	UButton* Button_Communication;
	UPROPERTY(meta=(BindWidget))
	UButton* Button_RemoteSensing;
	UPROPERTY(meta=(BindWidget))
	UButton* Button_ScientificExploration;
	
	UPROPERTY(meta=(BindWidget))
	UTileView* TaskView;
	UPROPERTY(meta=(BindWidget))
	UButton* Button_Spaceship;
	UPROPERTY(meta=(BindWidget))
	UButton* Button_DeepSpaceProbes;
	UPROPERTY(meta=(BindWidget))
	UButton* Button_SpaceStation;
	
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

	UPROPERTY(Transient, meta=(BindWidgetAnim))
	UWidgetAnimation* Ani_showInfo;
	UPROPERTY(meta=(BindWidget))
	UImage* HTQ_Image;
	UPROPERTY(meta=(BindWidget))
	UTextBlock* HTQName;
	UPROPERTY(meta=(BindWidget))
	UTextBlock* LockFunc;
	UPROPERTY(meta=(BindWidget))
	UTextBlock* HTQ_Description;
	UPROPERTY(meta=(BindWidget))
	UButton* Button_StartOrbits;
	UPROPERTY(meta=(BindWidget))
	UButton* Button_Reselect;
	
	FTimerHandle TimerHandle;

	TArray<FTaskTable*> AllTaskArry;
};
