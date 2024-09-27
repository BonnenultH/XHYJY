// Fill out your copyright notice in the Description page of Project Settings.


#include "UMG/WHoisting.h"
#include "Components/VerticalBoxSlot.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/LevelStreaming.h"
#include "GameFramework/PlayerController.h"
#include "Scene/A_DispatchParts.h"

void UWHoisting::InitWidget()
{
	Super::InitWidget();
	
	WBP_PersonTitle->InitWidget();
	WBP_Timing->InitWidget();
	WBP_States->InitWidget();

	UIManager->OnUpdateProgress.Broadcast();

	FirePlaceMap.Add(EFirePlace::EFP_JQ,"XHYJY_Out_JQ");
	FirePlaceMap.Add(EFirePlace::EFP_TY,"XHYJY_Out_TY");
	FirePlaceMap.Add(EFirePlace::EFP_WC,"XHYJY_Out_WC");
	FirePlaceMap.Add(EFirePlace::EFP_XC,"XHYJY_Out_XC");
	
	FLatentActionInfo LevelInfo;
	LevelInfo.CallbackTarget = this;
	LevelInfo.Linkage = 0;
	LevelInfo.ExecutionFunction = FName("OnLevelLoaded");
	LevelInfo.UUID = FMath::Rand();
	
	UGameplayStatics::LoadStreamLevel(GetWorld(), "XHYJY_In", false, true, FLatentActionInfo());
	UGameplayStatics::LoadStreamLevel(GetWorld(), FirePlaceMap[UIManager->SelectTaskItem->FirePlace], false, true,LevelInfo);

	Button_OperateInstructions->OnClicked.AddDynamic(this, &UWHoisting::PlayOperateInstructions);
	Button_ok->OnClicked.AddDynamic(this, &UWHoisting::PlayReverseOperateIns);
	Button_close->OnClicked.AddDynamic(this, &UWHoisting::PlayErrorPart);
	Button_StartHoist->OnClicked.AddDynamic(this, &UWHoisting::PlayStartHoist);
	Button_StartSelectPart->OnClicked.AddDynamic(this, &UWHoisting::PlaySelectPartReverseAnim);
	Button_CurOk->OnClicked.AddDynamic(this, &UWHoisting::DispearCurSelect);
	
	SceneManager->InitHoistRocketParts();
	
	InitRocketPartInfos();
	InitDiagram();
	
	InitDelegateSingle();
}


void UWHoisting::OnLevelLoaded()
{
	ULevelStreaming* LocalLevelOut = FStreamLevelAction::FindAndCacheLevelStreamingObject(FirePlaceMap[UIManager->SelectTaskItem->FirePlace], GetWorld());
	ULevelStreaming* LocalLevelIn = FStreamLevelAction::FindAndCacheLevelStreamingObject("XHYJY_In", GetWorld());
	if(LocalLevelOut && LocalLevelIn)
	{
		LocalLevelOut->SetShouldBeVisible(true);
		LocalLevelIn->SetShouldBeVisible(true);
		
		
		if(ResourceManager->MainLevelSequencePlayer)
        	{
        		ResourceManager->MainLevelSequencePlayer->Play();
				ResourceManager->MainLevelSequencePlayer->OnFinished.AddDynamic(this, &UWHoisting::GoHoisting);
				//GoHoisting();
        	}
	}
}

