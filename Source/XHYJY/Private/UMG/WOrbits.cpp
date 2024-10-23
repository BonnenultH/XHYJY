// Fill out your copyright notice in the Description page of Project Settings.


#include "UMG/WOrbits.h"

#include "Kismet/GameplayStatics.h"


void UWOrbits::InitWidget()
{
	Super::InitWidget();

	ErrorNums = 2;

	WBP_PersonTitle->InitWidget();
	WBP_Timing->InitWidget();
	Left_Orbit->SetVisibility(ESlateVisibility::Collapsed);
	WBP_States->InitWidget();
	

	LEO->OnClicked.AddDynamic(this,&UWOrbits::LEOClicked);
	MEO->OnClicked.AddDynamic(this,&UWOrbits::MEOClicked);
	SSO->OnClicked.AddDynamic(this,&UWOrbits::SSOClicked);
	GEO->OnClicked.AddDynamic(this,&UWOrbits::GEOClicked);
	GTO->OnClicked.AddDynamic(this,&UWOrbits::GTOClicked);
	IGSO->OnClicked.AddDynamic(this,&UWOrbits::IGSOClicked);
	TLI->OnClicked.AddDynamic(this,&UWOrbits::TLIClicked);
	TMI->OnClicked.AddDynamic(this,&UWOrbits::TMIClicked);

	HTQName->SetText(FText::FromString(UIManager->SelectTaskItem->Name));
	HTQDes->SetText(FText::FromString(UIManager->SelectTaskItem->HTQDes));
	
	Button_RightOk->OnClicked.AddDynamic(this, &UWOrbits::RightAnswer);
	Button_WrongAgain->OnClicked.AddDynamic(this, &UWOrbits::WrongAnswer);
	Button_Ok->OnClicked.AddDynamic(this,&UWOrbits::CreateRocketSelect);
	UIManager->OnUpdateProgress.Broadcast();
}


void UWOrbits::LEOClicked()
{
	OrbitInfoFunc(EOrbit::EO_LEO);
}

void UWOrbits::MEOClicked()
{
	OrbitInfoFunc(EOrbit::EO_MEO);
}

void UWOrbits::SSOClicked()
{
	OrbitInfoFunc(EOrbit::EO_SSO);
}

void UWOrbits::GEOClicked()
{
	OrbitInfoFunc(EOrbit::EO_GEO);
}

void UWOrbits::GTOClicked()
{
	OrbitInfoFunc(EOrbit::EO_GTO);
}

void UWOrbits::IGSOClicked()
{
	OrbitInfoFunc(EOrbit::EO_IGSO);
}

void UWOrbits::TLIClicked()
{
	OrbitInfoFunc(EOrbit::EO_TLI);
}

void UWOrbits::TMIClicked()
{
	OrbitInfoFunc(EOrbit::EO_TMI);
}

void UWOrbits::CreateRocketSelect()
{
	if(CurSelectedOrbit.HTQOrbitType == UIManager->SelectTaskItem->HTQOrbitType)
	{
		PlayAnimation(Orbit_RightPop);
	
	}
	else
	{
		if(ErrorNums != 0)
		{
			UIManager->MinusGrade(5);
			CountErrorNums();
			PlayAnimation(Orbit_WrongPop);
		}
		else
		{
			UIManager->bShowOrbit = true;
			UIManager->CreateVDWidget(EWidgetType::EWT_RocketSelect);
		}
	}
}

void UWOrbits::OrbitInfoFunc(EOrbit Orbit)
{
	UGameplayStatics::PlaySound2D(this, ResourceManager->Button);
	Left_Orbit->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	OrbitName->SetText(FText::FromString(UIManager->GetOrbit(Orbit).HTQOrbitName));
	OrbitInfo->SetText(FText::FromString(UIManager->GetOrbit(Orbit).HTQOrbitInfo));
	CurSelectedOrbit = UIManager->GetOrbit(Orbit);
}

void UWOrbits::RightAnswer()
{
	PlayAnimationReverse(Orbit_RightPop);
	UIManager->bShowOrbit = true;
	UIManager->CreateVDWidget(EWidgetType::EWT_RocketSelect);
}

void UWOrbits::WrongAnswer()
{
	PlayAnimationReverse(Orbit_WrongPop);
}