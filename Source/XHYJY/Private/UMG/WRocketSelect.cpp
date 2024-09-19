// Fill out your copyright notice in the Description page of Project Settings.


#include "UMG/WRocketSelect.h"
#include "Components/Spacer.h"
#include "UMG/Child/WRocketMode.h"


void UWRocketSelect::InitWidget()
{
	Super::InitWidget();
	
	WBP_PersonTitle->InitWidget();
	WBP_Timing->InitWidget();
	WBP_States->InitWidget();
	
	UIManager->OnUpdateProgress.Broadcast();
	Button_Ok->OnClicked.AddDynamic(this, &UWRocketSelect::CheckSelectRocket);

	InitRocketView();
	PlayAnimation(ShowTwoSlide);
}

void UWRocketSelect::InitRocketView()
{
	ErrorNums = 1;
	RocketListView->ClearListItems();
	SelectedRocketArry.Empty();
	
	if(CurMode == ERSMode::ERSM_Capacity)
	{
		for(auto Rocket : UIManager->SelectTaskData->RocketArry)
		{
			FRocketTable* RocketData = UIManager->GetRocketData(Rocket.RocketType);
			UItemRocket* RocketItem = NewObject<UItemRocket>(this);
			RocketItem->InitRocketData(RocketData, Rocket.bRight);
			if(Rocket.bRight)
			{
				UImage* TempImage = NewObject<UImage>(this);
				USpacer* MySpacer = NewObject<USpacer>(this);
				SeletedBoxArry.Add(TempImage);
				SeletedBox->AddChild(TempImage);
				SeletedBox->AddChild(MySpacer);
				TempImage->SetBrushFromTexture(ResourceManager->UnCheckBar, true);
				MySpacer->SetSize(FVector2d(12.0f,1.0f));
				RightRocketArry.Add(Rocket);
			}
			RocketListView->AddItem(RocketItem);
		}
		Chosen->SetText(FText::FromString(FString::FromInt(0)));
		ToChosen->SetText(FText::FromString(FString::FromInt(RightRocketArry.Num())));
	}
	else if(CurMode == ERSMode::ERSM_Price)
	{
		SeletedBoxArry.Empty();
		SeletedBox->ClearChildren();
		
		UImage* TempImage = NewObject<UImage>(this);
		SeletedBoxArry.Add(TempImage);
		SeletedBox->AddChild(TempImage);
		TempImage->SetBrushFromTexture(ResourceManager->UnCheckBar, true);
		for(auto Rocket : RightRocketArry)
		{
			FRocketTable* RocketData = UIManager->GetRocketData(Rocket.RocketType);
			UItemRocket* RocketItem = NewObject<UItemRocket>(this);
			RocketItem->InitRocketData(RocketData, Rocket.bRight);
			RocketListView->AddItem(RocketItem);
		}
		Chosen->SetText(FText::FromString(FString::FromInt(0)));
		ToChosen->SetText(FText::FromString(FString::FromInt(1)));
	}
}

void UWRocketSelect::CheckSelectRocket()
{
	bool bResult = true;

	if(CurMode == ERSMode::ERSM_Capacity)
	{
		if(SelectedRocketArry.Num() != RightRocketArry.Num())
		{
			// 选错了
			bResult = false;
		}
		else
		{
			for(auto RocketItem : SelectedRocketArry)
			{
				if(!RocketItem->bRocketRight)
				{
					// 选错
					bResult = false;
					break;
				}
			}
		}
	
		if(bResult)
		{
			SelectRocketRight();
		}
		else
		{
			SelectRocketError();
		}
	}
	else if(CurMode == ERSMode::ERSM_Price)
	{
		if(SelectedRocketArry.Num() != 1)
		{
			// 选错了
			bResult = false;
		}
		else
		{
			if(SelectedRocketArry[0]->RocketType != UIManager->SelectTaskData->GetCheapestRocket())
			{
				bResult = false;
			}
		}
		
		if(bResult)
		{
			UIManager->CurRightRocketType = UIManager->SelectTaskData->GetCheapestRocket();
			CreateLaunch();
		}
		else
		{
			SelectPRocketError();
		}
	}
}

void UWRocketSelect::SelectRocketError()
{
	if(ErrorNums != 0)
	{
		UIManager->MinusGrade(10);
		CountErrorNums();
		
		CanvasPanel->SetVisibility(ESlateVisibility::HitTestInvisible);
		if(TimerHandle.IsValid())
		{
			GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
		}
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UWRocketSelect::ReInitialRocketView, 2);
	
		for(auto RocketItem : SelectedRocketArry)
		{
			if(!RocketItem->bRocketRight)
			{
				UWRocketMode* ItemWidget = Cast<UWRocketMode>(RocketListView->GetEntryWidgetFromItem(RocketItem));
				ItemWidget->BGChanged(2);
			}
		}
	}
	else
	{
		// 选对了
		SelectRocketRight();
	}
}

void UWRocketSelect::SelectRocketRight()
{
	SwitchLeft->SetActiveWidgetIndex(1);
	SwitchRight->SetActiveWidgetIndex(1);
	CurMode = ERSMode::ERSM_Price;
	ChangeMode.Broadcast(CurMode);
	InitRocketView();
}

void UWRocketSelect::ReInitialRocketView()
{
	CanvasPanel->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	for(auto RocketItem : SelectedRocketArry)
	{
		UWRocketMode* ItemWidget = Cast<UWRocketMode>(RocketListView->GetEntryWidgetFromItem(RocketItem));
		ItemWidget->BGChanged(1);
	}
	SelectedRocketArry.Empty();
	Chosen->SetText(FText::FromString(FString::FromInt(0)));
	for(auto Image : SeletedBoxArry)
	{
		Image->SetBrushFromTexture(ResourceManager->UnCheckBar, true);
	}
}

void UWRocketSelect::SelectPRocketError()
{
	if(ErrorNums != 0)
	{
		UIManager->MinusGrade(10);
		CountErrorNums();
		
		CanvasPanel->SetVisibility(ESlateVisibility::HitTestInvisible);
		if(TimerHandle.IsValid())
		{
			GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
		}
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UWRocketSelect::ReInitialRocketView, 2);
	
		for(auto RocketItem : SelectedRocketArry)
		{
			if(RocketItem->RocketType != UIManager->SelectTaskData->GetCheapestRocket())
			{
				UWRocketMode* ItemWidget = Cast<UWRocketMode>(RocketListView->GetEntryWidgetFromItem(RocketItem));
				ItemWidget->BGChanged(2);
			}
		}
	}
	else
	{
		// 选对了
		CreateLaunch();
	}
}

void UWRocketSelect::SelectRocketItem(UObject* ObjItem)
{
	UItemRocket* Item = Cast<UItemRocket>(ObjItem);
	UWRocketMode* ItemWidget = Cast<UWRocketMode>(RocketListView->GetEntryWidgetFromItem(Item));
	if(SelectedRocketArry.Contains(Item))
	{
		return;
	}
	
	SelectedRocketArry.Add(Item);
	ItemWidget->BGChanged(0);
	Chosen->SetText(FText::FromString(FString::FromInt(SelectedRocketArry.Num())));
	if(SelectedRocketArry.Num() <= SeletedBoxArry.Num())
	{
		SeletedBoxArry[SelectedRocketArry.Num() - 1]->SetBrushFromTexture(ResourceManager->CheckBar, true);
	}
}

void UWRocketSelect::CreateLaunch()
{
	UIManager->CreateVDWidget(EWidgetType::EWT_Launch);
}
