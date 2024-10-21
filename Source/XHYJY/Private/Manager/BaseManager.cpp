// Fill out your copyright notice in the Description page of Project Settings.


#include "Manager/BaseManager.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABaseManager::ABaseManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABaseManager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseManager::InitManager()
{
	AVDPawn* Pawn = nullptr;
	Pawn = Cast<AVDPawn>(UGameplayStatics::GetPlayerPawn(this, 0));
	if(Pawn)
	{
		VDPawn			= Pawn;
		ResourceManager = Pawn->ResourceManager;
		UIManager		= Pawn->UIManager;
		SceneManager	= Pawn->SceneManager;
	}
}

