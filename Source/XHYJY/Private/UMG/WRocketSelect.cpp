// Fill out your copyright notice in the Description page of Project Settings.


#include "UMG/WRocketSelect.h"

#include "Components/HorizontalBoxSlot.h"
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
	for(auto Rocket : UIManager->SelectTaskData->RocketArry)
	{
		if(Rocket.bRight)
		{
			RightRocketArry.Add(Rocket.RocketType);
			UImage* TempImage = NewObject<UImage>(this);
			ImageBox->AddChildToHorizontalBox(TempImage);
			TempImage->SetBrushFromTexture(ResourceManager->UnCheckBar);
			TempImage->SetDesiredSizeOverride(TempImage->GetDesiredSize());
		}
		
		FSelectRocket* RocketData = UIManager->GetRocketData(Rocket.RocketType);
		UItemRocket* RocketItem = NewObject<UItemRocket>(this);
		RocketItem->InitRocketData(RocketData);
		RocketListView->AddItem(RocketItem);
	}
}

void UWRocketSelect::CheckSelectRocket()
{
	
}

void UWRocketSelect::SelectRocketItem(UObject* objItem)
{
	
}

void UWRocketSelect::CreateLaunch()
{
	UIManager->CreateVDWidget(EWidgetType::EWT_Launch);
}
