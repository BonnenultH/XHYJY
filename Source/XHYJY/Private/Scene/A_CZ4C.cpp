// Fill out your copyright notice in the Description page of Project Settings.


#include "Scene/A_CZ4C.h"

#include "Components/BoxComponent.h"
#include "Scene/A_SinglePart.h"

void AA_CZ4C::BeginPlay()
{
	Super::BeginPlay();

	CoreOneLevel->OnComponentBeginOverlap.AddDynamic(this, &AA_CZ4C::OnOverlapCOneSBox);
	Cowling->OnComponentBeginOverlap.AddDynamic(this, &AA_CZ4C::OnOverlapCowBox);
	CoreThreeLevels->OnComponentBeginOverlap.AddDynamic(this, &AA_CZ4C::OnOverlapCThreeSBox);
	CoreTwoLevels->OnComponentBeginOverlap.AddDynamic(this, &AA_CZ4C::OnOverlapCTwoSBox);
}

void AA_CZ4C::OnOverlapCOneSBox(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
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

void AA_CZ4C::OnOverlapCowBox(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
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

void AA_CZ4C::OnOverlapCThreeSBox(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
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

void AA_CZ4C::OnOverlapCTwoSBox(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor && OtherActor != this)
	{
		AA_SinglePart* SingleActor = Cast<AA_SinglePart>(OtherActor);
		if(SingleActor)
		{
			CheckMeshCollsion(SingleActor, CoreThreeLevelsC, ERocketPartsType::ERP_CoreTwoLevels);
		}
	}
}

void AA_CZ4C::ShowAllMesh()
{
	Super::ShowAllMesh();

	CoreOneLevelC->SetHiddenInGame(false);
	CowlingC->SetHiddenInGame(false);
	CoreThreeLevelsC->SetHiddenInGame(false);
	CoreTwoLevelsC->SetHiddenInGame(false);
}
