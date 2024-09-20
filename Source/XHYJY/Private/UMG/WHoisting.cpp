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

	InitRocketPartInfos();
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
		RocketPartName->SetText(FText::FromString(UIDiagram->RocketParts[0].RocketPartName));
		TextBlock_RocketPartInfo->SetText(FText::FromString(RocketPartInfosMap[UIDiagram->RocketParts[0].RocketPartsType]));
	}
	
	
}

void UWHoisting::InitRocketPartInfos()
{
	RocketPartInfosMap.Add(ERocketPartsType::ERP_Cowling,TEXT("整流罩也被称为有效载荷整流罩，位于火箭头部，是火箭送入太空的“货物”——有效载荷的保护罩，其主要功能是为有效载荷提供一个相对封闭的适宜的环境，保护他们不受外界因素的影响，安全穿越大气层。而火箭冲出大气层后，整流罩就必须及时分离，以免影响到运载能力"));
	RocketPartInfosMap.Add(ERocketPartsType::ERP_EscapeTower,TEXT("逃逸塔位于火箭的顶端，是载人火箭独具的逃逸系统。当运载火箭在飞行中出现异常情况危急航天员生命时，逃逸火箭立即点火，带着整流罩和整流罩内的载人飞船一起迅速脱离运载火箭，飞向安全区。如果火箭飞行顺利，会在飞行120s时抛掉逃逸塔"));
	RocketPartInfosMap.Add(ERocketPartsType::ERP_CoreThreeLevels,TEXT("多级火箭的第三级，在火箭二子级分离前后三级发动机点火，使火箭速度进一步增加，推进剂用完后关机并自动脱离。"));
	RocketPartInfosMap.Add(ERocketPartsType::ERP_CoreTwoLevels,TEXT("多级火箭的第二级，在火箭一子级分离前后二级发动机点火，使火箭进一步加速，推进剂用完后关机并自动脱离。"));
	RocketPartInfosMap.Add(ERocketPartsType::ERP_CoreOneLevel,TEXT("多级火箭的第一级，在火箭发射时最先点火，使火箭达到一定速度后推进剂耗尽自动脱落。"));
	RocketPartInfosMap.Add(ERocketPartsType::ERP_Boosters,TEXT("火箭助推器是一种用于火箭发射时使其迅速飞离发射器并加速达到预定飞行速度的小型火箭。助推器捆绑在火箭芯级第一级，能够增加火箭的运载能力，在燃料耗尽后自动脱落。"));
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


