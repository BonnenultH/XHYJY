// Fill out your copyright notice in the Description page of Project Settings.


#include "Manager/ResourceManager.h"
#include "MediaPlayer.h"
#include "MediaSource.h"

// Sets default values
AResourceManager::AResourceManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	InitRSWidgetMap();
	InitMediaResource();
}

// Called when the game starts or when spawned
void AResourceManager::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AResourceManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AResourceManager::InitManager()
{
	Super::InitManager();
}

TSubclassOf<UUserWidget> AResourceManager::LoadWidgetFile(FString Path)
{
	return ConstructorHelpers::FClassFinder<UUserWidget>(*Path).Class;
}

void AResourceManager::InitRSWidgetMap()
{
	RSWidgetMap.Add(EWidgetType::EWT_HomePage,LoadWidgetFile(TEXT("'/Game/VD/UMG/WBP_HomePage.WBP_HomePage_C'")));
	RSWidgetMap.Add(EWidgetType::EWT_UserFile,LoadWidgetFile(TEXT("'/Game/VD/UMG/WBP_UserFile.WBP_UserFile_C'")));
}

void AResourceManager::InitMediaResource()
{
	ConstructorHelpers::FObjectFinder<UMediaPlayer> MediaPlayer(TEXT("'/Game/VD/UMG/Homepage/MediaVideo/MP_Earth.MP_Earth'"));
	MP= MediaPlayer.Object;
	ConstructorHelpers::FObjectFinder<UMediaSource> MediaSource(TEXT("'/Game/VD/UMG/Homepage/MediaVideo/Earth.Earth'"));
	MS= MediaSource.Object;
}



