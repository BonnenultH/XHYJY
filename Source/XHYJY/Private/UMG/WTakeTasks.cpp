// Fill out your copyright notice in the Description page of Project Settings.


#include "UMG/WTakeTasks.h"

void UWTakeTasks::InitWidget()
{
	Super::InitWidget();
	Button_Ok->OnClicked.AddDynamic(this,&UWTakeTasks::CreateOrbits);
}

void UWTakeTasks::CreateOrbits()
{
	UIManager->CreateVDWidget(EWidgetType::EWT_Orbits);
}
