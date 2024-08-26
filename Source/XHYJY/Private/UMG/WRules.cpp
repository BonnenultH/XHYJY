// Fill out your copyright notice in the Description page of Project Settings.


#include "UMG/WRules.h"

void UWRules::InitWidget()
{
	Super::InitWidget();
	Button_Return->OnClicked.AddDynamic(this,&UWRules::ReturnUserFile);
	Button_TakeTasks->OnClicked.AddDynamic(this,&UWRules::CreateTakeTasks);
}

void UWRules::ReturnUserFile()
{
	UIManager->CreateVDWidget(ReturnWidgetType);
}

void UWRules::CreateTakeTasks()
{
	UIManager->CreateVDWidget(EWidgetType::EWT_TakeTasks);
}
