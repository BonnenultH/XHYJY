// Fill out your copyright notice in the Description page of Project Settings.


#include "UMG/WTakeTasks.h"
#include "Components/ListView.h"
#include "UMG/Child/WItemTask.h"


void UWTakeTasks::InitWidget()
{
	Super::InitWidget();
	
	UIManager->bTimeStart = true;
	InitTaskView();
	WBP_PersonTitle->InitWidget();
	WBP_Timing->InitWidget();
	UIManager->OnUpdateProgress.Broadcast();
	
	Button_Satellite->OnClicked.AddDynamic(this, &UWTakeTasks::OnSelectedSatellite);
	Button_Spaceship->OnClicked.AddDynamic(this, &UWTakeTasks::OnSelectedSpaceship);
	Button_DeepSpaceProbes->OnClicked.AddDynamic(this, &UWTakeTasks::OnSelectedDeepSpaceProbes);
	Button_SpaceStation->OnClicked.AddDynamic(this, &UWTakeTasks::OnSelectedSpaceStation);
	Button_Navigation->OnClicked.AddDynamic(this, &UWTakeTasks::OnSelectedNavigation);
	Button_Communication->OnClicked.AddDynamic(this, &UWTakeTasks::OnSelectedCommunication);
	Button_RemoteSensing->OnClicked.AddDynamic(this, &UWTakeTasks::OnSelectedRemoteSensing);
	Button_ScientificExploration->OnClicked.AddDynamic(this, &UWTakeTasks::OnSelectedScientificExploration);
	Button_Ok->OnClicked.AddDynamic(this, &UWTakeTasks::PlayPoppingAni);
	Button_StartOrbits->OnClicked.AddDynamic(this, &UWTakeTasks::CreateOrbits);
}

void UWTakeTasks::InitTaskView()
{
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
	RightImage->SetBrushSize(ItemData->Image->GetImportedSize());
	RightName->SetText(FText::FromString(ItemData->Name));
	RightForAppFunc->SetText(FText::FromString(ItemData->ForAppFunc));
	RightDes->SetText(FText::FromString(ItemData->HTQDes));

	HTQ_Image->SetBrushFromTexture(ItemData->Image);
	HTQ_Image->SetBrushSize(ItemData->Image->GetImportedSize());
	HTQName->SetText(FText::FromString(ItemData->Name));
	LockFunc->SetText(FText::FromString(ItemData->ForAppFunc));
	HTQ_Description->SetText(FText::FromString(ItemData->HTQDes));
}

void UWTakeTasks::OnSelectedSatellite()
{
	if(Satellite->GetVisibility() == ESlateVisibility::Collapsed)
	{
		Satellite->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	}
	else
	{
		Satellite->SetVisibility(ESlateVisibility::Collapsed);
	}
	TaskView->ClearListItems();
	for(auto Task : AllTaskArry)
	{
		UItemTask* TaskItem = NewObject<UItemTask>(this);
		TaskItem->InitTaskData(Task);
		if(TaskItem->FirstCategory == L"人造卫星")
		{
		TaskView->AddItem(TaskItem);
		}
	}
	Right->SetVisibility(ESlateVisibility::Collapsed);
	
}

void UWTakeTasks::OnSelectedNavigation()
{
	TaskView->ClearListItems();
	for(auto Task : AllTaskArry)
	{
		UItemTask* TaskItem = NewObject<UItemTask>(this);
		TaskItem->InitTaskData(Task);
		if(TaskItem->SecondCategory == L"导航卫星")
		{
			TaskView->AddItem(TaskItem);
		}
	}
	Right->SetVisibility(ESlateVisibility::Collapsed);
}


void UWTakeTasks::OnSelectedCommunication()
{
	TaskView->ClearListItems();
	for(auto Task : AllTaskArry)
	{
		UItemTask* TaskItem = NewObject<UItemTask>(this);
		TaskItem->InitTaskData(Task);
		if(TaskItem->SecondCategory == L"通信卫星")
		{
			TaskView->AddItem(TaskItem);
		}
	}
	Right->SetVisibility(ESlateVisibility::Collapsed);
}

void UWTakeTasks::OnSelectedRemoteSensing()
{
	TaskView->ClearListItems();
	for(auto Task : AllTaskArry)
	{
		UItemTask* TaskItem = NewObject<UItemTask>(this);
		TaskItem->InitTaskData(Task);
		if(TaskItem->SecondCategory == L"遥感卫星")
		{
			TaskView->AddItem(TaskItem);
		}
	}
	Right->SetVisibility(ESlateVisibility::Collapsed);
}

void UWTakeTasks::OnSelectedScientificExploration()
{
	TaskView->ClearListItems();
	for(auto Task : AllTaskArry)
	{
		UItemTask* TaskItem = NewObject<UItemTask>(this);
		TaskItem->InitTaskData(Task);
		if(TaskItem->SecondCategory == L"科学探测卫星")
		{
			TaskView->AddItem(TaskItem);
		}
	}
	Right->SetVisibility(ESlateVisibility::Collapsed);
}

void UWTakeTasks::OnSelectedSpaceship()
{
	TaskView->ClearListItems();
	for(auto Task : AllTaskArry)
	{
		UItemTask* TaskItem = NewObject<UItemTask>(this);
		TaskItem->InitTaskData(Task);
		if(TaskItem->FirstCategory == L"宇宙飞船")
		{
			TaskView->AddItem(TaskItem);
		}
	}
	Right->SetVisibility(ESlateVisibility::Collapsed);
}

void UWTakeTasks::OnSelectedDeepSpaceProbes()
{
	TaskView->ClearListItems();
	for(auto Task : AllTaskArry)
	{
		UItemTask* TaskItem = NewObject<UItemTask>(this);
		TaskItem->InitTaskData(Task);
		if(TaskItem->FirstCategory == L"深空探测器")
		{
			TaskView->AddItem(TaskItem);
		}
	}
	Right->SetVisibility(ESlateVisibility::Collapsed);
}

void UWTakeTasks::OnSelectedSpaceStation()
{
	TaskView->ClearListItems();
	for(auto Task : AllTaskArry)
	{
		UItemTask* TaskItem = NewObject<UItemTask>(this);
		TaskItem->InitTaskData(Task);
		if(TaskItem->FirstCategory == L"空间站")
		{
			TaskView->AddItem(TaskItem);
		}
	}
	Right->SetVisibility(ESlateVisibility::Collapsed);
}

void UWTakeTasks::PlayPoppingAni()
{
	PlayAnimation(Ani_showInfo);
}

void UWTakeTasks::CreateOrbits()
{
	UIManager->CreateVDWidget(EWidgetType::EWT_Orbits);	
}


