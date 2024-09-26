// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Manager/BaseManager.h"
#include "SceneManager.generated.h"

/**
 * 
 */
UCLASS()
class XHYJY_API ASceneManager : public ABaseManager
{
	GENERATED_BODY()

public:
	void InitManager() override;

	void SwitchViewByHoist();

	void InitHoistRocketParts();

public:
	UPROPERTY()
	AActor* HoistCamera;
	
	UPROPERTY()
	AA_DispatchParts* DispatchParts;
};
