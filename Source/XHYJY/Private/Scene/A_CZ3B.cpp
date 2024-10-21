// Fill out your copyright notice in the Description page of Project Settings.


#include "Scene/A_CZ3B.h"
#include "Components/BoxComponent.h"
#include "Scene/A_SinglePart.h"

// Sets default values
AA_CZ3B::AA_CZ3B()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
}

// Called when the game starts or when spawned
void AA_CZ3B::BeginPlay()
{
	Super::BeginPlay();
	Cowling->OnComponentBeginOverlap.AddDynamic(this, &AA_CZ3B::OnOverlapCowlingBox);
	CoreOneLevel->OnComponentBeginOverlap.AddDynamic(this, &AA_CZ3B::OnOverlapCoreOneLevelBox);
	CoreTwoLevels->OnComponentBeginOverlap.AddDynamic(this, &AA_CZ3B::OnOverlapCoreTwoLevelsBox);
	CoreThreeLevels->OnComponentBeginOverlap.AddDynamic(this, &AA_CZ3B::OnOverlapCoreThreeLevelsBox);
	Rollboosters->OnComponentBeginOverlap.AddDynamic(this, &AA_CZ3B::OnOverlapRollboostersBox);
	Rollboosters2->OnComponentBeginOverlap.AddDynamic(this, &AA_CZ3B::OnOverlapRollboostersBox);
	Rollboosters3->OnComponentBeginOverlap.AddDynamic(this, &AA_CZ3B::OnOverlapRollboostersBox);
	Rollboosters4->OnComponentBeginOverlap.AddDynamic(this, &AA_CZ3B::OnOverlapRollboostersBox);

	RollboostersC->SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);
	RollboostersC2->SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);
	RollboostersC3->SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);
	RollboostersC4->SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);
	CoreThreeLevelsC->SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);
	CoreTwoLevelsC->SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);
	CoreOneLevelC->SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);
	CowlingC->SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);
}

// Called every frame
void AA_CZ3B::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AA_CZ3B::OnOverlapCowlingBox(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor && OtherActor != this)
	{
		CheckMeshCollsion(CowlingC, ERocketPartsType::ERP_Cowling);
	}
}

void AA_CZ3B::OnOverlapCoreOneLevelBox(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor && OtherActor != this)
	{
		AA_SinglePart* SingleActor = Cast<AA_SinglePart>(OtherActor);
		if(SingleActor)
		{
			CheckMeshCollsion(CoreOneLevelC, ERocketPartsType::ERP_CoreOneLevel);
		}
	}
}

void AA_CZ3B::OnOverlapCoreTwoLevelsBox(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor && OtherActor != this)
	{
		CheckMeshCollsion(CoreTwoLevelsC, ERocketPartsType::ERP_CoreTwoLevels);
	}
}

void AA_CZ3B::OnOverlapCoreThreeLevelsBox(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor && OtherActor != this)
	{
		CheckMeshCollsion(CoreThreeLevelsC, ERocketPartsType::ERP_CoreThreeLevels);
	}
}

void AA_CZ3B::OnOverlapRollboostersBox(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor && OtherActor != this)
	{
		
		TArray<UStaticMeshComponent*> MeshArry;
		MeshArry.Add(RollboostersC);
		MeshArry.Add(RollboostersC2);
		MeshArry.Add(RollboostersC3);
		MeshArry.Add(RollboostersC4);
		CheckMeshCollsion(MeshArry, ERocketPartsType::ERP_Boosters);
		
	}
}

void AA_CZ3B::ShowAllMesh()
{
	Super::ShowAllMesh();

	RollboostersC->SetHiddenInGame(false);
	RollboostersC2->SetHiddenInGame(false);
	RollboostersC3->SetHiddenInGame(false);
	RollboostersC4->SetHiddenInGame(false);
	CoreThreeLevelsC->SetHiddenInGame(false);
	CoreTwoLevelsC->SetHiddenInGame(false);
	CoreOneLevelC->SetHiddenInGame(false);
	CowlingC->SetHiddenInGame(false);
	
}






