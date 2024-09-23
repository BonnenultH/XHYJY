// Fill out your copyright notice in the Description page of Project Settings.


#include "GM/VDPawn.h"
#include "Manager/ResourceManager.h"
#include "Manager/UIManager.h"
#include "Manager/SceneManager.h"
#include "Camera/CameraComponent.h"

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
	
	Camera = GetComponentByClass<UCameraComponent>();
	HoistMesh = GetComponentByClass<UStaticMeshComponent>();
	
	UserInfoData.IDName			= L"不可思议的佳佳";
	UserInfoData.Accomplishment = L"型号研究院高级研究员";
	UserInfoData.Grades			= L"720";
	UserInfoData.HTQNumbers		= L"30";
	UserInfoData.Gender			= EGender::EG_Woman;
	
	CreateManagers();
	InitManagers();
}

void AVDPawn::CreateManagers()
{
	ResourceManager = NewObject<AResourceManager>(this);
	UIManager = GetWorld()->SpawnActor<AUIManager>();
	SceneManager = NewObject<ASceneManager>(this);
}

void AVDPawn::InitManagers()
{
	ResourceManager->InitManager();
	UIManager->InitManager();
	SceneManager->InitManager();
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

