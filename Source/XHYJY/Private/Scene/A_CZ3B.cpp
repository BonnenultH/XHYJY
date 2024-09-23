// Fill out your copyright notice in the Description page of Project Settings.


#include "Scene/A_CZ3B.h"
#include "Components/BoxComponent.h"

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
	Box1->OnComponentBeginOverlap.AddDynamic(this, &AA_CZ3B::OnOverlapBox1);
}

// Called every frame
void AA_CZ3B::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AA_CZ3B::OnOverlapBox1(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == this)
	{
		return;
	}

	UE_LOG(LogTemp, Log, TEXT("触发了！"))
}



