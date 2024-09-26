// Fill out your copyright notice in the Description page of Project Settings.


#include "Scene/A_SinglePart.h"

// Sets default values
AA_SinglePart::AA_SinglePart()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RocketDispatchMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RocketDispatchMesh"));
	SetRootComponent(RocketDispatchMesh);
}

// Called when the game starts or when spawned
void AA_SinglePart::BeginPlay()
{
	Super::BeginPlay();
	
	
}

void AA_SinglePart::NotifyActorOnClicked(FKey ButtonPressed)
{
	Super::NotifyActorOnClicked(ButtonPressed);
	MouseRocketClickReturn.Broadcast(this);
}


// Called every frame
void AA_SinglePart::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

