// Fill out your copyright notice in the Description page of Project Settings.


#include "Scene/A_SinglePart.h"
#include "GM/VDPawn.h"
#include "Kismet/GameplayStatics.h"
#include "Manager/SceneManager.h"


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
	AVDPawn* Pawn = nullptr;
	Pawn = Cast<AVDPawn>(UGameplayStatics::GetPlayerPawn(this, 0));
	if(Pawn->SceneManager->GetSelectable())
	{
		Super::NotifyActorOnClicked(ButtonPressed);
		OnRocketClick.Broadcast(this);
		Pawn->SceneManager->SetSelectable(false);
	}
}

void AA_SinglePart::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	UE_LOG(LogTemp, Log, TEXT("我撞到了"))
}


// Called every frame
void AA_SinglePart::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if(bAbleRotator)
	{
		FRotator NewRotator = FRotator(GetActorRotation().Pitch + 2, GetActorRotation().Yaw, GetActorRotation().Roll);
		SetActorRotation(NewRotator);
		if(GetActorRotation().Pitch > 89)
		{
			SetActorRotation(FRotator(90, GetActorRotation().Yaw, GetActorRotation().Roll));
			bAbleRotator = false;
		}
	}

	if(bAbleUp)
	{
		FVector NewLocation = FVector(GetActorLocation().X, GetActorLocation().Y, GetActorLocation().Z + 10);
		SetActorLocation(NewLocation);
		if(GetActorLocation().Z > 1199)
		{
			SetActorLocation(FVector(GetActorLocation().X, GetActorLocation().Y, 1200));
			bAbleUp = false;
		}
	}
	
}

void AA_SinglePart::InitMesh(UStaticMesh* Mesh, ERocketPartsType _RocketPartType, FString _RocketPartName)
{
	RocketDispatchMesh->SetStaticMesh(Mesh);
	RocketPartType = _RocketPartType;
	RocketPartName = _RocketPartName;
}

void AA_SinglePart::AbleRotatorSelf()
{
	bAbleRotator = true;
}

void AA_SinglePart::AbleUpSelf()
{
	bAbleUp = true;
}



