// Fill out your copyright notice in the Description page of Project Settings.


#include "Scene/A_CZ7.h"

#include "Components/BoxComponent.h"
#include "Scene/A_SinglePart.h"

void AA_CZ7::BeginPlay()
{
	Super::BeginPlay();

	Cowling->OnComponentBeginOverlap.AddDynamic(this, &AA_CZ7::OnOverlapCowlingBox);
	CoreOneLevel->OnComponentBeginOverlap.AddDynamic(this, &AA_CZ7::OnOverlapCoreOneLevelBox);
	CoreTwoLevels->OnComponentBeginOverlap.AddDynamic(this, &AA_CZ7::OnOverlapCoreTwoLevelsBox);
	Rollboosters->OnComponentBeginOverlap.AddDynamic(this, &AA_CZ7::OnOverlapRollboostersBox);
	Rollboosters2->OnComponentBeginOverlap.AddDynamic(this, &AA_CZ7::OnOverlapRollboostersBox);
	Rollboosters3->OnComponentBeginOverlap.AddDynamic(this, &AA_CZ7::OnOverlapRollboostersBox);
	Rollboosters4->OnComponentBeginOverlap.AddDynamic(this, &AA_CZ7::OnOverlapRollboostersBox);
}

void AA_CZ7::OnOverlapCowlingBox(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor && OtherActor != this)
	{
		CheckMeshCollsion(CowlingS, ERocketPartsType::ERP_Cowling);
		
	}
}

void AA_CZ7::OnOverlapCoreOneLevelBox(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor && OtherActor != this)
	{
		CheckMeshCollsion(CoreOneLevelS, ERocketPartsType::ERP_CoreOneLevel);
		
	}
}

void AA_CZ7::OnOverlapCoreTwoLevelsBox(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor && OtherActor != this)
	{
		CheckMeshCollsion(CoreTwoLevelsS, ERocketPartsType::ERP_CoreTwoLevels);
	}
}

void AA_CZ7::OnOverlapRollboostersBox(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor && OtherActor != this)
	{
		TArray<UStaticMeshComponent*> MeshArry;
		MeshArry.Add(RollboostersS);
		MeshArry.Add(RollboostersS2);
		MeshArry.Add(RollboostersS3);
		MeshArry.Add(RollboostersS4);
		CheckMeshCollsion(MeshArry, ERocketPartsType::ERP_Boosters);
		
	}
}

void AA_CZ7::ShowAllMesh()
{
	Super::ShowAllMesh();

	RollboostersS->SetHiddenInGame(false);
	RollboostersS2->SetHiddenInGame(false);
	RollboostersS3->SetHiddenInGame(false);
	RollboostersS4->SetHiddenInGame(false);
	CoreTwoLevelsS->SetHiddenInGame(false);
	CoreOneLevelS->SetHiddenInGame(false);
	CowlingS->SetHiddenInGame(false);
}
