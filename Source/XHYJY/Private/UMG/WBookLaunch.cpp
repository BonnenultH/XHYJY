// Fill out your copyright notice in the Description page of Project Settings.


#include "UMG/WBookLaunch.h"

//#include "GM/VDGameInstance.h"
//#include "Kismet/GameplayStatics.h"
#include "TcpSocket/VDSocket.h"


void UWBookLaunch::InitWidget()
{
	Super::InitWidget();

	WBP_PersonTitle->InitWidget();
	UIManager->OnUpdateProgress.Broadcast();

	//线上
	//MyGameInstance = Cast<UVDGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	//线下和平里
	// TArray<AActor*> MySockets;
	// UGameplayStatics::GetAllActorsWithTag(GetWorld(),"MyBPSocket", MySockets);
	// MyTCPSocket = Cast<AVDSocket>(MySockets[0]);
	
	if(UIManager->GetGrade() == 100)
	{
		Image_Level->SetBrushFromTexture(ResourceManager->S);
	}
	else if(UIManager->GetGrade() > 90)
	{
		Image_Level->SetBrushFromTexture(ResourceManager->A);
	}
	else if(UIManager->GetGrade() > 80)
	{
		Image_Level->SetBrushFromTexture(ResourceManager->B);
	}
	else if(UIManager->GetGrade() > 60)
	{
		Image_Level->SetBrushFromTexture(ResourceManager->C);
	}
	else 
	{
		Image_Level->SetBrushFromTexture(ResourceManager->D);
	}

	
	//时间更改
	// //float totaltime = MyGameInstance->Time;
	// float totaltime = UIManager->ManagerMinute;
	// //本地运行
	// //float totaltime = 8;
	// TimeStr = TimeFormat(totaltime - UIManager->ManagerMinute);
	// TimeStr.Append(":");
	// TimeStr.Append(TimeFormat(59.0 - UIManager->ManagerSecond));

	
	const float UsedSecondsFloat =UIManager->TotalMinutes * 60.0f- (UIManager->ManagerMinute * 60.0f+ UIManager->ManagerSecond);

	const int32 UsedTimeSeconds =FMath::Max(0,FMath::RoundToInt(UsedSecondsFloat));

	const int32 UsedMinutes =UsedTimeSeconds / 60;
	const int32 UsedSeconds =UsedTimeSeconds % 60;

	const FString TimeStr = FString::Printf(TEXT("%02d:%02d"),UsedMinutes,UsedSeconds);
	
	TextBlock_Time->SetText(FText::FromString(TimeStr));
	TextBlock_HTQ->SetText(FText::FromString(UIManager->SelectTaskItem->Name));
	TextBlock_Rocket->SetText(FText::FromString(UIManager->GetRocketData(UIManager->SelectTaskItem->GetCheapestRocket())->RocketCNName));
	TextBlock_Fireplace->SetText(FText::FromString(UIManager->SelectTaskItem->FirePlaceName));
	
	GetWorld()->GetTimerManager().SetTimer(DelayReturn, this, &UWBookLaunch::GameRestart, 5.0f, false);
}

void UWBookLaunch::GameRestart()
{
	//新版本的型号研究院打开这个
	// MyTCPSocket->SendData();
	// MyTCPSocket->GameEnd();

	//线下和平里
	// MyGameInstance->SendLocalReportLog();
	// MyGameInstance->GameEnd();
	GetWorld()->GetFirstPlayerController()->ConsoleCommand(TEXT("RestartLevel"));
	
}


FString UWBookLaunch::TimeFormat(float Time)
{
	FString Formatstr;
	if(Time < 10)
	{
	Formatstr = FString::SanitizeFloat(Time).Left(1);
	Formatstr.InsertAt(0,TEXT("0"));
	}
	else
	{
	Formatstr = FString::SanitizeFloat(Time).Left(2);
	}
	return  Formatstr;
}
