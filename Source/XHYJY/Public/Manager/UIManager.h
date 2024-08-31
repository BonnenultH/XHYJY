// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BaseManager.h"
#include "UIManager.generated.h"

class UBaseWidget;

//DECLARE_MULTICAST_DELEGATE_OneParam(FProgressDelegate)
DECLARE_MULTICAST_DELEGATE(FProgressDelegate)

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
	void UpdateProgress();

	void UpdateTime(float DeltaTime);
	
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
	
	float Interval;

public:
	TMap<EWidgetType, UBaseWidget*> WidgetMap;
	EWidgetType CurWidgetType = EWidgetType::EWT_None;

	FProgressDelegate OnUpdateProgress;
	
	float	ManagerMinute = 8;
	float	ManagerSecond = 0;
	bool	bTimeStart = false;
	
};
