// Fill out your copyright notice in the Description page of Project Settings.


#include "UMG/WTakeTasks.h"

void UWTakeTasks::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void UWTakeTasks::InitWidget()
{
	Super::InitWidget();

	UIManager->bTimeStart = true;
	WBP_PersonTitle->InitWidget();
	WBP_Timing->InitWidget();
	Button_Ok->OnClicked.AddDynamic(this, &UWTakeTasks::CreateOrbits);
	UIManager->OnUpdateProgress.Broadcast();
}

void UWTakeTasks::UpdateProgressState()
{
	
}

void UWTakeTasks::CreateOrbits()
{
	UIManager->CreateVDWidget(EWidgetType::EWT_Orbits);	
}
