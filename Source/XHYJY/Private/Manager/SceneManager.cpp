// Fill out your copyright notice in the Description page of Project Settings.


#include "Manager/SceneManager.h"
#include "Camera/CameraActor.h"
#include "Components/AudioComponent.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Manager/UIManager.h"
#include "Scene/A_SinglePart.h"
#include "Scene/A_CZ3C.h"
#include "UMG/WHoisting.h"


void ASceneManager::InitManager()
{
	Super::InitManager();

	UClass* CZ3CActor;
	UClass* CZ3BActor;
	UClass* CZ1Actor;
	UClass* CZ5Actor;
	UClass* CZ7Actor;
	UClass* CZ2DActor;

	do
	{
		
		CZ3CActor = LoadClass<AActor>(nullptr, TEXT("/Script/Engine.Blueprint'/Game/Model/Rockets/CZ-3C/CZ3C_Actor.CZ3C_Actor_C'"));
		
	}while(!CZ3CActor);
	if(CZ3CActor)
	{
		TargetRocketBPMap.Add(ERocketType::ERT_CZ_3C, CZ3CActor);
	}

	do
	{
		CZ3BActor = LoadClass<AActor>(nullptr, TEXT("Blueprint'/Game/Model/Rockets/CZ-3B/CZ3B_Actor.CZ3B_Actor_C'"));
		
	}while(!CZ3BActor);
	if(CZ3BActor)
	{
		TargetRocketBPMap.Add(ERocketType::ERT_CZ_3B, CZ3BActor);
		TargetRocketBPMap.Add(ERocketType::ERT_CZ_3BG2, CZ3BActor);
		TargetRocketBPMap.Add(ERocketType::ERT_CZ_3BG3, CZ3BActor);
	}
	
	do
	{
		CZ1Actor = LoadClass<AActor>(nullptr, TEXT("Blueprint'/Game/Model/Rockets/CZ-1/CZ1Actor.CZ1Actor_C'"));
		
	}while(!CZ1Actor);
	if(CZ1Actor)
	{
		TargetRocketBPMap.Add(ERocketType::ERT_CZ_1, CZ1Actor);
	}
	
	do
	{
		CZ5Actor = LoadClass<AActor>(nullptr, TEXT("Blueprint'/Game/Model/Rockets/CZ-5/CZ-5Actor.CZ-5Actor_C'"));
		
	}while(!CZ5Actor);
	if(CZ5Actor)
	{
		TargetRocketBPMap.Add(ERocketType::ERT_CZ_5, CZ5Actor);
	}
	
	do
	{
		CZ7Actor = LoadClass<AActor>(nullptr, TEXT("Blueprint'/Game/Model/Rockets/CZ-7/CZ-7Actor.CZ-7Actor_C'"));
		
	}while(!CZ7Actor);
	if(CZ7Actor)
	{
		TargetRocketBPMap.Add(ERocketType::ERT_CZ_7, CZ7Actor);
	}

	do
	{
		CZ2DActor = LoadClass<AActor>(nullptr, TEXT("Blueprint'/Game/Model/Rockets/CZ-2D/CZ-2DActor.CZ-2DActor_C'"));
		
	}while(!CZ2DActor);
	if(CZ2DActor)
	{
		TargetRocketBPMap.Add(ERocketType::ERT_CZ_2D, CZ2DActor);
	}
	
	UClass* CZ2FActor;
	UClass* CZ3AActor;
	UClass* CZ4CActor;
	UClass* CZ5BActor;

	do
	{
		CZ2FActor = LoadClass<AActor>(nullptr, TEXT("Blueprint'/Game/Model/Rockets/CZ-2F/CZ-2FActor.CZ-2FActor_C'"));
		
	}while(!CZ2FActor);
	if(CZ2FActor)
	{
		TargetRocketBPMap.Add(ERocketType::ERT_CZ_2F, CZ2FActor);
	}

	do
	{
		CZ3AActor = LoadClass<AActor>(nullptr, TEXT("Blueprint'/Game/Model/Rockets/CZ-3A/CZ-3AActor.CZ-3AActor_C'"));
		
	}while(!CZ3AActor);
	if(CZ3AActor)
	{
		TargetRocketBPMap.Add(ERocketType::ERT_CZ_3A, CZ3AActor);
	}
	
	do
	{
		CZ4CActor = LoadClass<AActor>(nullptr, TEXT("Blueprint'/Game/Model/Rockets/CZ-4C/CZ_4CActor.CZ_4CActor_C'"));
		
	}while(!CZ4CActor);
	if(CZ4CActor)
	{
		TargetRocketBPMap.Add(ERocketType::ERT_CZ_4C, CZ4CActor);
	}

	do
	{
		CZ5BActor = LoadClass<AActor>(nullptr, TEXT("Blueprint'/Game/Model/Rockets/CZ-5B/CZ_5BActor.CZ_5BActor_C'"));
		
	}while(!CZ5BActor);
	if(CZ5BActor)
	{
		TargetRocketBPMap.Add(ERocketType::ERT_CZ_5B, CZ5BActor);
	}
	

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

void ASceneManager::FindNeedMesh()
{
	UClass* MyClass;
	do
	{
		MyClass = TargetRocketBPMap[UIManager->SelectTaskItem->GetCheapestRocket()];
	}
	while (!MyClass);
	AActor* MyActor = GetWorld()->SpawnActor(MyClass,&FVector::ZeroVector,&FRotator::ZeroRotator);
	TargetRocket = Cast<ABaseCZActor>(MyActor);

	
	do
	{
		UGameplayStatics::GetAllActorsWithTag(GetWorld(),TEXT("YSC"), YscArry);
	}
	while (!YscArry[0]);
	
	do
	{
		UGameplayStatics::GetAllActorsWithTag(GetWorld(),TEXT("DZJ"), DZJArray);
		DZJMesh = DZJArray[0];
	}
	while (!DZJMesh);
	
	
}

void ASceneManager::InitTargetRocket()
{
	do
		{
			UGameplayStatics::GetAllActorsWithTag(GetWorld(),"YSC", YscArry);
		}
		while (!*YscArry.GetData());
	
	TargetRocket->AttachToActor(*YscArry.GetData(), FAttachmentTransformRules::KeepRelativeTransform);
}

void ASceneManager::InitDZJ()
{
	DZJOrignLocation = DZJMesh->GetActorLocation();
}

void ASceneManager::SingleMeshClick(AA_SinglePart* SinglePart)
{
	CurSingleMesh = SinglePart;
}

void ASceneManager::CheckClickMesh()
{
	if(CurSingleMesh->GetSingleMeshType() != UIDiagram->RocketParts[ClickedNum].RocketPartsType)
	{
		PlaySoundWrong();
		
		UWHoisting* Widget = Cast<UWHoisting>(UIManager->WidgetMap[UIManager->CurWidgetType]);
		Widget->PlaySelectWrong();
		
		FTimerHandle Delaypop;
		GetWorld()->GetTimerManager().SetTimer(Delaypop, this, &ASceneManager::DelaySelect, 3.5f);
		return;
	}

	PlaySoundRight();
	ClickedNum++;
	UGameplayStatics::PlaySound2D(this, ResourceManager->HoistUp);
	
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
	VDPawn->BoxExtentUpdate();
	VDPawn->bMove = true;
}

void ASceneManager::DelaySelect()
{
	SetSelectable(true);
}


void ASceneManager::PlaySoundWrong()
{
	UGameplayStatics::PlaySound2D(this, ResourceManager->AnswerWrong);
}

void ASceneManager::PlaySoundRight()
{
	UGameplayStatics::PlaySound2D(this, ResourceManager->AnswerRight);
}

void ASceneManager::CollisionClose()
{
	TargetRocket->SetActorEnableCollision(false);
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


