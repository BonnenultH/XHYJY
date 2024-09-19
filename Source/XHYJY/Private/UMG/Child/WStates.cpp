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

	if(UIManager->CurRightRocketType != ERocketType::ERT_None)
	{
		Image_Rocket->SetBrushFromTexture(ResourceManager->StatesRocketLight, true);
		RocketName->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		RocketName->SetText(FText::FromString(UIManager->GetRocketData(UIManager->CurRightRocketType)->RocketCNName));
	}
	if(UIManager->SelectFirePlace != EFirePlace::EFP_None)
	{
		Image_FirePlace->SetBrushFromTexture(ResourceManager->StatesFireplaceLight, true);
		FirePlace->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		//FirePlace->SetText(FText::FromString());
	}
}


        



	
