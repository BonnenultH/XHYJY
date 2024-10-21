// Fill out your copyright notice in the Description page of Project Settings.


#include "UMG/WHistoryTasks.h"

void UWHistoryTasks::InitWidget()
{
	Super::InitWidget();
	
	Button_Return->OnClicked.AddDynamic(this, &UWHistoryTasks::ReturnWidget);
	WBP_PersonTitle->InitWidget();
}

void UWHistoryTasks::ReturnWidget()
{
	UIManager->CreateVDWidget(ReturnWidgetType);
}

void UWHistoryTasks::CreateTakeTasks()
{
	UIManager->CreateVDWidget(EWidgetType::EWT_TakeTasks);
}
