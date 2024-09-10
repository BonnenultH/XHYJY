// Fill out your copyright notice in the Description page of Project Settings.


#include "UMG/Child/WRocketMode.h"
#include "UMG/WRocketSelect.h"

void UWRocketMode::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(ListItemObject);
	ItemData = Cast<UItemRocket>(ListItemObject);
	InitWidget();
	SelectMode(false);
}

void UWRocketMode::InitWidget()
{
	Super::InitWidget();

	UWRocketSelect* Widget = Cast<UWRocketSelect>(UIManager->WidgetMap[UIManager->CurWidgetType]);
	Widget->ChangeMode.AddUObject(this, &UWRocketMode::SelectMode);
	
	RocketName->SetText(FText::FromString(ItemData->RocketName));
	RocketEnglishName->SetText(FText::FromString(ItemData->RocketEnglishName));
	RocketImage->SetBrushFromTexture(ItemData->RocketImage);
	RocketImage->SetDesiredSizeOverride(ItemData->RocketImage->GetImportedSize());
	CarryingCapacity->SetText(FText::FromString(FString::SanitizeFloat(ItemData->CarryingCapacity)));
}

void UWRocketMode::SelectMode(bool bMode)
{
	if(!bMode)
	{
		Category->SetText(FText::FromString(TEXT("运载能力")));
		ProgressBar->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		LogoImage->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		ProgressBar->SetPercent(ItemData->CarryingCapacity / 15000);
	}
	else if(bMode)
	{
		Category->SetText(FText::FromString(TEXT("经济能力")));
		ProgressBar->SetVisibility(ESlateVisibility::Collapsed);
		LogoImage->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void UWRocketMode::BGChanged(bool bSelected)
{
	if(bSelected)
	{
		BG->SetBrushFromTexture(ResourceManager->RocketSelectedBG);
	}
	else
	{
		BG->SetBrushFromTexture(ResourceManager->RocketUnselectedBG);
	}
}
