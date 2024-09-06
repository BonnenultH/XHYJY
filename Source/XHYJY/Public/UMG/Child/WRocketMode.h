// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UMG/BaseWidget.h"
#include "WRocketMode.generated.h"

/**
 * 
 */
UCLASS()
class XHYJY_API UWRocketMode : public UBaseWidget, public IUserObjectListEntry
{
	GENERATED_BODY()

public:
	virtual void InitWidget() override;

    virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;

	void BGChanged(bool bSelected);

public:
	UPROPERTY(meta=(BindWidget))
	UTextBlock* RocketEnglishName;
	UPROPERTY(meta=(BindWidget))
	UTextBlock* RocketName;
	UPROPERTY(meta=(BindWidget))
	UTextBlock* CarryingCapacity;
	UPROPERTY(meta=(BindWidget))
	UImage* RocketImage;
	UPROPERTY(meta=(BindWidget))
	UBorder* BG;
};
