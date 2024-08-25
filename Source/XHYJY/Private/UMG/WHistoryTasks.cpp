// Fill out your copyright notice in the Description page of Project Settings.


#include "UMG/WHistoryTasks.h"

void UWHistoryTasks::InitWidget()
{
	Super::InitWidget();
	Button_Return->OnClicked.AddDynamic(this, &UWHistoryTasks::ReturnWidget);
}

void UWHistoryTasks::ReturnWidget()
{
	UIManager->CreateVDWidget(ReturnWidgetType);
}
