// Fill out your copyright notice in the Description page of Project Settings.


#include "UMG/WTakeTasks.h"
#include "Components/ListView.h"
#include "Kismet/GameplayStatics.h"
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
	Button_Reselect->OnClicked.AddDynamic(this, &UWTakeTasks::UnSelect);
}

void UWTakeTasks::InitTaskView()
{
	for(auto ItemData: UIManager->GetCategoryData().FirstDataMap)
	{
		for(auto Data : ItemData.Value.AllDataArry)
		{
			UItemTask* TaskItem = NewObject<UItemTask>(this);
			TaskItem->InitTaskData(Data);
			TaskView->AddItem(TaskItem);
		}
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

void UWTakeTasks::InitSelectedInfo(UItemTask* ItemData)
{
	HTQ_Image->SetBrushFromTexture(ItemData->Image, true);
	HTQName->SetText(FText::FromString(ItemData->Name));
	LockFunc->SetText(FText::FromString(ItemData->ForAppFunc));
	HTQ_Description->SetText(FText::FromString(ItemData->HTQDes));
}

void UWTakeTasks::OnSelectedSatellite()
{
	PlaySoundFirstCategory();

	if(Satellite->GetVisibility() == ESlateVisibility::Collapsed)
	{
		Satellite->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	}
	else
	{
		Satellite->SetVisibility(ESlateVisibility::Collapsed);
	}

	TArray<FHTQData> AllData = UIManager->GetCategoryData().FirstDataMap[EHFCategory::EHFC_Satellite].AllDataArry;
	UpdateView(AllData);

}

void UWTakeTasks::OnSelectedNavigation()
{
	PlaySoundButton();

	TMap<EHSCategory, TArray<FHTQData>> TempDataMap = UIManager->GetCategoryData().FirstDataMap[EHFCategory::EHFC_Satellite].SecondDataMap;
	TArray<FHTQData> AllData = TempDataMap[EHSCategory::EHSC_Navigation];
	UpdateView(AllData);

}

void UWTakeTasks::OnSelectedCommunication()
{
	PlaySoundButton();

	TMap<EHSCategory, TArray<FHTQData>> TempDataMap = UIManager->GetCategoryData().FirstDataMap[EHFCategory::EHFC_Satellite].SecondDataMap;
	TArray<FHTQData> AllData = TempDataMap[EHSCategory::EHSC_Communication];
	UpdateView(AllData);

}

void UWTakeTasks::OnSelectedRemoteSensing()
{
	PlaySoundButton();

	TMap<EHSCategory, TArray<FHTQData>> TempDataMap = UIManager->GetCategoryData().FirstDataMap[EHFCategory::EHFC_Satellite].SecondDataMap;
	TArray<FHTQData> AllData = TempDataMap[EHSCategory::EHSC_RemoteSensing];
	UpdateView(AllData);

}

void UWTakeTasks::OnSelectedScientificExploration()
{
	PlaySoundButton();

	TMap<EHSCategory, TArray<FHTQData>> TempDataMap = UIManager->GetCategoryData().FirstDataMap[EHFCategory::EHFC_Satellite].SecondDataMap;
	TArray<FHTQData> AllData = TempDataMap[EHSCategory::EHSC_ScientificExploration];
	UpdateView(AllData);

}

void UWTakeTasks::OnSelectedSpaceship()
{
	PlaySoundFirstCategory();

	TArray<FHTQData> AllData = UIManager->GetCategoryData().FirstDataMap[EHFCategory::EHFC_SpaceShip].AllDataArry;
	UpdateView(AllData);

}

void UWTakeTasks::OnSelectedDeepSpaceProbes()
{
	PlaySoundFirstCategory();

	TArray<FHTQData> AllData = UIManager->GetCategoryData().FirstDataMap[EHFCategory::EHFC_DeepSpaceProbes].AllDataArry;
	UpdateView(AllData);

}

void UWTakeTasks::OnSelectedSpaceStation()
{
	PlaySoundFirstCategory();

	TArray<FHTQData> AllData = UIManager->GetCategoryData().FirstDataMap[EHFCategory::EHFC_SpaceStation].AllDataArry;
	UpdateView(AllData);

}

void UWTakeTasks::PlayPoppingAni()
{
	InitSelectedInfo(CurItemWidget->GetItemData());
	PlayAnimation(Ani_showInfo);
}

void UWTakeTasks::CreateOrbits()
{
	PlaySoundTakeTask();
	
	UIManager->SelectTaskItem = CurItemWidget->GetItemData();
	SceneManager->InitSingleMesh();
	UIManager->CreateVDWidget(EWidgetType::EWT_Orbits);
}

void UWTakeTasks::UnSelect()
{
	PlaySoundReselect();
	
	PlayAnimationReverse(Ani_showInfo);
}

void UWTakeTasks::UpdateView(TArray<FHTQData> AllDataArry)
{
	TaskView->ClearListItems();
	for(auto Data : AllDataArry)
	{
		UItemTask* TaskItem = NewObject<UItemTask>(this);
		TaskItem->InitTaskData(Data);
		TaskView->AddItem(TaskItem);
	}
	
	Right->SetVisibility(ESlateVisibility::Collapsed);
}

void UWTakeTasks::PlaySoundFirstCategory()
{
	UGameplayStatics::PlaySound2D(this, ResourceManager->Menu);
}

void UWTakeTasks::PlaySoundTakeTask()
{
	UGameplayStatics::PlaySound2D(this, ResourceManager->TakeTasksSound);
}

void UWTakeTasks::PlaySoundReselect()
{
	UGameplayStatics::PlaySound2D(this, ResourceManager->Return);
}


