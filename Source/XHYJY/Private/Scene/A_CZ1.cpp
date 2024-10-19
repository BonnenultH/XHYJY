// Fill out your copyright notice in the Description page of Project Settings.


#include "Scene/A_CZ1.h"

#include "Components/BoxComponent.h"
#include "Scene/A_SinglePart.h"

void AA_CZ1::BeginPlay()
{
	Super::BeginPlay();

	CoreOneLevel->OnComponentBeginOverlap.AddDynamic(this, &AA_CZ1::OnOverlapCOneSBox);
	Cowling->OnComponentBeginOverlap.AddDynamic(this, &AA_CZ1::OnOverlapCowBox);
	CoreThreeLevels->OnComponentBeginOverlap.AddDynamic(this, &AA_CZ1::OnOverlapCThreeSBox);
	CoreTwoLevels->OnComponentBeginOverlap.AddDynamic(this, &AA_CZ1::OnOverlapCTwoSBox);
}

void AA_CZ1::OnOverlapCOneSBox(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                               UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor && OtherActor != this)
	{
		CheckMeshCollsion(CoreOneLevelC, ERocketPartsType::ERP_CoreOneLevel);
	}
	
}

void AA_CZ1::OnOverlapCowBox(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor && OtherActor != this)
	{
		CheckMeshCollsion(CowlingC, ERocketPartsType::ERP_Cowling);
	}
}

void AA_CZ1::OnOverlapCThreeSBox(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor && OtherActor != this)
	{
		CheckMeshCollsion(CoreThreeLevelsC, ERocketPartsType::ERP_CoreThreeLevels);
	}
}

void AA_CZ1::OnOverlapCTwoSBox(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor && OtherActor != this)
	{
		CheckMeshCollsion(CoreTwoLevelsC, ERocketPartsType::ERP_CoreTwoLevels);
	}
}

void AA_CZ1::ShowAllMesh()
{
	Super::ShowAllMesh();

	CoreOneLevelC->SetHiddenInGame(false);
	CowlingC->SetHiddenInGame(false);
	CoreThreeLevelsC->SetHiddenInGame(false);
	CoreTwoLevelsC->SetHiddenInGame(false);
}
