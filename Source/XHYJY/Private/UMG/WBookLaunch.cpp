// Fill out your copyright notice in the Description page of Project Settings.


#include "UMG/WBookLaunch.h"

void UWBookLaunch::InitWidget()
{
	Super::InitWidget();

	WBP_PersonTitle->InitWidget();
	UIManager->OnUpdateProgress.Broadcast();

	
	if(UIManager->GetGrade() == 100)
	{
		Image_Level->SetBrushFromTexture(ResourceManager->S);
	}
	else if(UIManager->GetGrade() > 90)
	{
		Image_Level->SetBrushFromTexture(ResourceManager->A);
	}
	else if(UIManager->GetGrade() > 80)
	{
		Image_Level->SetBrushFromTexture(ResourceManager->B);
	}
	else if(UIManager->GetGrade() > 60)
	{
		Image_Level->SetBrushFromTexture(ResourceManager->C);
	}
	else 
	{
		Image_Level->SetBrushFromTexture(ResourceManager->D);
	}

	FString TimeStr;
	TimeStr = FString::SanitizeFloat(8 - UIManager->ManagerMinute);
	TimeStr.Append(":");
	TimeStr.Append(FString::SanitizeFloat(59 - UIManager->ManagerSecond));
	TextBlock_Time->SetText(FText::FromString(TimeStr));
	TextBlock_HTQ->SetText(FText::FromString(UIManager->SelectTaskItem->Name));
	TextBlock_Rocket->SetText(FText::FromString(UIManager->GetRocketData(UIManager->SelectTaskItem->GetCheapestRocket())->RocketCNName));
	TextBlock_Fireplace->SetText(FText::FromString(UIManager->SelectTaskItem->FirePlaceName));
}
