// Fill out your copyright notice in the Description page of Project Settings.


#include "Manager/SceneManager.h"

#include "AssetTypeActions/AssetDefinition_SoundBase.h"
#include "Camera/CameraActor.h"
#include "Components/AudioComponent.h"
#include "Components/BoxComponent.h"
#include "Engine/StaticMeshActor.h"
#include "Kismet/GameplayStatics.h"
#include "Manager/UIManager.h"
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
	MyActorClass = LoadClass<AActor>(nullptr, TEXT("Blueprint'/Game/Model/Rockets/CZ-1/CZ1Actor.CZ1Actor_C'"));
	TargetRocketBPMap.Add(ERocketType::ERT_CZ_1, MyActorClass);
	MyActorClass = LoadClass<AActor>(nullptr, TEXT("Blueprint'/Game/Model/Rockets/CZ-5/CZ-5Actor.CZ-5Actor_C'"));
	TargetRocketBPMap.Add(ERocketType::ERT_CZ_5, MyActorClass);
	MyActorClass = LoadClass<AActor>(nullptr, TEXT("Blueprint'/Game/Model/Rockets/CZ-7/CZ-7Actor.CZ-7Actor_C'"));
	TargetRocketBPMap.Add(ERocketType::ERT_CZ_7, MyActorClass);
	MyActorClass = LoadClass<AActor>(nullptr, TEXT("Blueprint'/Game/Model/Rockets/CZ-2D/CZ-2DActor.CZ-2DActor_C'"));
	TargetRocketBPMap.Add(ERocketType::ERT_CZ_2D, MyActorClass);
	MyActorClass = LoadClass<AActor>(nullptr, TEXT("Blueprint'/Game/Model/Rockets/CZ-2F/CZ-2FActor.CZ-2FActor_C'"));
	TargetRocketBPMap.Add(ERocketType::ERT_CZ_2F, MyActorClass);
	MyActorClass = LoadClass<AActor>(nullptr, TEXT("Blueprint'/Game/Model/Rockets/CZ-3A/CZ-3AActor.CZ-3AActor_C'"));
	TargetRocketBPMap.Add(ERocketType::ERT_CZ_3A, MyActorClass);
	MyActorClass = LoadClass<AActor>(nullptr, TEXT("Blueprint'/Game/Model/Rockets/CZ-4C/CZ_4CActor.CZ_4CActor_C'"));
	TargetRocketBPMap.Add(ERocketType::ERT_CZ_4C, MyActorClass);
	MyActorClass = LoadClass<AActor>(nullptr, TEXT("Blueprint'/Game/Model/Rockets/CZ-5B/CZ_5BActor.CZ_5BActor_C'"));
	TargetRocketBPMap.Add(ERocketType::ERT_CZ_5B, MyActorClass);

	PlayBGMSound();
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

void ASceneManager::InitDZJ()
{
	TArray<AActor*> DZJArray;
	UGameplayStatics::GetAllActorsOfClassWithTag(this, AStaticMeshActor::StaticClass(), "DZJ", DZJArray);
	DZJMesh = DZJArray[0];
	DZJOrignLocation = DZJMesh->GetActorLocation();
	
}

void ASceneManager::SingleMeshClick(AA_SinglePart* SinglePart)
{
	CurSingleMesh = SinglePart;
	TempMesh = SinglePart;
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
	
	DZJMesh->SetActorLocation(FVector(MeshLocation.X,MeshLocation.Y, 1200));
	VDPawn->SetActorLocation(FVector(MeshLocation.X,MeshLocation.Y, 1200));
	
	UGameplayStatics::GetPlayerController(this, 0)->SetViewTargetWithBlend(VDPawn, 1);
	FTimerHandle Delaypop;
	GetWorld()->GetTimerManager().SetTimer(Delaypop, this, &ASceneManager::DelayAttach, 1.0f);
}

void ASceneManager::DelayAttach()
{
	DZJMesh->AttachToComponent(VDPawn->MyBox, FAttachmentTransformRules::KeepWorldTransform);
	
	VDPawn->MyMesh->SetStaticMesh(CurSingleMesh->GetStaticMesh());
	VDPawn->RocketPartType = CurSingleMesh->GetSingleMeshType();
	CurSingleMesh->SetActorHiddenInGame(true);
	CurSingleMesh->SetActorEnableCollision(false);
	VDPawn->bMove = true;
	FTimerHandle DelayDestrouSingle;
	GetWorld()->GetTimerManager().SetTimer(DelayDestrouSingle, this, &ASceneManager::DestroySingle, 3.0f);
}

void ASceneManager::DelaySelect()
{
	SetSelectable(true);
}

void ASceneManager::DestroySingle()
{
	TempMesh->Destroy();
}

void ASceneManager::PlayBGMSound()
{
	if(bStartUIBGM)
	{
		AudioComponent = UGameplayStatics::SpawnSound2D(this, ResourceManager->BGMSound);
	}
	else
	{
		AudioComponent->Stop();
	}
}


void ASceneManager::PlayFactorySound()
{
	UGameplayStatics::PlaySound2D(this, ResourceManager->FactoryOpen);
}

void ASceneManager::PlayHoistBG()
{
	if(bHoist)
	{
		AudioComponent = UGameplayStatics::SpawnSound2D(this, ResourceManager->FactoryBG);
	}
	else
	{
		AudioComponent->Stop();
	}
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

void ASceneManager::DZJReturnLocation()
{
	DZJMesh->DetachRootComponentFromParent();
	DZJMesh->SetActorLocation(DZJOrignLocation);
}


