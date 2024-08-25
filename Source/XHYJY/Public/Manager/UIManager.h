// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BaseManager.h"
#include "UIManager.generated.h"

class UBaseWidget;

UCLASS()
class XHYJY_API AUIManager : public ABaseManager
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AUIManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void InitManager() override;

public:
	void CreateVDWidget(EWidgetType UItype, bool bReturnWidget = false);

public:
	TMap<EWidgetType, UBaseWidget*> WidgetMap;
	
	EWidgetType CurWidgetType = EWidgetType::EWT_None;
};
