// Fill out your copyright notice in the Description page of Project Settings.


#include "UMG/WHomePage.h"
#include "MediaPlayer.h"
#include "Kismet/GameplayStatics.h"

void UWHomePage::InitWidget()
{
	Super::InitWidget();
	
	if(ResourceManager->MP && ResourceManager->MS)
	{
		ResourceManager->MP->OpenSource(ResourceManager->MS);
	}

	GameStart();
	StartButton->OnClicked.AddDynamic(this, &UWHomePage::CreatUserFile);
}

void UWHomePage::GameStart()
{
	Overlay_Start->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
}

void UWHomePage::CreatUserFile()
{
	PlayStartGameSound();
	UIManager->CreateVDWidget(EWidgetType::EWT_UserFile);
}

void UWHomePage::PlayStartGameSound()
{
	UGameplayStatics::PlaySound2D(this, ResourceManager->StartGame);
}



