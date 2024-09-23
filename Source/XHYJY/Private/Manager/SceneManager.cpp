// Fill out your copyright notice in the Description page of Project Settings.


#include "Manager/SceneManager.h"
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
