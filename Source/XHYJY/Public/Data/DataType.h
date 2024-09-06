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
	EWT_Launch,
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

USTRUCT(BlueprintType)
struct FHTQCategory
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString FirstCategory;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString SecondCategory;
};


USTRUCT(BlueprintType)
struct FTaskTable : public FTableRowBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString FirstCategory;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString SecondCategory;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* Image;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString ForAppFunc;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString HTQDes;
};


UCLASS()
class XHYJY_API UItemTask : public UObject
{
	GENERATED_BODY()
public:
	void InitTaskData(FTaskTable* Data)
	{
		Name			= Data->Name;
		FirstCategory	= Data->FirstCategory;
		SecondCategory	= Data->SecondCategory;
		Image			= Data->Image;
		ForAppFunc		= Data->ForAppFunc;
		HTQDes			= Data->HTQDes;
	}
	
public:	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString FirstCategory;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString SecondCategory;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* Image;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString ForAppFunc;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString HTQDes;
};


USTRUCT(BlueprintType)
struct FSelectRocket : public FTableRowBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString RocketName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString RocketEnglishName;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString CarryingCapacity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Price;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* RocketImage;
};


UCLASS()
class XHYJY_API URocketSelection : public UObject
{
	GENERATED_BODY()
public:
	void InitRocketData(FSelectRocket* Data)
	{
		RocketName			= Data->RocketName;
		RocketEnglishName	= Data->RocketEnglishName;
		CarryingCapacity	= Data->CarryingCapacity;
		Price				= Data->Price;
		RocketImage			= Data->RocketImage;
	}
	
public:	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString RocketName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString RocketEnglishName;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString CarryingCapacity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Price;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* RocketImage;
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
