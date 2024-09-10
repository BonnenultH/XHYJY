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

protected:
	// bMode = false : 代表是运载；bMode = true : 代表是经济；
	UFUNCTION()
	void SelectMode(bool bMode = false);

public:
	virtual void InitWidget() override;

    virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;

	void BGChanged(bool bSelected);

protected:
	UPROPERTY(meta=(BindWidget))
	UTextBlock* RocketEnglishName;
	UPROPERTY(meta=(BindWidget))
	UTextBlock* RocketName;
	UPROPERTY(meta=(BindWidget))
	UTextBlock* CarryingCapacity;
	UPROPERTY(meta=(BindWidget))
	UTextBlock* Category;
	UPROPERTY(meta=(BindWidget))
	UProgressBar* ProgressBar;
	UPROPERTY(meta=(BindWidget))
	UImage* RocketImage;
	UPROPERTY(meta=(BindWidget))
	UBorder* BG;
	UPROPERTY(meta=(BindWidget))
	UImage* LogoImage;

	UPROPERTY()
	UItemRocket* ItemData;
};
