// Fill out your copyright notice in the Description page of Project Settings.


#include "Manager/SceneManager.h"
#include "Camera/CameraActor.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Manager/UIManager.h"
#include "CineCameraComponent.h"
#include "Scene/A_SinglePart.h"
#include "UMG/WHoisting.h"

class UCineCameraComponent;

void ASceneManager::InitManager()
{
	Super::InitManager();
}

void ASceneManager::InitSingleMesh()
{
	UIDiagram = UIManager->GetDiagramMap(UIManager->SelectTaskItem->GetCheapestRocket());
	for(auto Item: UIDiagram->RocketParts)
	{
		SinglePartLocation = FVector(SinglePartLocation.X,SinglePartLocation.Y - 500, SinglePartLocation.Z);
		AA_SinglePart* SinglePart =	GetWorld()->SpawnActor<AA_SinglePart>(SinglePartLocation,FRotator(0));
		SinglePart->InitMesh(Item.DispatchMesh, Item.RocketPartsType, Item.RocketPartName);
		SinglePart->OnRocketClick.AddUObject(this, &ASceneManager::SingleMeshClick);
		SingleArray.Add(SinglePart);
	}
}

void ASceneManager::SingleMeshClick(AA_SinglePart* SinglePart)
{
	CurSingleMesh = SinglePart;
}

void ASceneManager::CheckClickMesh()
{
	if(CurSingleMesh->GetSingleMeshType() != UIDiagram->RocketParts[ClickedNum].RocketPartsType)
	{
		UE_LOG(LogTemp, Log, TEXT("检查错误！"))
		return;
	}

	UE_LOG(LogTemp, Log, TEXT("检查正确！"))
	ClickedNum++;
	
	UCineCameraComponent* Camera = HoistCamera->GetComponentByClass<UCineCameraComponent>();
	Camera->SetActive(false);
	VDPawn->HoistMesh->SetStaticMesh(CurSingleMesh->GetStaticMesh());
	UGameplayStatics::GetPlayerController(this, 0)->SetViewTargetWithBlend(VDPawn, 1);
}

void ASceneManager::SwitchViewByHoist()
{
	TArray<AActor*> MyPlayerCameras;
	UGameplayStatics::GetAllActorsOfClassWithTag(this, ACameraActor::StaticClass(),"MainCamera",MyPlayerCameras);
	HoistCamera = MyPlayerCameras[0];
	VDPawn->Camera->SetActive(false);
	UGameplayStatics::GetPlayerController(this, 0)->SetViewTargetWithBlend(HoistCamera);
}



void ASceneManager::BindHoistUIDelegate()
{
	UWHoisting* Widget = Cast<UWHoisting>(UIManager->WidgetMap[UIManager->CurWidgetType]);
	Widget->OnAnimEnd.BindUObject(this, &ASceneManager::CheckClickMesh);
}

