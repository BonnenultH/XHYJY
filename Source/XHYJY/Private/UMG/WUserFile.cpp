// Fill out your copyright notice in the Description page of Project Settings.


#include "UMG/WUserFile.h"

#include "Kismet/GameplayStatics.h"

void UWUserFile::InitWidget()
{
	Super::InitWidget();
	
	InitUserFileInfo();
	Button_History->OnClicked.AddDynamic(this, &UWUserFile::CreatHistoryTasks);
	Button_Rules->OnClicked.AddDynamic(this, &UWUserFile::CreatRules);
	Button_Task->OnClicked.AddDynamic(this, &UWUserFile::CreatTakeTasks);
}

void UWUserFile::InitUserFileInfo()
{
	IDName->SetText(FText::FromString(VDPawn->UserInfoData.IDName));
	if(VDPawn->UserInfoData.Gender == EGender::EG_Man)
	{
		Gender->SetText(FText::FromString(TEXT("男")));
	}
	else if(VDPawn->UserInfoData.Gender == EGender::EG_Woman)
	{
		Gender->SetText(FText::FromString(TEXT("女")));
	}
	Accomplishment->SetText(FText::FromString(VDPawn->UserInfoData.Accomplishment));
	Grades->SetText(FText::FromString(VDPawn->UserInfoData.Grades));
	HTQNumbers->SetText(FText::FromString(VDPawn->UserInfoData.HTQNumbers));
}

void UWUserFile::CreatHistoryTasks()
{
	UIManager->CreateVDWidget(EWidgetType::EWT_HistoryTasks, true);
	PlaySoundButton();
}

void UWUserFile::CreatRules()
{
	UIManager->CreateVDWidget(EWidgetType::EWT_Rules, true);
	PlaySoundButton();
}

void UWUserFile::CreatTakeTasks()
{
	UIManager->CreateVDWidget(EWidgetType::EWT_TakeTasks);
	PlaySoundButton();
}
