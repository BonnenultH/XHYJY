// Fill out your copyright notice in the Description page of Project Settings.


#include "Scene/A_CZ3A.h"

#include "Components/BoxComponent.h"
#include "Scene/A_SinglePart.h"

void AA_CZ3A::BeginPlay()
{
	Super::BeginPlay();

	CoreOneLevel->OnComponentBeginOverlap.AddDynamic(this, &AA_CZ3A::OnOverlapCOneSBox);
	Cowling->OnComponentBeginOverlap.AddDynamic(this, &AA_CZ3A::OnOverlapCowBox);
	CoreThreeLevels->OnComponentBeginOverlap.AddDynamic(this, &AA_CZ3A::OnOverlapCThreeSBox);
	CoreTwoLevels->OnComponentBeginOverlap.AddDynamic(this, &AA_CZ3A::OnOverlapCTwoSBox);
}

void AA_CZ3A::OnOverlapCOneSBox(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor && OtherActor != this)
	{
		AA_SinglePart* SingleActor = Cast<AA_SinglePart>(OtherActor);
		if(SingleActor)
		{
			CheckMeshCollsion(SingleActor, CoreOneLevelC, ERocketPartsType::ERP_CoreOneLevel);
		}
	}
}

void AA_CZ3A::OnOverlapCowBox(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor && OtherActor != this)
	{
		AA_SinglePart* SingleActor = Cast<AA_SinglePart>(OtherActor);
		if(SingleActor)
		{
			CheckMeshCollsion(SingleActor, CowlingC, ERocketPartsType::ERP_Cowling);
		}
	}
}

void AA_CZ3A::OnOverlapCThreeSBox(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor && OtherActor != this)
	{
		AA_SinglePart* SingleActor = Cast<AA_SinglePart>(OtherActor);
		if(SingleActor)
		{
			CheckMeshCollsion(SingleActor, CoreThreeLevelsC, ERocketPartsType::ERP_CoreThreeLevels);
		}
	}
}

void AA_CZ3A::OnOverlapCTwoSBox(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor && OtherActor != this)
	{
		AA_SinglePart* SingleActor = Cast<AA_SinglePart>(OtherActor);
		if(SingleActor)
		{
			CheckMeshCollsion(SingleActor, CoreTwoLevelsC, ERocketPartsType::ERP_CoreTwoLevels);
		}
	}
}

void AA_CZ3A::ShowAllMesh()
{
	Super::ShowAllMesh();
	CoreOneLevelC->SetHiddenInGame(false);
	CowlingC->SetHiddenInGame(false);
	CoreThreeLevelsC->SetHiddenInGame(false);
	CoreTwoLevelsC->SetHiddenInGame(false);
}
