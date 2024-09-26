// Fill out your copyright notice in the Description page of Project Settings.


#include "Manager/SceneManager.h"
#include "Scene/A_DispatchParts.h"
#include "Camera/CameraActor.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"

void ASceneManager::InitManager()
{
	Super::InitManager();
}

void ASceneManager::SwitchViewByHoist()
{
	TArray<AActor*> MyPlayerCameras;
	UGameplayStatics::GetAllActorsOfClassWithTag(this, ACameraActor::StaticClass(),"MainCamera",MyPlayerCameras);
	HoistCamera = MyPlayerCameras[0];
	
	VDPawn->Camera->SetActive(false);
	UGameplayStatics::GetPlayerController(this, 0)->SetViewTargetWithBlend(HoistCamera);
}

void ASceneManager::InitHoistRocketParts()
{
	DispatchParts = GetWorld()->SpawnActor<AA_DispatchParts>(FVector(-53.145418,987.363786,280.799904), FRotator(0));
}
