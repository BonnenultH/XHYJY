// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "UMG/BaseWidget.h"
#include "WItemTask.generated.h"

/**
 * 
 */
UCLASS()
class XHYJY_API UWItemTask : public UBaseWidget, public IUserObjectListEntry
{
	GENERATED_BODY()

protected:
	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;

public:
	virtual void InitWidget() override;

	void ChangeBG(bool bIsSelect);

	UItemTask* GetItemData()
	{
		return ItemData;
	}
	
protected:
	UPROPERTY(meta=(BindWidget))
	UTextBlock* Name;
	UPROPERTY(meta=(BindWidget))
	UTextBlock* FirstCategory;
	UPROPERTY(meta=(BindWidget))
	UTextBlock* SecondCategory;
	UPROPERTY(meta=(BindWidget))
	UImage* Image;
	UPROPERTY(meta=(BindWidget))
	UBorder* BG;
	UPROPERTY()
	UItemTask* ItemData;
};
