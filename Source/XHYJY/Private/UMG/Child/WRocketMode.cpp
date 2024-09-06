// Fill out your copyright notice in the Description page of Project Settings.


#include "UMG/Child/WRocketMode.h"

void UWRocketMode::InitWidget()
{
	Super::InitWidget();
	
}

void UWRocketMode::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(ListItemObject);
	URocketSelection* RocketSelection = Cast<URocketSelection>(ListItemObject);
	InitWidget();
	RocketName->SetText(FText::FromString(RocketSelection->RocketName));
	RocketEnglishName->SetText(FText::FromString(RocketSelection->RocketEnglishName));
	RocketImage->SetBrushFromTexture(RocketSelection->RocketImage);
	RocketImage->SetDesiredSizeOverride(RocketSelection->RocketImage->GetImportedSize());
	CarryingCapacity->SetText(FText::FromString(RocketSelection->CarryingCapacity));
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
