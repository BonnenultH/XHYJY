// Fill out your copyright notice in the Description page of Project Settings.


#include "Scene/A_CZ3C.h"
#include "Components/BoxComponent.h"
#include "Scene/A_SinglePart.h"


// Sets default values
AA_CZ3C::AA_CZ3C()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AA_CZ3C::BeginPlay()
{
	Super::BeginPlay();
	COneS_BoxC->OnComponentBeginOverlap.AddDynamic(this, &AA_CZ3C::OnOverlapCOneSBox);
	RB1_BoxC->OnComponentBeginOverlap.AddDynamic(this, &AA_CZ3C::OnOverlapRBBox);
	RB2_BoxC->OnComponentBeginOverlap.AddDynamic(this, &AA_CZ3C::OnOverlapRBBox);
	Cow_BoxC->OnComponentBeginOverlap.AddDynamic(this, &AA_CZ3C::OnOverlapCowBox);
	CThreeS_BoxC->OnComponentBeginOverlap.AddDynamic(this, &AA_CZ3C::OnOverlapCThreeSBox);
	CTwoS_BoxC->OnComponentBeginOverlap.AddDynamic(this, &AA_CZ3C::OnOverlapCTwoSBox);
}

// Called every frame
void AA_CZ3C::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AA_CZ3C::OnOverlapCOneSBox(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor && OtherActor != this)
	{
		AA_SinglePart* SingleActor = Cast<AA_SinglePart>(OtherActor);
		if(SingleActor)
		{
			CheckMeshCollsion(SingleActor, CoreOneStageC, ERocketPartsType::ERP_CoreOneLevel);
		}
	}
}

void AA_CZ3C::OnOverlapRBBox(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor && OtherActor != this)
	{
		AA_SinglePart* SingleActor = Cast<AA_SinglePart>(OtherActor);
		if(SingleActor)
		{
			TArray<UStaticMeshComponent*> MeshArry;
			MeshArry.Add(RollBooster1C);
			MeshArry.Add(RollBooster2C);
			CheckMeshCollsion(SingleActor, MeshArry, ERocketPartsType::ERP_Boosters);
		}
	}
}

void AA_CZ3C::OnOverlapCowBox(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
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

void AA_CZ3C::OnOverlapCThreeSBox(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor && OtherActor != this)
	{
		AA_SinglePart* SingleActor = Cast<AA_SinglePart>(OtherActor);
		if(SingleActor)
		{
			CheckMeshCollsion(SingleActor, CoreThreeStageC, ERocketPartsType::ERP_CoreThreeLevels);
		}
	}
}

void AA_CZ3C::OnOverlapCTwoSBox(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor && OtherActor != this)
	{
		AA_SinglePart* SingleActor = Cast<AA_SinglePart>(OtherActor);
		if(SingleActor)
		{
			CheckMeshCollsion(SingleActor, CoreTwoStageC, ERocketPartsType::ERP_CoreTwoLevels);
		}
	}
}

void AA_CZ3C::ShowAllMesh()
{
	CoreOneStageC->SetHiddenInGame(false);
	RollBooster1C->SetHiddenInGame(false);
	RollBooster2C->SetHiddenInGame(false);
	CowlingC->SetHiddenInGame(false);
	CoreThreeStageC->SetHiddenInGame(false);
	CoreTwoStageC->SetHiddenInGame(false);
}
