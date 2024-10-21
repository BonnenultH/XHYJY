// Fill out your copyright notice in the Description page of Project Settings.


#include "UMG/BaseWidget.h"
#include "Kismet/GameplayStatics.h"

void UBaseWidget::InitWidget()
{
	AVDPawn* Pawn = nullptr;
	Pawn = Cast<AVDPawn>(UGameplayStatics::GetPlayerPawn(this, 0));
	if(Pawn)
	{
		VDPawn			= Pawn;
		ResourceManager	= Pawn->ResourceManager;
		UIManager		= Pawn->UIManager;
		SceneManager	= Pawn->SceneManager;
	}
}

void UBaseWidget::CountErrorNums()
{
	ErrorNums -= 1;
}

