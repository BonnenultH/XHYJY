// Fill out your copyright notice in the Description page of Project Settings.


#include "UMG/WHomePage.h"
#include "MediaPlayer.h"

void UWHomePage::InitWidget()
{
	Super::InitWidget();
	
	if(ResourceManager->MP && ResourceManager->MS)
	{
		ResourceManager->MP->OpenSource(ResourceManager->MS);
	}

	Overlay_Start->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	StartButton->OnClicked.AddDynamic(this, &UWHomePage::CreatUserFile);
}

void UWHomePage::CreatUserFile()
{
	UIManager->CreateVDWidget(EWidgetType::EWT_UserFile);
}



