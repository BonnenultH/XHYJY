// Fill out your copyright notice in the Description page of Project Settings.


#include "UMG/WLaunch.h"


void UWLaunch::InitWidget()
{
	Super::InitWidget();

	ErrorNums = 2;
	
	WBP_PersonTitle->InitWidget();
	WBP_Timing->InitWidget();
	UIManager->OnUpdateProgress.Broadcast();
	WBP_States->InitWidget();

	Button_JQ->OnClicked.AddDynamic(this, &UWLaunch::ClickedJQ);
	Button_TY->OnClicked.AddDynamic(this, &UWLaunch::ClickedTY);
	Button_XC->OnClicked.AddDynamic(this, &UWLaunch::ClickedXC);
	Button_WC->OnClicked.AddDynamic(this, &UWLaunch::ClickedWC);

	Button_Ok->OnClicked.AddDynamic(this, &UWLaunch::CheckFirePlace);
	Button_Again->OnClicked.AddDynamic(this, &UWLaunch::WrongAgain);
	Button_GoHoist->OnClicked.AddDynamic(this, &UWLaunch::CreateHoisting);
	Button_WrongGoHoist->OnClicked.AddDynamic(this, &UWLaunch::CreateHoisting);

	Button_JQ->SetIsEnabled(false);
	CurButton = Button_JQ;
	CurFirePlace = EFirePlace::EFP_JQ;
}

void UWLaunch::ClickedJQ()
{
	if(CurButton)
	{
		CurButton->SetIsEnabled(true);
	}
	ImageBG->SetBrushFromTexture(ResourceManager->JQ);
	CurFirePlace = EFirePlace::EFP_JQ;
	Button_JQ->SetIsEnabled(false);
	CurButton = Button_JQ;
}

void UWLaunch::ClickedTY()
{
	if(CurButton)
	{
		CurButton->SetIsEnabled(true);
	}
	ImageBG->SetBrushFromTexture(ResourceManager->TY);
	CurFirePlace = EFirePlace::EFP_TY;
	Button_TY->SetIsEnabled(false);
	CurButton = Button_TY;
}

void UWLaunch::ClickedXC()
{
	if(CurButton)
	{
		CurButton->SetIsEnabled(true);
	}
	ImageBG->SetBrushFromTexture(ResourceManager->XC);
	
	CurFirePlace = EFirePlace::EFP_XC;
	Button_XC->SetIsEnabled(false);
	CurButton = Button_XC;
}

void UWLaunch::ClickedWC()
{
	if(CurButton)
	{
		CurButton->SetIsEnabled(true);
	}
	ImageBG->SetBrushFromTexture(ResourceManager->WC);
	
	CurFirePlace = EFirePlace::EFP_WC;
	Button_WC->SetIsEnabled(false);
	CurButton = Button_WC;
}

void UWLaunch::CheckFirePlace()
{
	if(CurFirePlace != UIManager->SelectTaskItem->FirePlace)
	{
		if(ErrorNums != 0)
		{
			UIManager->MinusGrade(5);
			CountErrorNums();
			PlayAnimation(WrongAnswer);
			return;
		}
		PlayAnimation(WrongAnswer_GoHoist);
		return;
	}
	PlayAnimation(RightAnswer);
}

void UWLaunch::WrongAgain()
{
	PlayAnimationReverse(WrongAnswer);
}

void UWLaunch::CreateHoisting()
{
	UIManager->bShowFirePlace = true;
	UIManager->CreateVDWidget(EWidgetType::EWT_Hoisting);
	SceneManager->BindHoistUIDelegate();
}

