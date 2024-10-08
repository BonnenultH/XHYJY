// Fill out your copyright notice in the Description page of Project Settings.


#include "Manager/UIManager.h"
#include "UMG/BaseWidget.h"
#include "Manager/ResourceManager.h"
#include "Materials/MaterialParameterCollectionInstance.h"


// Sets default values
AUIManager::AUIManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AUIManager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AUIManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UpdateTime(DeltaTime);
}

void AUIManager::InitManager()
{
	Super::InitManager();
	
	OnUpdateProgress.AddUObject(this, &AUIManager::UpdateProgress);
	CreateVDWidget(EWidgetType::EWT_HomePage);
	
	InitUserFileGender();
	InitRocketTable();
	InitTaskTable();
	InitOrbitInfo();
	InitQuestionTable();
	InitRocketPartDiagram();
}

void AUIManager::UpdateProgress()
{
	ManagerProgress += 1;
}

void AUIManager::UpdateTime(float DeltaTime)
{
	if(!bTimeStart)
	{
		return;
	}
	
	//UE_LOG(LogTemp, Log, TEXT("当前的分时间：%f, 当前的秒时间：%f, InDeltaTime == %f"), ManagerMinute, ManagerSecond, DeltaTime)
	if(UIManager->ManagerSecond == 0)
	{
		ManagerMinute -= 1;
		ManagerSecond = 59;
	}
	if(Interval <= 1)
	{
		Interval += DeltaTime;
	}
	else
	{
		Interval = 0;
		ManagerSecond -= 1;
	}
}

void AUIManager::InitUserFileGender()
{
	if(VDPawn->UserInfoData.Gender == EGender::EG_None)
		return;

	if(VDPawn->UserInfoData.Gender == EGender::EG_Man)
	{
		ResourceManager->GenderMaterialInstance->SetScalarParameterValue("ManORWoman", 2);
	}
	else if(VDPawn->UserInfoData.Gender == EGender::EG_Woman)
	{
		ResourceManager->GenderMaterialInstance->SetScalarParameterValue("ManORWoman", 0);
	}
}

void AUIManager::InitTaskTable()
{
	TArray<FTaskTable*> AllTaskArry;
	ResourceManager->HTQTasks->GetAllRows<FTaskTable>("", AllTaskArry);
	
	for(auto Task : AllTaskArry)
	{
		if(Task->FirstData.HTQFirstType != EHFCategory::EHFC_None)
		{
			if(HTQCategoryData.FirstDataMap.Find(Task->FirstData.HTQFirstType) == nullptr)
			{
				HTQCategoryData.CreateFirstData(Task->FirstData.HTQFirstType);
			}
			
			FHTQData HTQData(Task);
			HTQCategoryData.FirstDataMap[Task->FirstData.HTQFirstType].AllDataArry.Add(HTQData);
			
			if(Task->SecondData.HTQSecondType != EHSCategory::EHSC_None)
			{
				if(HTQCategoryData.FirstDataMap[Task->FirstData.HTQFirstType].SecondDataMap.Find(Task->SecondData.HTQSecondType) == nullptr)
				{
					HTQCategoryData.FirstDataMap[Task->FirstData.HTQFirstType].CreateSecondData(Task->SecondData.HTQSecondType);
				}
				HTQCategoryData.FirstDataMap[Task->FirstData.HTQFirstType].SecondDataMap[Task->SecondData.HTQSecondType].Add(HTQData);
			}
		}
	}
}

void AUIManager::InitRocketTable()
{
	TArray<FRocketTable*> AllTaskArry;
	ResourceManager->RocketSelect->GetAllRows<FRocketTable>("", AllTaskArry);
	
	for(auto Task : AllTaskArry)
	{
		RocketMap.Add(Task->RocketType, Task);
	}
	
}


