// Fill out your copyright notice in the Description page of Project Settings.


#include "Manager/UIManager.h"
#include "UMG/BaseWidget.h"
#include "Manager/ResourceManager.h"
#include "Materials/MaterialParameterCollectionInstance.h"


// Sets default values
AUIManager::AUIManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AUIManager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AUIManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UpdateTime(DeltaTime);
}

void AUIManager::InitManager()
{
	Super::InitManager();
	
	OnUpdateProgress.AddUObject(this, &AUIManager::UpdateProgress);
	CreateVDWidget(EWidgetType::EWT_HomePage);
	InitUserFileGender();
	InitTaskTable();
	InitRocketTable();
}

void AUIManager::UpdateProgress()
{
	ManagerProgress += 1;
}

void AUIManager::UpdateTime(float DeltaTime)
{
	if(!bTimeStart)
	{
		return;
	}
	
	//UE_LOG(LogTemp, Log, TEXT("当前的分时间：%f, 当前的秒时间：%f, InDeltaTime == %f"), ManagerMinute, ManagerSecond, DeltaTime)
	if(UIManager->ManagerSecond == 0)
	{
		ManagerMinute -= 1;
		ManagerSecond = 59;
	}
	if(Interval <= 1)
	{
		Interval += DeltaTime;
	}
	else
	{
		Interval = 0;
		ManagerSecond -= 1;
	}
}

void AUIManager::InitUserFileGender()
{
	if(VDPawn->UserInfoData.Gender == EGender::EG_None)
		return;

	if(VDPawn->UserInfoData.Gender == EGender::EG_Man)
	{
		ResourceManager->GenderMaterialInstance->SetScalarParameterValue("ManORWoman", 2);
	}
	else if(VDPawn->UserInfoData.Gender == EGender::EG_Woman)
	{
		ResourceManager->GenderMaterialInstance->SetScalarParameterValue("ManORWoman", 0);
	}
}

void AUIManager::InitTaskTable()
{
	TArray<FTaskTable*> AllTaskArry;
	ResourceManager->HTQTasks->GetAllRows<FTaskTable>("", AllTaskArry);
	
	for(auto Task : AllTaskArry)
	{
		if(Task->FirstData.HTQFirstType != EHFCategory::EHFC_None)
		{
			if(HTQCategoryData.FirstDataMap.Find(Task->FirstData.HTQFirstType) == nullptr)
			{
				HTQCategoryData.CreateFirstData(Task->FirstData.HTQFirstType);
			}
			
			FHTQData HTQData(Task);
			HTQCategoryData.FirstDataMap[Task->FirstData.HTQFirstType].AllDataArry.Add(HTQData);
			
			if(Task->SecondData.HTQSecondType != EHSCategory::EHSC_None)
			{
				if(HTQCategoryData.FirstDataMap[Task->FirstData.HTQFirstType].SecondDataMap.Find(Task->SecondData.HTQSecondType) == nullptr)
				{
					HTQCategoryData.FirstDataMap[Task->FirstData.HTQFirstType].CreateSecondData(Task->SecondData.HTQSecondType);
				}
				HTQCategoryData.FirstDataMap[Task->FirstData.HTQFirstType].SecondDataMap[Task->SecondData.HTQSecondType].Add(HTQData);
			}
		}
	}
}

void AUIManager::InitRocketTable()
{
	TArray<FSelectRocket*> AllTaskArry;
	ResourceManager->RocketSelect->GetAllRows<FSelectRocket>("", AllTaskArry);
	
	for(auto Task : AllTaskArry)
	{
		RocketMap.Add(Task->RocketType, Task);
	}
	
}

void AUIManager::CreateVDWidget(EWidgetType WidgetType, bool bReturnWidget)
{
	if(CurWidgetType != EWidgetType::EWT_None)
	{
		WidgetMap[CurWidgetType]->SetVisibility(ESlateVisibility::Hidden);
	}
	
	if(WidgetMap.Contains(WidgetType))
	{
		CurWidgetType = WidgetType;
		WidgetMap[CurWidgetType]->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		return;
	}

	UBaseWidget* Widget = CreateWidget<UBaseWidget>(GetWorld(),ResourceManager->RSWidgetMap[WidgetType]);
	if(bReturnWidget)
	{
		Widget->ReturnWidgetType = CurWidgetType;
	}
	
	CurWidgetType = WidgetType;
	WidgetMap.Add(WidgetType, Widget);
	Widget->InitWidget();
	Widget->AddToViewport();
}



