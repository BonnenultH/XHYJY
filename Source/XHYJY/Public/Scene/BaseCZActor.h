// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/DataType.h"
#include "GameFramework/Actor.h"
#include "BaseCZActor.generated.h"

class AVDPawn;
class UBoxComponent;
UCLASS()
class XHYJY_API ABaseCZActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseCZActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	void HoistSuccess();
	void DelaySwitchView();
	void CheckMeshCollsion(UStaticMeshComponent* TargetMesh, ERocketPartsType RightMeshType);
	void CheckMeshCollsion(TArray<UStaticMeshComponent*> TargetMeshArry, ERocketPartsType RightMeshType);
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void ShowAllMesh()	{};

public:
	UPROPERTY()
	AVDPawn* VDPawn;
	
	UPROPERTY()
	class AResourceManager* ResourceManager;

	UPROPERTY()
	class AUIManager* UIManager;

	UPROPERTY()
	class ASceneManager* SceneManager;
	
	

};
