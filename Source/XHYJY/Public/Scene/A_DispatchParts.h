// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Data/DataType.h"
#include "Scene/A_SinglePart.h"
#include "A_DispatchParts.generated.h"

class AUIManager;
class AResourceManager;

UCLASS()
class XHYJY_API AA_DispatchParts : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AA_DispatchParts();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void InitMeshArray();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	AUIManager* UIManager;
	AResourceManager* ResourceManager;
	
	FDiagramUITable* UIDiagram;
	
	TArray<FSingleRocketPart> SingleRocketPartArray;
	
	UStaticMesh* Mesh;
	
	FVector Location = FVector(-46243.709164,-37700.620589,409.999977);

public:
	TArray<AA_SinglePart*> SinglePartsArray;
};
