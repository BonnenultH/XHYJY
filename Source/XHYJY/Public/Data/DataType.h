// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DataType.generated.h"


enum class EWidgetType:uint8
{
	EWT_None,
	EWT_HomePage,
	EWT_UserFile,
	EWT_HistoryTasks,
	EWT_TakeTasks,
	EWT_Rules,
	EWT_Orbits,
	EWT_RocketSelect,
};

enum class EGender:uint8
{
	EG_None,
	EG_Man,
	EG_Woman,
};

struct S_UserInfo
{
	const WIDECHAR* IDName;
	const WIDECHAR* Accomplishment;
	const WIDECHAR* Grades;
	const WIDECHAR* HTQNumbers;
	EGender Gender = EGender::EG_None;
};

enum class EOrbit : uint8
{
	ELEO,
	EMEO,
	ESSO,
	EGEO,
	EGTO,
	EIGSO,
	ETLI,
	ETMI,
};


UCLASS()
class XHYJY_API ADataType : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADataType();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
