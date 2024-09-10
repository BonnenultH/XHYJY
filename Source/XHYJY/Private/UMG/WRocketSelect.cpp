// Fill out your copyright notice in the Description page of Project Settings.


#include "UMG/WRocketSelect.h"
#include "UMG/Child/WRocketMode.h"



void UWRocketSelect::InitWidget()
{
	Super::InitWidget();

	WBP_PersonTitle->InitWidget();
	WBP_Timing->InitWidget();
	WBP_States->InitWidget();
	
	UIManager->OnUpdateProgress.Broadcast();
	Button_Ok->OnClicked.AddDynamic(this, &UWRocketSelect::CreateLaunch);
	InitRocketView();
}

void UWRocketSelect::InitRocketView()
{
	
}

void UWRocketSelect::SelectRocketItem(UObject* objItem)
{
	
}

void UWRocketSelect::CreateLaunch()
{
	UIManager->CreateVDWidget(EWidgetType::EWT_Launch);
}
