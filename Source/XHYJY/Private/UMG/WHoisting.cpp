// Fill out your copyright notice in the Description page of Project Settings.


#include "UMG/WHoisting.h"
#include "Kismet/GameplayStatics.h"



void UWHoisting::InitWidget()
{
	Super::InitWidget();
	
	WBP_PersonTitle->InitWidget();
	WBP_Timing->InitWidget();
	WBP_States->InitWidget();
	UIManager->OnUpdateProgress.Broadcast();
	FLatentActionInfo info1;
	FLatentActionInfo info2;
	info1.UUID = FMath::Rand();
	info2.UUID = FMath::Rand();
	UGameplayStatics::LoadStreamLevel(GetWorld(), "XHYJY_In", true, true,info1);
	UGameplayStatics::LoadStreamLevel(GetWorld(), "XHYJY_Out_JQ", true, true,info2);

	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UWHoisting::LoadLevelAssets,1.0f, false, 0.002f);

}
void UWHoisting::LoadLevelAssets()
{
	if(ResourceManager->LevelSequencePlayer)
{
	ResourceManager->LevelSequencePlayer->Play();
}
}