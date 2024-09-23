// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GM/VDPawn.h"
#include "Manager/ResourceManager.h"
#include "Manager/UIManager.h"
#include "Manager/SceneManager.h"
#include "Components/Overlay.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Components/TileView.h"
#include "Components/VerticalBox.h"
#include "Components/Border.h"
#include "Animation/WidgetAnimation.h"
#include "LevelSequencePlayer.h"
#include "Components/ProgressBar.h"
#include "Components/HorizontalBox.h"
#include "Components/CanvasPanel.h"
#include "Components/WidgetSwitcher.h"
#include "BaseWidget.generated.h"


 
UCLASS()
class XHYJY_API UBaseWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void InitWidget();

	virtual void CountErrorNums();

public:
	UPROPERTY()
	AVDPawn* VDPawn;
	
	UPROPERTY()
	AResourceManager* ResourceManager;

	UPROPERTY()
	AUIManager* UIManager;

	UPROPERTY()
	ASceneManager* SceneManager;
	
	EWidgetType ReturnWidgetType;

	int32 ErrorNums = 0;
};
