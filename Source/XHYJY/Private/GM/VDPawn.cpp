// Fill out your copyright notice in the Description page of Project Settings.


#include "GM/VDPawn.h"
#include "Manager/ResourceManager.h"
#include "Manager/UIManager.h"

// Sets default values
AVDPawn::AVDPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AVDPawn::BeginPlay()
{
	Super::BeginPlay();
	CreateManagers();
	InitManagers();
}

void AVDPawn::CreateManagers()
{
	ResourceManager = NewObject<AResourceManager>(this);
	UIManager = NewObject<AUIManager>(this);
}

void AVDPawn::InitManagers()
{
	ResourceManager->InitManager();
	UIManager->InitManager();
}

// Called every frame
void AVDPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AVDPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

