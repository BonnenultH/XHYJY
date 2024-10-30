// Fill out your copyright notice in the Description page of Project Settings.


#include "UMG/Child/WPersonTitle.h"

void UWPersonTitle::InitWidget()
{
	Super::InitWidget();
	ImageArry.Add(Progress1);
	ImageArry.Add(Progress2);
	ImageArry.Add(Progress3);
	ImageArry.Add(Progress4);
	ImageArry.Add(Progress5);
	ImageArry.Add(Progress6);
	ImageArry.Add(Progress7);
	
	IDName->SetText(FText::FromString(VDPawn->UserInfoData.IDName));
	Accomplishment->SetText(FText::FromString(VDPawn->UserInfoData.Accomplishment));
	UIManager->OnUpdateProgress.AddUObject(this, &UWPersonTitle::UpdateProgress);
}

void UWPersonTitle::UpdateProgress()
{
	if(TimerHandle.IsValid())
	{
		GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
	}
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UWPersonTitle::DelayUpdateProgress, 0.02);
}

void UWPersonTitle::DelayUpdateProgress()
{
	if(UIManager->GetManagerProgress() < 0)
		return;

	for(int i = 1; i <= UIManager->GetManagerProgress(); ++i)
	{
		ImageArry[i - 1]->SetBrushFromTexture(ResourceManager->ProgressOkImage);
	}
}

