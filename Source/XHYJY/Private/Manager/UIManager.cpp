// Fill out your copyright notice in the Description page of Project Settings.


#include "Manager/UIManager.h"
#include "UMG/BaseWidget.h"
#include "Manager/ResourceManager.h"


// Sets default values
AUIManager::AUIManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AUIManager::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AUIManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AUIManager::InitManager()
{
	Super::InitManager();
	
	CreateVDWidget(EWidgetType::EWT_HomePage);
}

void AUIManager::CreateVDWidget(EWidgetType WidgetType, bool bReturnWidget)
{
	if(CurWidgetType != EWidgetType::EWT_None)
	{
		WidgetMap[CurWidgetType]->SetVisibility(ESlateVisibility::Hidden);
	}
	
	if(WidgetMap.Contains(WidgetType))
	{
		CurWidgetType = WidgetType;
		WidgetMap[CurWidgetType]->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		return;
	}

	UBaseWidget* Widget = CreateWidget<UBaseWidget>(GetWorld(),ResourceManager->RSWidgetMap[WidgetType]);
	if(bReturnWidget)
	{
		Widget->ReturnWidgetType = CurWidgetType;
	}
	
	CurWidgetType = WidgetType;
	WidgetMap.Add(WidgetType, Widget);
	Widget->InitWidget();
	Widget->AddToViewport();
}


