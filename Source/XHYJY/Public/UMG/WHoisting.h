// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UMG/BaseWidget.h"
#include "WHoisting.generated.h"

/**
 * 
 */
DECLARE_DELEGATE(FSelectAnimEnd)

UCLASS()
class XHYJY_API UWHoisting : public UBaseWidget
{
	GENERATED_BODY()

protected:
	void InitDiagram();

	void InitRocketPartInfos();
	
	UFUNCTION()
	void OnLevelLoaded();

	UFUNCTION()
	void PlayStartHoist();
	
	UFUNCTION()
	void PlayOperateInstructions();

	UFUNCTION()
	void PlayReverseOperateIns();
	
	void CameraMove();

	void DelayAssembly();

	UFUNCTION()
	void PlaySelectPartReverseAnim();

	UFUNCTION()
	void PlayErrorPart();

	UFUNCTION()
	void GoHoisting();

	void InitDelegateSingle();

	UFUNCTION()
	void DispearCurSelect();
	
	UFUNCTION()
	void GetRocketSingleInfo(AA_SinglePart* SinglePart);

	UFUNCTION()
	void ClickedAssembly();

	UFUNCTION()
	void GoTest();

public:
	virtual void InitWidget() override;
	
	void HoistingProgress();

	void PlaySelectPartAnim();

	void PlaySelectWrong();

	void PlaySelectRight();

	int32 GetCurProgress()
	{
		return CurProgress;
	}

protected:
	UPROPERTY(meta=(BindWidget))
	UBaseWidget* WBP_PersonTitle;
	UPROPERTY(meta=(BindWidget))
	UBaseWidget* WBP_Timing;
	UPROPERTY(meta=(BindWidget))
	UBaseWidget* WBP_States;

	UPROPERTY(meta=(BindWidget))
	UCanvasPanel* Hoisting;
	UPROPERTY(meta=(BindWidget))
	UVerticalBox* VerticalBox_PartImage;
	UPROPERTY(meta=(BindWidget))
	UVerticalBox* VerticalBox_PartText;
	
	UPROPERTY(meta=(BindWidget))
	UButton* Button_StartHoist;
	UPROPERTY(meta=(BindWidget))
	UButton* Button_ClickAssembly;
	UPROPERTY(meta=(BindWidget))
	UButton* Button_OperateInstructions;
	UPROPERTY(meta=(BindWidget))
	UButton* Button_ok;
	UPROPERTY(meta=(BindWidget))
	UButton* Button_close;
	UPROPERTY(meta=(BindWidget))
	UButton* Button_StartSelectPart;
	UPROPERTY(meta=(BindWidget))
	UButton* Button_CurOk;
	UPROPERTY(meta=(BindWidget))
	UButton* Button_GoTest;
	
	
	UPROPERTY(meta=(BindWidget))
	UTextBlock* RocketPartName;
	UPROPERTY(meta=(BindWidget))
	UTextBlock* TextBlock_RocketPartInfo;
	UPROPERTY(meta=(BindWidget))
	UTextBlock* Loadoutprogress;
	UPROPERTY(meta=(BindWidget))
	UTextBlock* TextBlock_Part;
	UPROPERTY(meta=(BindWidget))
	UTextBlock* TextBlock_CurPart;
	UPROPERTY(meta=(BindWidget))
	UTextBlock* TextBlock_SuccessPart;
	

	UPROPERTY(meta=(BindWidget))
	UProgressBar* ProgressBar;
	UPROPERTY(Transient, meta=(BindWidgetAnim))
	UWidgetAnimation* Instructions;
	UPROPERTY(Transient, meta=(BindWidgetAnim))
	UWidgetAnimation* Tests;
	UPROPERTY(Transient, meta=(BindWidgetAnim))
	UWidgetAnimation* ErrorPartSelection;
	UPROPERTY(Transient, meta=(BindWidgetAnim))
	UWidgetAnimation* StartHoist;
	UPROPERTY(Transient, meta=(BindWidgetAnim))
	UWidgetAnimation* StartSelectPartAnim;
	UPROPERTY(Transient, meta=(BindWidgetAnim))
	UWidgetAnimation* CurSelectPartAnim;
	UPROPERTY(Transient, meta=(BindWidgetAnim))
	UWidgetAnimation* SuccessHoist;

	FDiagramUITable* UIDiagram;
	TMap<ERocketPartsType, FString> RocketPartInfosMap;
	TMap<EFirePlace, FName> FirePlaceMap;
	FSingleRocketPart CurSingleRocketPart;
	float CurProgress = 0;
	UPROPERTY()
	UOverlay* Overlay;
	TArray<UImage*> PartImageArry;
	TArray<UImage*> PartTextArry;

public:
	FSelectAnimEnd OnAnimEnd;
};
