// Fill out your copyright notice in the Description page of Project Settings.


#include "Scene/A_CZ2D.h"

#include "Components/BoxComponent.h"
#include "Scene/A_SinglePart.h"

void AA_CZ2D::BeginPlay()
{
	Super::BeginPlay();

	Cowling->OnComponentBeginOverlap.AddDynamic(this, &AA_CZ2D::OnOverlapCowlingBox);
	CoreOneLevel->OnComponentBeginOverlap.AddDynamic(this, &AA_CZ2D::OnOverlapCoreOneLevelBox);
	CoreTwoLevels->OnComponentBeginOverlap.AddDynamic(this, &AA_CZ2D::OnOverlapCoreTwoLevelsBox);

	CoreTwoLevelsS->SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);
	CoreOneLevelS->SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);
	CowlingS->SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);
	
}

void AA_CZ2D::OnOverlapCowlingBox(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor && OtherActor != this)
	{
		CheckMeshCollsion(CowlingS, ERocketPartsType::ERP_Cowling);
	}
}

void AA_CZ2D::OnOverlapCoreOneLevelBox(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor && OtherActor != this)
	{
		CheckMeshCollsion(CoreOneLevelS, ERocketPartsType::ERP_CoreOneLevel);
	}
}

void AA_CZ2D::OnOverlapCoreTwoLevelsBox(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor && OtherActor != this)
	{
		CheckMeshCollsion(CoreTwoLevelsS, ERocketPartsType::ERP_CoreTwoLevels);
	}
}


void AA_CZ2D::ShowAllMesh()
{
	Super::ShowAllMesh();

	CoreTwoLevelsS->SetHiddenInGame(false);
	CoreOneLevelS->SetHiddenInGame(false);
	CowlingS->SetHiddenInGame(false);
}
