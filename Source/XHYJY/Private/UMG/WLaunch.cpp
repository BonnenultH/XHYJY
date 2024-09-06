// Fill out your copyright notice in the Description page of Project Settings.


#include "UMG/WLaunch.h"

void UWLaunch::InitWidget()
{
	Super::InitWidget();
	
	WBP_PersonTitle->InitWidget();
	WBP_Timing->InitWidget();
	UIManager->OnUpdateProgress.Broadcast();
}
