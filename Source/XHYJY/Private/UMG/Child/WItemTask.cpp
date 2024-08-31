// Fill out your copyright notice in the Description page of Project Settings.


#include "UMG/Child/WItemTask.h"

void UWItemTask::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(ListItemObject);
	ItemData = Cast<UItemTask>(ListItemObject);
	InitWidget();
}

void UWItemTask::InitWidget()
{
	Super::InitWidget();
	Name->SetText(FText::FromString(ItemData->Name));
	FirstCategory->SetText(FText::FromString(ItemData->FirstCategory));
	SecondCategory->SetText(FText::FromString(ItemData->SecondCategory));
	Image->SetBrushFromTexture(ItemData->Image);
}

void UWItemTask::ChangeBG(bool bIsSelect)
{
	if(bIsSelect)
	{
		BG->SetBrushFromTexture(ResourceManager->SelectBG);
	}
	else
	{
		BG->SetBrushFromTexture(ResourceManager->UnSelectBG);
	}
}
