// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GM/VDPawn.h"
#include "Manager/ResourceManager.h"
#include "Manager/UIManager.h"
#include "BaseWidget.generated.h"


 
UCLASS()
class XHYJY_API UBaseWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void InitWidget();

public:
	UPROPERTY()
	AVDPawn* VDPawn;
	
	UPROPERTY()
	AResourceManager* ResourceManager;

	UPROPERTY()
	AUIManager* UIManager;
	
};
