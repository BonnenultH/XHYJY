// Fill out your copyright notice in the Description page of Project Settings.


#include "UMG/WUserFile.h"
#include "Materials/MaterialParameterCollectionInstance.h"

void UWUserFile::InitWidget()
{
	Super::InitWidget();
	
	InitUserFileInfo(TEXT("不可思议的佳佳"), TEXT("女"), TEXT("型号研究院高级研究员"), TEXT("720"), TEXT("30"));
	InitUserFileGender(EGender::EG_Woman);
	
	Button_History->OnClicked.AddDynamic(this, &UWUserFile::CreatHistoryTasks);
	Button_Rules->OnClicked.AddDynamic(this, &UWUserFile::CreatRules);
	Button_Task->OnClicked.AddDynamic(this, &UWUserFile::CreatTakeTasks);
}

void UWUserFile::InitUserFileInfo(FString _IDName, FString _Gender, FString _Accomplishment, FString _Grades, FString _HTQNumbers)
{
	IDName->SetText(FText::FromString(_IDName));
	Gender->SetText(FText::FromString(_Gender));
	Accomplishment->SetText(FText::FromString(_Accomplishment));
	Grades->SetText(FText::FromString(_Grades));
	HTQNumbers->SetText(FText::FromString(_HTQNumbers));
}

void UWUserFile::InitUserFileGender(EGender _Gender)
{
	UserFileGender = _Gender;
	if(UserFileGender == EGender::EG_None)
		return;

	if(UserFileGender == EGender::EG_Man)
	{
		ResourceManager->GenderMaterialInstance->SetScalarParameterValue("ManORWoman", 2);
	}
	else if(UserFileGender == EGender::EG_Woman)
	{
		ResourceManager->GenderMaterialInstance->SetScalarParameterValue("ManORWoman", 0);
	}
}

void UWUserFile::CreatHistoryTasks()
{
	UIManager->CreateVDWidget(EWidgetType::EWT_HistoryTasks, true);
}

void UWUserFile::CreatRules()
{
	UIManager->CreateVDWidget(EWidgetType::EWT_Rules, true);
}

void UWUserFile::CreatTakeTasks()
{
	UIManager->CreateVDWidget(EWidgetType::EWT_TakeTasks);
}
