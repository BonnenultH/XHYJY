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
	EWT_Hoisting,
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

UENUM(BlueprintType)
enum class EOrbit : uint8
{
	EO_LEO,
	EO_MEO,
	EO_SSO,
	EO_GEO,
	EO_GTO,
	EO_IGSO,
	EO_TLI,
	EO_TMI,
};

UENUM(BlueprintType)
enum class EHFCategory : uint8
{
	EHFC_None,
	EHFC_Satellite,
	EHFC_SpaceShip,
	EHFC_DeepSpaceProbes,
	EHFC_SpaceStation,
};

UENUM(BlueprintType)
enum class EHSCategory : uint8
{
	EHSC_None,
	EHSC_Navigation,
	EHSC_Communication,
	EHSC_RemoteSensing,
	EHSC_ScientificExploration,
};

UENUM(BlueprintType)
enum class ERocketType : uint8
{
	ERT_None,
	ERT_CZ_1,
	ERT_CZ_2,
	ERT_CZ_2D,
	ERT_CZ_2F,
	ERT_CZ_3,
	ERT_CZ_3A,
	ERT_CZ_3B,
	ERT_CZ_3BG2,
	ERT_CZ_3BG3,
	ERT_CZ_3C,
	ERT_CZ_4A,
	ERT_CZ_4B,
	ERT_CZ_4C,
	ERT_CZ_5,
	ERT_CZ_5B,
	ERT_CZ_6,
	ERT_CZ_7,
};

UENUM(BlueprintType)
enum class ERocketPartsType : uint8
{
	ERP_None,
	ERP_EscapeTower,
	ERP_Cowling,
	ERP_CoreThreeLevels,
	ERP_CoreTwoLevels,
	ERP_CoreOneLevel,
	ERP_Boosters,
};

USTRUCT(BlueprintType)
struct FRocketTable : public FTableRowBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ERocketType RocketType = ERocketType::ERT_None;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString RocketCNName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString RocketEnglishName;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CarryingCapacity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Price;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* RocketImage;
};

USTRUCT(BlueprintType)
struct FHTQOrbit
{
	GENERATED_BODY()

	FHTQOrbit() {};
	
	FHTQOrbit(EOrbit _HTQOrbitType, FString _HTQOrbitInfo, FString _HTQOrbitName)
	{
		HTQOrbitType = _HTQOrbitType;
		HTQOrbitInfo = _HTQOrbitInfo;
		HTQOrbitName = _HTQOrbitName;
	};
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EOrbit HTQOrbitType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString HTQOrbitInfo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString HTQOrbitName;
};

USTRUCT(BlueprintType)
struct FHTQFTaskData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EHFCategory HTQFirstType = EHFCategory::EHFC_None;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString FirstCategoryName;
};

USTRUCT(BlueprintType)
struct FHTQSTaskData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EHSCategory HTQSecondType = EHSCategory::EHSC_None;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString SecondCategoryName;
};

USTRUCT(BlueprintType)
struct FTaskRocket
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ERocketType RocketType = ERocketType::ERT_None;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bRight = false;
};

USTRUCT(BlueprintType)
struct FTaskTable : public FTableRowBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FHTQFTaskData FirstData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FHTQSTaskData SecondData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EOrbit HTQOrbitType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* Image;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString ForAppFunc;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString HTQDes;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FTaskRocket TaskRocket1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FTaskRocket TaskRocket2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FTaskRocket TaskRocket3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FTaskRocket TaskRocket4;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FTaskRocket TaskRocket5;
};

USTRUCT(BlueprintType)
struct FHTQData
{
	GENERATED_BODY()
public:
	FHTQData()	{};
	
	FHTQData(FTaskTable* Task)
	{
		TaskTable = Task;
	};
	
public:
	FTaskTable* TaskTable;
	
	// bIsLock = true : 代表锁定; bIsLock = false : 代表解锁;
	bool bIsLock = true;
};

USTRUCT(BlueprintType)
struct FHTQFirstData
{
	GENERATED_BODY()
public:
	void CreateSecondData(EHSCategory DataType)
	{
		TArray<FHTQData> Arry;
		SecondDataMap.Add(DataType, Arry);
	}
	
public:
	TMap<EHSCategory, TArray<FHTQData>> SecondDataMap;
	TArray<FHTQData> AllDataArry;
};

USTRUCT(BlueprintType)
struct FHTQCategoryData
{
	GENERATED_BODY()
public:
	void CreateFirstData(EHFCategory DataType)
	{
		FHTQFirstData Data;
		FirstDataMap.Add(DataType, Data);
	}

public:
	TMap<EHFCategory, FHTQFirstData> FirstDataMap;
};

USTRUCT(BlueprintType)
struct FPartsAttribute
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* UnselectedRocketPart;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* selectedRocketPart;

};

USTRUCT(BlueprintType)
struct FSingleRocketPart
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ERocketPartsType RocketPartsType = ERocketPartsType::ERP_None;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString  RocketPartName;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FPartsAttribute ImagePartDiagram;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FPartsAttribute TextPartDiagram;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bchosen = false;
	
};


USTRUCT(BlueprintType)
struct FDiagramUITable : public FTableRowBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ERocketType RocketType = ERocketType::ERT_None;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FSingleRocketPart>  RocketParts;
};

UCLASS()
class XHYJY_API UItemRocket : public UObject
{
	GENERATED_BODY()
public:
	void InitRocketData(FRocketTable* Data)
	{
		RocketType			= Data->RocketType;
		RocketName			= Data->RocketCNName;
		RocketEnglishName	= Data->RocketEnglishName;
		CarryingCapacity	= Data->CarryingCapacity;
		Price				= Data->Price;
		RocketImage			= Data->RocketImage;
	}
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ERocketType RocketType = ERocketType::ERT_None;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString RocketName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString RocketEnglishName;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CarryingCapacity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Price;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* RocketImage;
};

UCLASS()
class XHYJY_API UItemTask : public UObject
{
	GENERATED_BODY()
public:
	void InitTaskData(FHTQData Data)
	{
		Name			= Data.TaskTable->Name;
		FirstCategory	= Data.TaskTable->FirstData.FirstCategoryName;
		SecondCategory	= Data.TaskTable->SecondData.SecondCategoryName;
		Image			= Data.TaskTable->Image;
		ForAppFunc		= Data.TaskTable->ForAppFunc;
		HTQDes			= Data.TaskTable->HTQDes;
		HTQOrbitType	= Data.TaskTable->HTQOrbitType;

		RocketArry.Add(Data.TaskTable->TaskRocket1);
		RocketArry.Add(Data.TaskTable->TaskRocket2);
		RocketArry.Add(Data.TaskTable->TaskRocket3);
		RocketArry.Add(Data.TaskTable->TaskRocket4);
		RocketArry.Add(Data.TaskTable->TaskRocket5);
	}
	
public:	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString FirstCategory;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString SecondCategory;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EOrbit HTQOrbitType;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* Image;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString ForAppFunc;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString HTQDes;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FTaskRocket> RocketArry;
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
