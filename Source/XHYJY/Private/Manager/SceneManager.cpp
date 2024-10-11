// Fill out your copyright notice in the Description page of Project Settings.


#include "Manager/SceneManager.h"
#include "Camera/CameraActor.h"
#include "Kismet/GameplayStatics.h"
#include "Manager/UIManager.h"
#include "GameFramework/SpringArmComponent.h"
#include "Scene/A_SinglePart.h"
#include "Scene/A_CZ3C.h"
#include "UMG/WHoisting.h"

void ASceneManager::InitManager()
{
	Super::InitManager();
	UClass* MyActorClass = LoadClass<AActor>(nullptr, TEXT("Blueprint'/Game/Model/Rockets/CZ-3C/CZ3C_Actor.CZ3C_Actor_C'"));
	TargetRocketBPMap.Add(ERocketType::ERT_CZ_3C, MyActorClass);
	MyActorClass = LoadClass<AActor>(nullptr, TEXT("Blueprint'/Game/Model/Rockets/CZ-3B/CZ3B_Actor.CZ3B_Actor_C'"));
	TargetRocketBPMap.Add(ERocketType::ERT_CZ_3B, MyActorClass);
	
}

void ASceneManager::InitSingleMesh()
{
	UIDiagram = UIManager->GetDiagramMap(UIManager->SelectTaskItem->GetCheapestRocket());
	for(auto Item: UIDiagram->RocketParts)
	{
		SinglePartLocation = FVector(SinglePartLocation.X,SinglePartLocation.Y - 500, SinglePartLocation.Z);
		AA_SinglePart* SinglePart =	GetWorld()->SpawnActor<AA_SinglePart>(SinglePartLocation,FRotator(0,0,0));
		SinglePart->InitMesh(Item.DispatchMesh, Item.RocketPartsType, Item.RocketPartName);
		SinglePart->OnRocketClick.AddUObject(this, &ASceneManager::SingleMeshClick);
		SingleArray.Add(SinglePart);
	}
}

void ASceneManager::InitTargetRocket()
{
	TArray<AActor*> YSCArry;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(),"YSC", YSCArry);
	UClass* MyClass = TargetRocketBPMap[UIManager->SelectTaskItem->GetCheapestRocket()];
	TargetRocket = GetWorld()->SpawnActor<ABaseCZActor>(MyClass,FVector::ZeroVector,FRotator::ZeroRotator);
	TargetRocket->AttachToActor(YSCArry[0], FAttachmentTransformRules::KeepRelativeTransform);
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
		UWHoisting* Widget = Cast<UWHoisting>(UIManager->WidgetMap[UIManager->CurWidgetType]);
		Widget->PlaySelectWrong();
		
		FTimerHandle Delaypop;
		GetWorld()->GetTimerManager().SetTimer(Delaypop, this, &ASceneManager::DelaySelect, 3.5f);
		return;
	}

	UE_LOG(LogTemp, Log, TEXT("检查正确！"))
	ClickedNum++;
	CurSingleMesh->AbleRotatorSelf();
	CurSingleMesh->AbleUpSelf();
	FVector MeshLocation = CurSingleMesh->GetActorLocation();
	VDPawn->SetActorLocation(FVector(MeshLocation.X,MeshLocation.Y - 1500, 1200));
	
	UGameplayStatics::GetPlayerController(this, 0)->SetViewTargetWithBlend(VDPawn, 1);
	FTimerHandle Delaypop;
	GetWorld()->GetTimerManager().SetTimer(Delaypop, this, &ASceneManager::DelayAttach, 0.5f);
}

void ASceneManager::DelayAttach()
{
	CurSingleMesh->AttachToComponent(VDPawn->MySpringArm, FAttachmentTransformRules::KeepWorldTransform);
	VDPawn->bMove = true;
}

void ASceneManager::DelaySelect()
{
	SetSelectable(true);
}

void ASceneManager::AssemblySuccess()
{
	SwitchViewByFront();

	if(TargetRocket)
	{
		TargetRocket->ShowAllMesh();
	}
}

void ASceneManager::SwitchViewByHoist()
{
	TArray<AActor*> AnotherPlayerCameras;
	UGameplayStatics::GetAllActorsOfClassWithTag(this, ACameraActor::StaticClass(),"FrontCamera",AnotherPlayerCameras);
	FrontCamera = AnotherPlayerCameras[0];
	
	TArray<AActor*> MyPlayerCameras;
	UGameplayStatics::GetAllActorsOfClassWithTag(this, ACameraActor::StaticClass(),"MainCamera",MyPlayerCameras);
	HoistCamera = MyPlayerCameras[0];
	UGameplayStatics::GetPlayerController(this, 0)->SetViewTargetWithBlend(HoistCamera);
}

void ASceneManager::SwitchViewByFront()
{
	if(!FrontCamera)
		return;
	
	UGameplayStatics::GetPlayerController(this, 0)->SetViewTargetWithBlend(FrontCamera,1);
}

void ASceneManager::BindHoistUIDelegate()
{
	UWHoisting* Widget = Cast<UWHoisting>(UIManager->WidgetMap[UIManager->CurWidgetType]);
	Widget->OnAnimEnd.BindUObject(this, &ASceneManager::CheckClickMesh);
}


