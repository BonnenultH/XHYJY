// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Data/DataType.h"
#include "Blueprint/UserWidget.h"
#include "GM/VDPawn.h"
#include "BaseManager.generated.h"

UCLASS()
class XHYJY_API ABaseManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void InitManager();
	
public:
	UPROPERTY()
	AVDPawn* VDPawn;
	
	UPROPERTY()
	AResourceManager* ResourceManager;
	
	UPROPERTY()
	AUIManager* UIManager;

	UPROPERTY()
	ASceneManager* SceneManager;
};
