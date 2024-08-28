// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BaseManager.h"
#include "UIManager.generated.h"

class UBaseWidget;

DECLARE_MULTICAST_DELEGATE_OneParam(FProgressMag, int32)
DECLARE_MULTICAST_DELEGATE(FProgressTitle)

UCLASS()
class XHYJY_API AUIManager : public ABaseManager
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AUIManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

protected:
	void InitUserFileGender();

	UFUNCTION()
	void UpdateProgressState(int32 Progres);
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void InitManager() override;

public:
	void CreateVDWidget(EWidgetType WidgetType, bool bReturnWidget = false);

	int32 GetManagerProgress()
	{
		return ManagerProgress;
	}

protected:
	int32 ManagerProgress = 0;

public:
	TMap<EWidgetType, UBaseWidget*> WidgetMap;
	EWidgetType CurWidgetType = EWidgetType::EWT_None;

	FProgressMag OnProgressState;
	FProgressTitle OnUpdateTitle;
	
	float	ManagerMinute = 8;
	float	ManagerSecond = 0;
};
