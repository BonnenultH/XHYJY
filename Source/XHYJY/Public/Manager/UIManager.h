// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BaseManager.h"
#include "UIManager.generated.h"

class UBaseWidget;


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

	void InitTaskTable();

	void InitRocketTable();

	void InitOrbitInfo();

	void InitRocketPartDiagram();

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

	FHTQCategoryData GetCategoryData()
	{
		return HTQCategoryData;
	}

	FRocketTable* GetRocketData(ERocketType RocketType)
	{
		return RocketMap[RocketType];
	}

	void MinusGrade(int32 Grade)
	{
		TaskGrade -= Grade;
	}

	int32 GetGrade()
	{
		return TaskGrade;
	}

	FDiagramUITable* GetDiagramMap(ERocketType RocketType)
	{
		return DiagramMap[RocketType];
	}

	FHTQOrbit GetOrbit(EOrbit OrbitType)
	{
		return OrbitMap[OrbitType];
	}

protected:
	int32 ManagerProgress = 0;
	float Interval;

	FHTQCategoryData HTQCategoryData;
	TMap<ERocketType, FRocketTable*> RocketMap;
	TMap<EOrbit, FHTQOrbit> OrbitMap;
	
	
	TMap<ERocketType, FDiagramUITable*> DiagramMap;
	int32 TaskGrade = 100;
	
public:
	TMap<EWidgetType, UBaseWidget*> WidgetMap;
	EWidgetType CurWidgetType = EWidgetType::EWT_None;

	FProgressDelegate OnUpdateProgress;

	UItemTask* SelectTaskItem;

	bool bShowOrbit = false;
	bool bShowRocket = false;
	bool bShowFirePlace = false;
	
	float	ManagerMinute = 2;
	float	ManagerSecond = 0;
	bool	bTimeStart = false;
};