void UWHoisting::InitDiagram()
{
	UIDiagram = UIManager->GetDiagramMap(UIManager->SelectTaskItem->GetCheapestRocket());
	for(int i = UIDiagram->RocketParts.Num()-1; i >= 0; --i)
	{
		UImage* PartImage = NewObject<UImage>(this);
		UImage* PartText = NewObject<UImage>(this);
		VerticalBox_PartImage->AddChildToVerticalBox(PartImage);
		VerticalBox_PartText->AddChildToVerticalBox(PartText);
		ImageSlot = Cast<UVerticalBoxSlot>(PartImage->Slot);
		if(ImageSlot)
		{
			ImageSlot->Size.SizeRule = ESlateSizeRule::Automatic;
			ImageSlot->HorizontalAlignment = EHorizontalAlignment::HAlign_Center;
			ImageSlot->VerticalAlignment = VAlign_Top;
		}
		PartText->SetBrushFromTexture(UIDiagram->RocketParts[i].TextPartDiagram.UnselectedRocketPart, true);
		PartImage->SetBrushFromTexture(UIDiagram->RocketParts[i].ImagePartDiagram.UnselectedRocketPart,true);
		if(UIDiagram->RocketParts[i].RocketPartsType == ERocketPartsType::ERP_Boosters)
		{
			VerticalBox_PartImage->RemoveChild(PartImage);
		}
		
		if(i <= UIDiagram->RocketParts.Num()-2 && UIDiagram->RocketParts[i + 1].RocketPartsType == ERocketPartsType::ERP_Boosters)
		{
			UImage* PartImageBooster = NewObject<UImage>(this);
			VerticalBox_PartImage->AddChildToVerticalBox(PartImageBooster);
			PartImageBooster->SetBrushFromTexture(UIDiagram->RocketParts[i + 1].ImagePartDiagram.UnselectedRocketPart, true);
			ImageSlot = Cast<UVerticalBoxSlot>(PartImageBooster->Slot);
			ImageSlot->SetPadding(FMargin(0, - UIDiagram->RocketParts[i + 1].ImagePartDiagram.UnselectedRocketPart->GetSizeY(),0,0));
		}  
	}
		UImage* PartTextDown = NewObject<UImage>(this);
		VerticalBox_PartText->AddChildToVerticalBox(PartTextDown);
		PartTextDown->SetBrushFromTexture(ResourceManager->HoistDown, true);

	//取ImageTarray的逆序排列然后存到数组里每次去替换
	//判断是否一致要和当前进行绑定

	HoistingProgress();
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

void UWHoisting::HoistingProgress()
{
		int i = 0;
		CurSingleRocketPart = UIDiagram->RocketParts[i];
		TextBlock_Part->SetText(FText::FromString(CurSingleRocketPart.RocketPartName));
		RocketPartName->SetText(FText::FromString(CurSingleRocketPart.RocketPartName));
		Loadoutprogress->SetText(FText::FromString(FString::FromInt(i / UIDiagram->RocketParts.Num()).Append(L"%")));
		ProgressBar->SetPercent(i / UIDiagram->RocketParts.Num());
		TextBlock_RocketPartInfo->SetText(FText::FromString(RocketPartInfosMap[CurSingleRocketPart.RocketPartsType]));
		
}



void UWHoisting::PlayStartHoist()
{
	PlayAnimation(StartHoist);
	FTimerHandle Delaypop;
	GetWorld()->GetTimerManager().SetTimer(Delaypop, this, &UWHoisting::PlaySelectPartAnim, 0.75f);
	
}


void UWHoisting::PlayOperateInstructions()
{
	PlayAnimation(Instructions);
}

void UWHoisting::PlayReverseOperateIns()
{
	PlayAnimationReverse(Instructions);
}

void UWHoisting::PlaySelectPartAnim()
{
	PlayAnimation(StartSelectPartAnim);
}

void UWHoisting::PlaySelectPartReverseAnim()
{
	PlayAnimationReverse(StartSelectPartAnim);
}


void UWHoisting::PlayErrorPart()
{
	PlayAnimationReverse(ErrorPartSelection);
}

void UWHoisting::DispearCurSelect()
{
	PlayAnimationReverse(CurSelectPartAnim);
}

void UWHoisting::GoHoisting()
{
	Hoisting->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	SceneManager->SwitchViewByHoist();
}

void UWHoisting::InitDelegateSingle()
{
	for(int i = 0 ; i < SceneManager->DispatchParts->SinglePartsArray.Num(); i++)
	{
	SceneManager->DispatchParts->SinglePartsArray[i]->MouseRocketClickReturn.AddUObject(this, &UWHoisting::ClickedRocketAttribute);
	}

}


void UWHoisting::ClickedRocketAttribute(AA_SinglePart* SinglePart)
{
	TextBlock_CurPart->SetText(FText::FromString(SinglePart->RocketPartName));
	PlayAnimation(CurSelectPartAnim);
}


