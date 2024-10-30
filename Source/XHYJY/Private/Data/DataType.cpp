// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/DataType.h"
#include "GM/VDPawn.h"
#include "Kismet/GameplayStatics.h"
#include "Manager/UIManager.h"

ERocketType UItemTask::GetCheapestRocket()
{
	if(CheapestRocketType != ERocketType::ERT_None)
	{
		return CheapestRocketType;
	}
		
	int32 Price = 0;
	for(auto Rocket : RocketArry)
	{
		AVDPawn* Pawn = Cast<AVDPawn>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
		FRocketTable* RocketData = Pawn->UIManager->GetRocketData(Rocket.RocketType);
		if(Rocket.bRight)
		{
			if(Price > RocketData->Price || Price == 0)
			{
				Price = RocketData->Price;
				CheapestRocketType = RocketData->RocketType;
			}
		}
	}
	return CheapestRocketType;
}

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

