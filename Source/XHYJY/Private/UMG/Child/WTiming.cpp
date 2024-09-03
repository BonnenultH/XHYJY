// Fill out your copyright notice in the Description page of Project Settings.


#include "UMG/Child/WTiming.h"

void UWTiming::InitWidget()
{
	Super::InitWidget();

	UpdateTime();
}

void UWTiming::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	UpdateTime();
}

void UWTiming::UpdateTime()
{
	_Minute = TimeFormat(UIManager->ManagerMinute);
	_Second = TimeFormat(UIManager->ManagerSecond);
	
	Minute->SetText(FText::FromString(_Minute));
	Second->SetText(FText::FromString(_Second));
	
}

FString UWTiming::TimeFormat(float time)
{
	FString _Time;
	if(time<10)
	{
		_Time=FString::SanitizeFloat(time).Left(1);
		_Time.InsertAt(0,TEXT("0"));
	}
	else
	{
		_Time = FString::SanitizeFloat(time).Left(2);
	}
	return _Time;
}



