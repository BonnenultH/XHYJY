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
	
	if(UIManager->bShowOrbit)
	{
		Orbit->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		FString Name = UIManager->GetOrbit(UIManager->SelectTaskData->HTQOrbitType).HTQOrbitName;
		Orbit->SetText(FText::FromString(Name));
	}

	if(UIManager->bShowRocket)
	{
		Image_Rocket->SetBrushFromTexture(ResourceManager->StatesRocketLight, true);
		RocketName->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		FString Name = UIManager->GetRocketData(UIManager->SelectTaskData->GetCheapestRocket())->RocketCNName;
		RocketName->SetText(FText::FromString(Name));
	}
	
	if(UIManager->bShowFirePlace)
	{
		Image_FirePlace->SetBrushFromTexture(ResourceManager->StatesFireplaceLight, true);
		FirePlace->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		FirePlace->SetText(FText::FromString(UIManager->SelectTaskData->FirePlaceName));
	}
}


        



	
