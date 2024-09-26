// Fill out your copyright notice in the Description page of Project Settings.


#include "Scene/A_DispatchParts.h"

#include "GM/VDPawn.h"
#include "Kismet/GameplayStatics.h"
#include "Manager/UIManager.h"


// Sets default values
AA_DispatchParts::AA_DispatchParts()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AVDPawn* Pawn = Cast<AVDPawn>(UGameplayStatics::GetPlayerPawn(this, 0));
	if(Pawn)
	{
		UIManager = Pawn->UIManager;
		ResourceManager = Pawn->ResourceManager;
	}
	CreateDefaultSubobject<USceneComponent>(TEXT("SceneComp"));

	if(UIManager && ResourceManager)
	{
		InitMeshArray();
	}
}

// Called when the game starts or when spawned
void AA_DispatchParts::BeginPlay()
{
	Super::BeginPlay();
	
	for (int i = 0; i < SingleRocketPartArray.Num(); i++)
	{
		Location = FVector(Location.X,Location.Y - 500, Location.Z);
		AA_SinglePart* SinglePart =	GetWorld()->SpawnActor<AA_SinglePart>(Location,FRotator(0));
		SinglePart->RocketDispatchMesh->SetStaticMesh(SingleRocketPartArray[i].DispatchMesh);
		SinglePart->RocketPartType = SingleRocketPartArray[i].RocketPartsType;
		SinglePart->RocketPartName = SingleRocketPartArray[i].RocketPartName;
		SinglePartsArray.Add(SinglePart);
	}
	
}

void AA_DispatchParts::InitMeshArray()
{
	UIDiagram = UIManager->GetDiagramMap(UIManager->SelectTaskItem->GetCheapestRocket());
	for (int i = 0; i < UIDiagram->RocketParts.Num(); i++)
	{
		SingleRocketPartArray.Add(UIDiagram->RocketParts[i]);
	}
}

// Called every frame
void AA_DispatchParts::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

