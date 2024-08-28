// Fill out your copyright notice in the Description page of Project Settings.


#include "UMG/Child/WTiming.h"

void UWTiming::InitWidget()
{
	Super::InitWidget();

	FString _Minute = LexToString(UIManager->ManagerMinute).Left(1);
	_Minute.InsertAt(0, TEXT("0"));
	FString _Second = LexToString(UIManager->ManagerSecond).Left(2);
	
	Minute->SetText(FText::FromString(_Minute));
	Second->SetText(FText::FromString(_Second));
}