void AUIManager::InitOrbitInfo()
{
	FHTQOrbit OrbitGEO(EOrbit::EO_GEO, TEXT("即轨道倾角i=0°的地球同步轨道，距地面约36000公里的圆轨道。卫星与地面的相对位置保持不变，轨道周期与地球自转周期一致。典型航天器：通信、对地观测、导航、预警、气象等民用和军用卫星。"), TEXT("GEO轨道"));
	FHTQOrbit OrbitLEO(EOrbit::EO_LEO, TEXT("低地（球）轨道/近地（球）轨道（LEO：Low Earth Orbit）距地面约200-1200千米的近圆轨道。典型航天器：载人飞船、空间站、对地观测卫星以及一些新型通信卫星系统等。"), TEXT("LEO轨道"));
	FHTQOrbit OrbitIGSO(EOrbit::EO_IGSO, TEXT("倾斜地球同步轨道（IGSO：Inclined Geosynchronous Orbit ）即轨道倾角i≠0°的地球同步轨道，其星下点轨迹是一条“8”字形的封闭曲线，中国北斗卫星导航系统的其中三颗卫星位于55°倾角的倾斜地球同步轨道。"), TEXT("IGSO轨道"));
	FHTQOrbit OrbitMEO(EOrbit::EO_MEO, TEXT("中地球轨道（MEO：Middle Earth Orbit）轨道高度为1200-36000公里之间；GPS、GLONASS都属于此类轨道。美国GPS系统、俄罗斯GLONASS系统、欧盟伽利略系统和中国北斗系统均使用了高度20000-24000km的约55°倾角的中地球轨道。"), TEXT("MEO轨道"));
	FHTQOrbit OrbitGTO(EOrbit::EO_GTO, TEXT("地球同步转移轨道（GTO：Geostationary Transfer Orbit ）指距地面近地点约200公里，远地点约36000公里的椭圆轨道。地球同步转移轨道为霍曼转移轨道的运用之一，为椭圆形轨道，经加速后可达地球静止轨道(GEO)。近地点多在1000公里以下，远地点则为地球静止轨道高度36000公里。地球同步转移轨道一般只作为地球同步轨道的过渡轨道。"), TEXT("GTO轨道"));
	FHTQOrbit OrbitSSO(EOrbit::EO_SSO, TEXT("太阳同步轨道（SSO：Sun-synchronous Orbit ）又称近地太阳同步轨道，典型的太阳同步轨道高度大约是800km，周期在96-100分钟范围，倾角大致在98°附近，以满足任务需要。其轨道平面始终与太阳保持固定的取向，轨道平面自西向东保持360度/年的进动，轨道平面绕地球自转轴旋转的方向与地球公转方向相同。典型航天器：气象卫星、光学遥感卫星等。"), TEXT("SSO轨道"));
	FHTQOrbit OrbitTLI(EOrbit::EO_TLI, TEXT("地月转移轨道（Trans-Lunar injection，缩写为TLI）是指从月球探测器通过不断加速、脱离地球引力、飞向月球开始，到被月球引力捕获、近月制动为止的轨道段。典型的地月转移轨道，近地点在低地球轨道，远地点大约在400000公里的月球轨道。典型的航天器有月球探测器、地月中继卫星、月球着陆器、载人登月飞船等。"), TEXT("TLI轨道"));
	FHTQOrbit OrbitTMI(EOrbit::EO_TMI, TEXT("地火转移轨道（Trans-Mars injection，TMI），是一类特殊的日心轨道。从地球发射的人造卫星或探测器会通过这类轨道进入火星轨道，典型的地火转移轨道，近日点在1.3个天文单位，远日点在1.6个天文单位，由于地球和火星公转的差异，每隔26个月才会出现一次适合转移的窗口。典型的航天器有火星探测器、火星着陆器等。"), TEXT("TMI轨道"));

	
	OrbitMap.Add(OrbitGEO.HTQOrbitType, OrbitGEO);
	OrbitMap.Add(OrbitLEO.HTQOrbitType, OrbitLEO);
	OrbitMap.Add(OrbitIGSO.HTQOrbitType, OrbitIGSO);
	OrbitMap.Add(OrbitMEO.HTQOrbitType, OrbitMEO);
	OrbitMap.Add(OrbitGTO.HTQOrbitType, OrbitGTO);
	OrbitMap.Add(OrbitSSO.HTQOrbitType, OrbitSSO);
	OrbitMap.Add(OrbitTLI.HTQOrbitType, OrbitTLI);
	OrbitMap.Add(OrbitTMI.HTQOrbitType, OrbitTMI);
}

void AUIManager::InitQuestionTable()
{
	TArray<FComprehensiveTests*> AllTests;
	ResourceManager->ComprehensiveTest->GetAllRows<FComprehensiveTests>("", AllTests);
	for(auto Test : AllTests)
	{
		TestsAry.Add(*Test);
	}
	
}

void AUIManager::InitRocketPartDiagram()
{
	TArray<FDiagramUITable*> AllRocketPartsTables;
	ResourceManager->RocketPartTable->GetAllRows("",AllRocketPartsTables);
	for(auto Part: AllRocketPartsTables)
	{
		DiagramMap.Add(Part->RocketType, Part);
	}
}

void AUIManager::CreateVDWidget(EWidgetType WidgetType, bool bReturnWidget)
{
	if(CurWidgetType != EWidgetType::EWT_None)
	{
		WidgetMap[CurWidgetType]->SetVisibility(ESlateVisibility::Hidden);
	}
	
	if(WidgetMap.Contains(WidgetType))
	{
		CurWidgetType = WidgetType;
		WidgetMap[CurWidgetType]->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		return;
	}

	UBaseWidget* Widget = CreateWidget<UBaseWidget>(GetWorld(),ResourceManager->RSWidgetMap[WidgetType]);
	if(bReturnWidget)
	{
		Widget->ReturnWidgetType = CurWidgetType;
	}
	
	Widget->InitWidget();
	CurWidgetType = WidgetType;
	WidgetMap.Add(WidgetType, Widget);
	Widget->AddToViewport();
}



