// Fill out your copyright notice in the Description page of Project Settings.


#include "UMG/WHoisting.h"
#include "Camera/CameraActor.h"
#include "Components/VerticalBoxSlot.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/LevelStreaming.h"
#include "GameFramework/PlayerController.h"

void UWHoisting::InitWidget()
{
	Super::InitWidget();

	
	WBP_PersonTitle->InitWidget();
	WBP_Timing->InitWidget();
	WBP_States->InitWidget();

	UIManager->OnUpdateProgress.Broadcast();
	
	FLatentActionInfo info;
	info.UUID = FMath::Rand();
	UGameplayStatics::LoadStreamLevel(GetWorld(), "XHYJY_Out_JQ", false, true,info);
	UGameplayStatics::LoadStreamLevel(GetWorld(), "XHYJY_In", false, true,FLatentActionInfo());

	
	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UWHoisting::LoadLevelAssets,1.0f, false, 0.001f);

	Button_OperateInstructions->OnClicked.AddDynamic(this, &UWHoisting::PlayOperateInstructions);
	Button_ok->OnClicked.AddDynamic(this, &UWHoisting::PlayReverseOperateIns);
	Button_close->OnClicked.AddDynamic(this, &UWHoisting::PlayErrorPart);
	Button_StartHoist->OnClicked.AddDynamic(this, &UWHoisting::PlayStartHoist);
	
	InitDiagram();
}


void UWHoisting::LoadLevelAssets()
{
	ULevelStreaming* LocalLevelJQ =FStreamLevelAction::FindAndCacheLevelStreamingObject("XHYJY_Out_JQ", GetWorld());
	ULevelStreaming* LocalLevelIn =FStreamLevelAction::FindAndCacheLevelStreamingObject("XHYJY_In", GetWorld());
	if(LocalLevelJQ && LocalLevelIn)
	{
		LocalLevelJQ->SetShouldBeVisible(true);
		LocalLevelIn->SetShouldBeVisible(true);
		if(ResourceManager->MainLevelSequencePlayer)
        	{
        		ResourceManager->MainLevelSequencePlayer->Play();
			
				FTimerHandle TimeAnimDelay;
				GetWorld()->GetTimerManager().SetTimer(TimeAnimDelay, this, &UWHoisting::GoHoisting, 1.0f, false, ResourceManager->MainLevelSequencePlayer->GetDuration().AsSeconds());
        	}
	}
}



void UWHoisting::InitDiagram()
{
	FDiagramUITable* UIDiagram = UIManager->GetDiagramMap(ERocketType::ERT_CZ_3B);
	for(int i = 0; i < UIDiagram->RocketParts.Num(); ++i)
	{
		auto PartImage =NewObject<UImage>(this);
		auto PartText =NewObject<UImage>(this);
		VerticalBox_PartImage->AddChildToVerticalBox(PartImage);
		VerticalBox_PartText->AddChildToVerticalBox(PartText);
		ImageSlot = Cast<UVerticalBoxSlot>(PartImage->Slot);
		if(ImageSlot)
		{
			ImageSlot->Size.SizeRule = ESlateSizeRule::Automatic;
			ImageSlot->HorizontalAlignment = EHorizontalAlignment::HAlign_Center;
			ImageSlot->VerticalAlignment = VAlign_Top;
		}
		if(UIDiagram->RocketParts[i].RocketPartsType == ERocketPartsType::ERP_Boosters)
		{
			
			ImageSlot->SetPadding(FMargin(0,-UIDiagram->RocketParts[i].ImagePartDiagram.UnselectedRocketPart->GetSizeY(),0,0));
		}
		PartImage->SetBrushFromTexture(UIDiagram->RocketParts[i].ImagePartDiagram.UnselectedRocketPart,true);
		PartText->SetBrushFromTexture(UIDiagram->RocketParts[i].TextPartDiagram.UnselectedRocketPart, true);
	}
	
}

void UWHoisting::PlayStartHoist()
{
	PlayAnimation(StartHoist);
}
void UWHoisting::PlayOperateInstructions()
{
	PlayAnimation(Instructions);
}

void UWHoisting::PlayReverseOperateIns()
{
	PlayAnimationReverse(Instructions);
}

void UWHoisting::PlayErrorPart()
{
	PlayAnimationReverse(ErrorPartSelection);
}

void UWHoisting::GoHoisting()
{
	Hoisting->SetVisibility(ESlateVisibility::SelfHitTestInvisible);

	UGameplayStatics::GetAllActorsOfClassWithTag(this, ACameraActor::StaticClass(),"MainCamera",MyPlayerCameras);
	UGameplayStatics::GetPlayerController(this, 0)->SetViewTarget(MyPlayerCameras[0]);
	
}


