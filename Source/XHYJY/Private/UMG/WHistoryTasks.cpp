// Fill out your copyright notice in the Description page of Project Settings.


#include "UMG/WHistoryTasks.h"
#include "Kismet/GameplayStatics.h"
#include "UMG/Child/WItemTask.h"

void UWHistoryTasks::InitWidget()
{
	Super::InitWidget();

	Button_TakeTasks->OnClicked.AddDynamic(this, &UWHistoryTasks::CreateTakeTasks);
	Button_Return->OnClicked.AddDynamic(this, &UWHistoryTasks::ReturnWidget);
	WBP_PersonTitle->InitWidget();

	InitHistoryView();
	TextBlock_UnlockNum->SetText(FText::FromString(FString::FromInt(UIManager->HistoryArry.Num())));
}

void UWHistoryTasks::ReturnWidget()
{
	UGameplayStatics::PlaySound2D(this,ResourceManager->Return);
	UIManager->CreateVDWidget(ReturnWidgetType);
}

void UWHistoryTasks::CreateTakeTasks()
{
	UIManager->CreateVDWidget(EWidgetType::EWT_TakeTasks);
}

void UWHistoryTasks::InitHistoryView()
{
	for(auto ItemData: UIManager->GetCategoryData().FirstDataMap)
	{
		for(auto Data : ItemData.Value.AllDataArry)
		{
			UItemTask* TaskItem = NewObject<UItemTask>(this);
			TaskItem->InitTaskData(Data);
			for (auto History :UIManager->HistoryArry)
			{
				if(History.craftModel == TaskItem->Name)
				{
					TaskItem->UserGrade = History.grade;
					TaskItem->Finishtime = History.finishTime;
					TileView_History->AddItem(TaskItem);
				}
			}
		}
	}
}

void UWHistoryTasks::OnSelectTask(UObject* Item)
{
	if(Right->GetVisibility() == ESlateVisibility::Collapsed)
	{
		Right->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	}
	
	UWItemTask* ItemWidget = Cast<UWItemTask>(TileView_History->GetEntryWidgetFromItem(Item));
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

void UWHistoryTasks::InitRightInfo(UItemTask* ItemData)
{
	Image_HTQ->SetBrushFromTexture(ItemData->Image);
	HTQ_Name->SetText(FText::FromString(ItemData->Name));
	LockFunc->SetText(FText::FromString(ItemData->ForAppFunc));
	HTQ_Description->SetText(FText::FromString(ItemData->HTQDes));
	finishtime->SetText(FText::FromString(ItemData->Finishtime));
	TextBlock_Grade->SetText(FText::FromString(FString::FromInt(ItemData->UserGrade)));
}




