// Fill out your copyright notice in the Description page of Project Settings.


#include "Scene/BaseCZActor.h"

#include "GM/VDPawn.h"
#include "Kismet/GameplayStatics.h"
#include "Manager/ResourceManager.h"
#include "Manager/SceneManager.h"
#include "Manager/UIManager.h"
#include "Scene/A_SinglePart.h"
#include "UMG/WHoisting.h"


// Sets default values
ABaseCZActor::ABaseCZActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABaseCZActor::BeginPlay()
{
	Super::BeginPlay();
	AVDPawn* Pawn = nullptr;
	Pawn = Cast<AVDPawn>(UGameplayStatics::GetPlayerPawn(this, 0));
	if(Pawn)
	{
		VDPawn			= Pawn;
		ResourceManager	= Pawn->ResourceManager;
		UIManager		= Pawn->UIManager;
		SceneManager	= Pawn->SceneManager;
	}
}

void ABaseCZActor::HoistSuccess()
{
	VDPawn->bMove = false;
	SceneManager->SwitchViewByFront();

	FTimerHandle TimeHandle;
	GetWorld()->GetTimerManager().SetTimer(TimeHandle,this, &ABaseCZActor::DelaySwitchView,5);
}

void ABaseCZActor::DelaySwitchView()
{
	SceneManager->SwitchViewByHoist();
	UWHoisting* Widget = Cast<UWHoisting>(UIManager->WidgetMap[UIManager->CurWidgetType]);
	Widget->HoistingProgress();
	Widget->PlaySelectPartAnim();
}

void ABaseCZActor::CheckMeshCollsion(AA_SinglePart* SingleActor, UStaticMeshComponent* TargetMesh, ERocketPartsType RightMeshType)
{
	if(SingleActor->GetSingleMeshType() == RightMeshType)
	{
		SingleActor->Destroy();
		TargetMesh->SetHiddenInGame(false);
		HoistSuccess();
	}
}

void ABaseCZActor::CheckMeshCollsion(AA_SinglePart* SingleActor, TArray<UStaticMeshComponent*> TargetMeshArry,
	ERocketPartsType RightMeshType)
{
	if(SingleActor->GetSingleMeshType() == RightMeshType)
	{
		SingleActor->Destroy();
		for(auto Mesh : TargetMeshArry)
		{
			Mesh->SetHiddenInGame(false);
		}
		HoistSuccess();
	}
}

// Called every frame
void ABaseCZActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

