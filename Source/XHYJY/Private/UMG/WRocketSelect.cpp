// Fill out your copyright notice in the Description page of Project Settings.


#include "UMG/WRocketSelect.h"

void UWRocketSelect::InitWidget()
{
	Super::InitWidget();

	WBP_PersonTitle->InitWidget();
	UIManager->OnProgressState.Broadcast(1);
	
}
