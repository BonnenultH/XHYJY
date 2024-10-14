// Fill out your copyright notice in the Description page of Project Settings.


#include "Scene/A_CZ5B.h"

#include "Components/BoxComponent.h"
#include "Scene/A_SinglePart.h"

void AA_CZ5B::BeginPlay()
{
	Super::BeginPlay();
	Cowling->OnComponentBeginOverlap.AddDynamic(this, &AA_CZ5B::OnOverlapCowlingBox);
	CoreOneLevel->OnComponentBeginOverlap.AddDynamic(this, &AA_CZ5B::OnOverlapCoreOneLevelBox);
	Rollboosters->OnComponentBeginOverlap.AddDynamic(this, &AA_CZ5B::OnOverlapRollboostersBox);
	Rollboosters2->OnComponentBeginOverlap.AddDynamic(this, &AA_CZ5B::OnOverlapRollboostersBox);
	Rollboosters3->OnComponentBeginOverlap.AddDynamic(this, &AA_CZ5B::OnOverlapRollboostersBox);
	Rollboosters4->OnComponentBeginOverlap.AddDynamic(this, &AA_CZ5B::OnOverlapRollboostersBox);
}

void AA_CZ5B::OnOverlapCowlingBox(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                  UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor && OtherActor != this)
	{
		AA_SinglePart* SingleActor = Cast<AA_SinglePart>(OtherActor);
		if(SingleActor)
		{
			CheckMeshCollsion(SingleActor, CowlingS, ERocketPartsType::ERP_Cowling);
		}
	}
}

void AA_CZ5B::OnOverlapCoreOneLevelBox(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor && OtherActor != this)
	{
		AA_SinglePart* SingleActor = Cast<AA_SinglePart>(OtherActor);
		if(SingleActor)
		{
			CheckMeshCollsion(SingleActor, CoreOneLevelS, ERocketPartsType::ERP_CoreOneLevel);
		}
	}
}


void AA_CZ5B::OnOverlapRollboostersBox(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor && OtherActor != this)
	{
		AA_SinglePart* SingleActor = Cast<AA_SinglePart>(OtherActor);
		if(SingleActor)
		{
			TArray<UStaticMeshComponent*> MeshArry;
			MeshArry.Add(RollboostersS);
			MeshArry.Add(RollboostersS2);
			MeshArry.Add(RollboostersS3);
			MeshArry.Add(RollboostersS4);
			CheckMeshCollsion(SingleActor, MeshArry, ERocketPartsType::ERP_Boosters);
		}
	}
}

void AA_CZ5B::ShowAllMesh()
{
	Super::ShowAllMesh();

	RollboostersS->SetHiddenInGame(false);
	RollboostersS2->SetHiddenInGame(false);
	RollboostersS3->SetHiddenInGame(false);
	RollboostersS4->SetHiddenInGame(false);
	CoreOneLevelS->SetHiddenInGame(false);
	CowlingS->SetHiddenInGame(false);
}
