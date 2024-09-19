// Fill out your copyright notice in the Description page of Project Settings.


#include "UMG/WLaunch.h"


void UWLaunch::InitWidget()
{
	Super::InitWidget();
	
	WBP_PersonTitle->InitWidget();
	WBP_Timing->InitWidget();
	UIManager->OnUpdateProgress.Broadcast();
	WBP_States->InitWidget();

	Button_JQ->OnClicked.AddDynamic(this, &UWLaunch::ClickedJQ);
	Button_TY->OnClicked.AddDynamic(this, &UWLaunch::ClickedTY);
	Button_XC->OnClicked.AddDynamic(this, &UWLaunch::ClickedXC);
	Button_WC->OnClicked.AddDynamic(this, &UWLaunch::ClickedWC);

	Button_Ok->OnClicked.AddDynamic(this, &UWLaunch::CreateAnim);
	Button_Again->OnClicked.AddDynamic(this, &UWLaunch::WrongAgain);
	Button_GoHoist->OnClicked.AddDynamic(this, &UWLaunch::CreateHoisting);
}

void UWLaunch::ClickedJQ()
{
	ImageBG->SetBrushFromTexture(ResourceManager->JQ);
	UIManager->SelectFirePlace = EFirePlace::EFP_JQ;
}

void UWLaunch::ClickedTY()
{
	ImageBG->SetBrushFromTexture(ResourceManager->TY);
	UIManager->SelectFirePlace = EFirePlace::EFP_TY;
}

void UWLaunch::ClickedXC()
{
	ImageBG->SetBrushFromTexture(ResourceManager->XC);
	UIManager->SelectFirePlace = EFirePlace::EFP_XC;
}

void UWLaunch::ClickedWC()
{
	ImageBG->SetBrushFromTexture(ResourceManager->WC);
	UIManager->SelectFirePlace = EFirePlace::EFP_WC;
}

void UWLaunch::CreateAnim()
{
	PlayAnimation(RightAnswer);
}

void UWLaunch::WrongAgain()
{
	PlayAnimationReverse(WrongAnswer);
}


void UWLaunch::CreateHoisting()
{
	UIManager->CreateVDWidget(EWidgetType::EWT_Hoisting);
}

