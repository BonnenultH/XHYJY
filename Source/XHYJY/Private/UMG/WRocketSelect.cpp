// Fill out your copyright notice in the Description page of Project Settings.


#include "UMG/WRocketSelect.h"
#include "Components/Spacer.h"
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

	ToChosen->SetText(FText::FromString(FString::FromInt(RightRocketArry.Num())));
	
	PlayAnimation(ShowTwoSlide);
}

void UWRocketSelect::InitRocketView()
{
	for(auto Rocket : UIManager->SelectTaskData->RocketArry)
	{
		if(Rocket.bRight)
		{
			RightRocketArry.Add(Rocket.RocketType);
			auto TempImage =NewObject<UImage>(this);
			auto MySpacer = NewObject<USpacer>(this);
			SeletedBox->AddChild(TempImage);
			SeletedBox->AddChild(MySpacer);
			TempImage->SetBrushFromTexture(ResourceManager->UnCheckBar, true);
			MySpacer->SetSize(FVector2d(12.0f,1.0f));
		}
		FRocketTable* RocketData = UIManager->GetRocketData(Rocket.RocketType);
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
