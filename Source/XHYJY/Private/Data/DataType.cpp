// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/DataType.h"


// Sets default values
ADataType::ADataType()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADataType::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADataType::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

