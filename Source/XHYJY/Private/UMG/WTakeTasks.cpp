// Fill out your copyright notice in the Description page of Project Settings.


#include "UMG/WTakeTasks.h"

void UWTakeTasks::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	UE_LOG(LogTemp, Log, TEXT("当前的分时间：%f, 当前的秒时间：%f, InDeltaTime == %f"), UIManager->ManagerMinute, UIManager->ManagerSecond, InDeltaTime)
	WBP_Timing->InitWidget();
	if(UIManager->ManagerSecond == 0)
	{
		UIManager->ManagerMinute -= 1;
		UIManager->ManagerSecond = 59;
	}
	if(Interval <= 1)
	{
		Interval += InDeltaTime;
	}
	else
	{
		Interval = 0;
		UIManager->ManagerSecond -= 1;
	}
}

void UWTakeTasks::InitWidget()
{
	Super::InitWidget();
	
	WBP_PersonTitle->InitWidget();
	Button_Ok->OnClicked.AddDynamic(this, &UWTakeTasks::CreateOrbits);
	UIManager->OnProgressState.Broadcast(1);
}

void UWTakeTasks::UpdateProgressState()
{
	
}

void UWTakeTasks::CreateOrbits()
{
	UIManager->CreateVDWidget(EWidgetType::EWT_Orbits);	
}
