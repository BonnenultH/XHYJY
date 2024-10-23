// Fill out your copyright notice in the Description page of Project Settings.


#include "UMG/WRules.h"

#include "Kismet/GameplayStatics.h"

void UWRules::InitWidget()
{
	Super::InitWidget();
	Button_Return->OnClicked.AddDynamic(this,&UWRules::ReturnUserFile);
	Button_TakeTasks->OnClicked.AddDynamic(this,&UWRules::CreateTakeTasks);

	WBP_PersonTitle->InitWidget();
}

void UWRules::ReturnUserFile()
{
	UIManager->CreateVDWidget(ReturnWidgetType);
	UGameplayStatics::PlaySound2D(this,ResourceManager->Return);
}

void UWRules::CreateTakeTasks()
{
	UIManager->CreateVDWidget(EWidgetType::EWT_TakeTasks);
	UGameplayStatics::PlaySound2D(this,ResourceManager->Button);
}
