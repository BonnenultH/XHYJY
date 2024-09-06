// Fill out your copyright notice in the Description page of Project Settings.


#include "UMG/WRocketSelect.h"
#include "UMG/Child/WRocketMode.h"



void UWRocketSelect::InitWidget()
{
	Super::InitWidget();

	WBP_PersonTitle->InitWidget();
	WBP_Timing->InitWidget();
	UIManager->OnUpdateProgress.Broadcast();
	Button_Ok->OnClicked.AddDynamic(this, &UWRocketSelect::CreateLaunch);
	InitRocketView();
}

void UWRocketSelect::InitRocketView()
{
	TArray<FSelectRocket*> AllSelectRocket;
	ResourceManager->RocketSelect->GetAllRows("", AllSelectRocket);
	for (auto Rocket : AllSelectRocket)
	{
		URocketSelection* RocketSelection = NewObject<URocketSelection>(this);
		RocketSelection->InitRocketData(Rocket);
		RocketListView->AddItem(RocketSelection);
	}
}

void UWRocketSelect::SelectRocketItem(UObject* objItem)
{
	UWRocketMode* RocketMode = Cast<UWRocketMode>(RocketListView->GetEntryWidgetFromItem(objItem));
	if(RocketMode)
	{
		RocketMode->BGChanged(true);
	}
	SelectNum++;
	Chosen->SetText(FText::FromString(FString::FromInt(SelectNum)));
}

void UWRocketSelect::CreateLaunch()
{
	UIManager->CreateVDWidget(EWidgetType::EWT_Launch);
}
