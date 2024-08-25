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
}
