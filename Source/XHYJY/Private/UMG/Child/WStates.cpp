// Fill out your copyright notice in the Description page of Project Settings.


#include "UMG/Child/WStates.h"

void UWStates::InitWidget()
{
	Super::InitWidget();

	if(UIManager->SelectTaskData)
	{
		HTQName->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		HTQName->SetText(FText::FromString(UIManager->SelectTaskData->Name));
	}
	if(UIManager->OrbitName != L"")
	{
		Orbit->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		Orbit->SetText(FText::FromString(UIManager->OrbitName));
	}
}
