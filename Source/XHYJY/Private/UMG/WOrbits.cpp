// Fill out your copyright notice in the Description page of Project Settings.


#include "UMG/WOrbits.h"

void UWOrbits::InitWidget()
{
	Super::InitWidget();

	WBP_PersonTitle->InitWidget();
	WBP_Timing->InitWidget();
	Left_Orbit->SetVisibility(ESlateVisibility::Collapsed);

	LEO->OnClicked.AddDynamic(this,&UWOrbits::LEOClicked);
	MEO->OnClicked.AddDynamic(this,&UWOrbits::MEOClicked);
	SSO->OnClicked.AddDynamic(this,&UWOrbits::SSOClicked);
	GEO->OnClicked.AddDynamic(this,&UWOrbits::GEOClicked);
	GTO->OnClicked.AddDynamic(this,&UWOrbits::GTOClicked);
	IGSO->OnClicked.AddDynamic(this,&UWOrbits::IGSOClicked);
	TLI->OnClicked.AddDynamic(this,&UWOrbits::TLIClicked);
	TMI->OnClicked.AddDynamic(this,&UWOrbits::TMIClicked);
	
	Button_Ok->OnClicked.AddDynamic(this,&UWOrbits::CreateRocketSelect);
	UIManager->OnUpdateProgress.Broadcast();
}

void UWOrbits::LEOClicked()
{
	Left_Orbit->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	OrbitName->SetText(FText::FromString(TEXT("LEO轨道")));
	OrbitInfo->SetText(FText::FromString(ResourceManager->OrbitsInfoMap[EOrbit::ELEO]));
	OrbitType=EOrbit::ELEO;
}

void UWOrbits::MEOClicked()
{
	Left_Orbit->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	OrbitName->SetText(FText::FromString(TEXT("MEO轨道")));
	OrbitInfo->SetText(FText::FromString(ResourceManager->OrbitsInfoMap[EOrbit::EMEO]));
	OrbitType=EOrbit::EMEO;
}

void UWOrbits::SSOClicked()
{
	Left_Orbit->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	OrbitName->SetText(FText::FromString(TEXT("SSO轨道")));
	OrbitInfo->SetText(FText::FromString(ResourceManager->OrbitsInfoMap[EOrbit::ESSO]));
	OrbitType=EOrbit::ESSO;
}

void UWOrbits::GEOClicked()
{
	Left_Orbit->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	OrbitName->SetText(FText::FromString(TEXT("GEO轨道")));
	OrbitInfo->SetText(FText::FromString(ResourceManager->OrbitsInfoMap[EOrbit::EGEO]));
	OrbitType=EOrbit::EGEO;
}

void UWOrbits::GTOClicked()
{
	Left_Orbit->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	OrbitName->SetText(FText::FromString(TEXT("GTO轨道")));
	OrbitInfo->SetText(FText::FromString(ResourceManager->OrbitsInfoMap[EOrbit::EGTO]));
	OrbitType=EOrbit::EGTO;
}

void UWOrbits::IGSOClicked()
{
	Left_Orbit->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	OrbitName->SetText(FText::FromString(TEXT("IGSO轨道")));
	OrbitInfo->SetText(FText::FromString(ResourceManager->OrbitsInfoMap[EOrbit::EIGSO]));
	OrbitType=EOrbit::EIGSO;
}

void UWOrbits::TLIClicked()
{
	Left_Orbit->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	OrbitName->SetText(FText::FromString(TEXT("TLI轨道")));
	OrbitInfo->SetText(FText::FromString(ResourceManager->OrbitsInfoMap[EOrbit::ETLI]));
	OrbitType=EOrbit::ETLI;
}

void UWOrbits::TMIClicked()
{
	Left_Orbit->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	OrbitName->SetText(FText::FromString(TEXT("TMI轨道")));
	OrbitInfo->SetText(FText::FromString(ResourceManager->OrbitsInfoMap[EOrbit::ETMI]));
	OrbitType=EOrbit::ETMI;
}

void UWOrbits::CreateRocketSelect()
{
	UIManager->CreateVDWidget(EWidgetType::EWT_RocketSelect);
}

