// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UMG/BaseWidget.h"
#include "WHoisting.generated.h"

/**
 * 
 */
UCLASS()
class XHYJY_API UWHoisting : public UBaseWidget
{
	GENERATED_BODY()

protected:
	void InitDiagram();

	void InitRocketPartInfos();
	
	void LoadLevelAssets();

	UFUNCTION()
	void PlayStartHoist();
	
	UFUNCTION()
	void PlayOperateInstructions();

	UFUNCTION()
	void PlayReverseOperateIns();

	UFUNCTION()
	void PlayErrorPart();

	void GoHoisting();
	
public:
	virtual void InitWidget() override;

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
	UTextBlock* RocketPartName;
	UPROPERTY(meta=(BindWidget))
	UTextBlock* TextBlock_RocketPartInfo;
	UPROPERTY(meta=(BindWidget))
	UTextBlock* Loadoutprogress;

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
	
	TArray<AActor*> MyPlayerCameras;

	UVerticalBoxSlot* ImageSlot;
	UVerticalBoxSlot* TextSlot;

	TMap<ERocketPartsType, FString> RocketPartInfosMap;

	TMap<EFirePlace, FName> FirePlaceMap;
	
};
