// Fill out your copyright notice in the Description page of Project Settings.


#include "UMG/WTakeTasks.h"
#include "Components/ListView.h"
#include "UMG/Child/WItemTask.h"

void UWTakeTasks::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void UWTakeTasks::InitWidget()
{
	Super::InitWidget();
	
	UIManager->bTimeStart = true;
	InitTaskView();
	WBP_PersonTitle->InitWidget();
	WBP_Timing->InitWidget();
	Button_Ok->OnClicked.AddDynamic(this, &UWTakeTasks::CreateOrbits);
	UIManager->OnUpdateProgress.Broadcast();
}

void UWTakeTasks::InitTaskView()
{
	TArray<FTaskTable*> AllTaskArry;
	ResourceManager->HTQTasks->GetAllRows<FTaskTable>("", AllTaskArry);

	for(auto Task : AllTaskArry)
	{
		UItemTask* TaskItem = NewObject<UItemTask>(this);
		TaskItem->InitTaskData(Task);
		TaskView->AddItem(TaskItem);
	}
}

void UWTakeTasks::OnSelectTask(UObject* Item)
{
	if(Right->GetVisibility() == ESlateVisibility::Collapsed)
	{
		Right->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	}
	
	UWItemTask* ItemWidget = Cast<UWItemTask>(TaskView->GetEntryWidgetFromItem(Item));
	if(CurItemWidget)
	{
		CurItemWidget->ChangeBG(false);
	}
	if(ItemWidget)
	{
		ItemWidget->ChangeBG(true);
		CurItemWidget = ItemWidget;
	}
	
	UItemTask* ItemData = Cast<UItemTask>(Item);
	InitRightInfo(ItemData);
}

void UWTakeTasks::InitRightInfo(UItemTask* ItemData)
{
	RightImage->SetBrushFromTexture(ItemData->Image);
	RightName->SetText(FText::FromString(ItemData->Name));
	RightForAppFunc->SetText(FText::FromString(ItemData->ForAppFunc));
	RightDes->SetText(FText::FromString(ItemData->HTQDes));
}

void UWTakeTasks::CreateOrbits()
{
	UIManager->CreateVDWidget(EWidgetType::EWT_Orbits);	
}
