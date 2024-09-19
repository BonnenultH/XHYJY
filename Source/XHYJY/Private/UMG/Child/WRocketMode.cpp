// Fill out your copyright notice in the Description page of Project Settings.


#include "UMG/Child/WRocketMode.h"
#include "UMG/WRocketSelect.h"

void UWRocketMode::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(ListItemObject);
	ItemData = Cast<UItemRocket>(ListItemObject);
	InitWidget();
}

void UWRocketMode::InitWidget()
{
	Super::InitWidget();

	UWRocketSelect* Widget = Cast<UWRocketSelect>(UIManager->WidgetMap[UIManager->CurWidgetType]);
	Widget->ChangeMode.AddUObject(this, &UWRocketMode::SelectMode);
	
	RocketName->SetText(FText::FromString(ItemData->RocketName));
	RocketEnglishName->SetText(FText::FromString(ItemData->RocketEnglishName));
	RocketImage->SetBrushFromTexture(ItemData->RocketImage, true);
	CarryingCapacity->SetText(FText::FromString(FString::FromInt(FMath::RoundToInt(ItemData->CarryingCapacity))));
	SelectMode(Widget->GetCurMode());
}

void UWRocketMode::SelectMode(ERSMode Mode)
{
	if(Mode == ERSMode::ERSM_Capacity)
	{
		Category->SetText(FText::FromString(TEXT("运载能力")));
		ProgressBar->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		LogoImage->SetBrushFromTexture(ResourceManager->CapacityIcon,true);
		ProgressBar->SetPercent(ItemData->CarryingCapacity / 15000);
	}
	else if(Mode == ERSMode::ERSM_Price)
	{
		Category->SetText(FText::FromString(TEXT("经济能力")));
		ProgressBar->SetVisibility(ESlateVisibility::Collapsed);
		LogoImage->SetBrushFromTexture(ResourceManager->PriceIcon,true);
	}
}

void UWRocketMode::BGChanged(int32 bSelected)
{
	switch (bSelected)
	{
		case 0 :
			{
				BG->SetBrushFromTexture(ResourceManager->RocketSelectedBG);	
			}
		break;

		case 1 :
			{
				BG->SetBrushFromTexture(ResourceManager->RocketUnselectedBG);
			}
		break;

		case 2 :
			{
				BG->SetBrushFromTexture(ResourceManager->RocketWrong);
			}
		break;
	}
}
