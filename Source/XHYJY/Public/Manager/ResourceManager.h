// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BaseManager.h"
#include "ResourceManager.generated.h"


UCLASS()
class XHYJY_API AResourceManager : public ABaseManager
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AResourceManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	virtual void InitManager() override;
	
protected:
	void InitRSWidgetMap();

	void InitMediaResource();
	
	TSubclassOf<UUserWidget> LoadWidgetFile(FString Path);
	
public:
	TMap<EWidgetType, TSubclassOf<UUserWidget>> RSWidgetMap;
	
	UPROPERTY()
	class UMediaPlayer* MP;
	
	UPROPERTY()
	class UMediaSource* MS;
	
	UPROPERTY()
	class UMaterialParameterCollectionInstance* GenderMaterialInstance;
	
	UPROPERTY()
	class UMaterialParameterCollection* GenderMaterial;

	UPROPERTY()
	UTexture2D* ProgressOkImage;

	UPROPERTY()
	UDataTable* HTQTasks;

	UPROPERTY()
	UDataTable* RocketSelect;
	
	UPROPERTY()
	UTexture2D* SelectBG;

	UPROPERTY()
	UTexture2D* UnSelectBG;

	UPROPERTY()
	UTexture2D* CheckBar;

	UPROPERTY()
	UTexture2D* UnCheckBar;

	UPROPERTY()
	UTexture2D* JQ;
	UPROPERTY()
	UTexture2D* TY;
	UPROPERTY()
	UTexture2D* XC;
	UPROPERTY()
	UTexture2D* WC;

	UPROPERTY()
	UTexture2D* RocketSelectedBG;
	UPROPERTY()
	UTexture2D* RocketUnselectedBG;
	UPROPERTY()
	UTexture2D* RocketWrong;

	UPROPERTY()
	UMaterial* WarningMaterial;

	UPROPERTY()
	class ULevelSequence* LevelSequence;

	UPROPERTY()
	class ULevelSequencePlayer* LevelSequencePlayer;

	class ALevelSequenceActor * currentLevelSequenceActor = nullptr;
	
	
	
	
};
