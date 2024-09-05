// Fill out your copyright notice in the Description page of Project Settings.


#include "Manager/ResourceManager.h"
#include "MediaPlayer.h"
#include "MediaSource.h"
#include "Materials/MaterialParameterCollection.h"


// Sets default values
AResourceManager::AResourceManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	InitRSWidgetMap();
	InitMediaResource();
	
	ConstructorHelpers::FObjectFinder<UMaterialParameterCollection> GenderObj(TEXT("'/Game/UMG/UserFile/Texture/Meidum_Mat.Meidum_Mat'"));
	GenderMaterial = GenderObj.Object;
	
	ConstructorHelpers::FObjectFinder<UTexture2D> TexProgress(TEXT("'/Game/UMG/Child/PersonInfo/LoadingOk.LoadingOk'"));
	ProgressOkImage = TexProgress.Object;

	ConstructorHelpers::FObjectFinder<UTexture2D> TexSelectBG(TEXT("'/Game/UMG/Child/ItemTask/Selected.Selected'"));
	SelectBG = TexSelectBG.Object;
	
	ConstructorHelpers::FObjectFinder<UTexture2D> TexUnSelectBG(TEXT("'/Game/UMG/Child/ItemTask/Unselect.Unselect'"));
	UnSelectBG = TexUnSelectBG.Object;
	
	ConstructorHelpers::FObjectFinder<UDataTable> TableObj(TEXT("'/Game/UMG/DataTable/HTQTask.HTQTask'"));
	HTQTasks = TableObj.Object;
}

// Called when the game starts or when spawned
void AResourceManager::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AResourceManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AResourceManager::InitManager()
{
	Super::InitManager();
	GenderMaterialInstance = GetWorld()->GetParameterCollectionInstance(GenderMaterial);
	InitOrbitsInfo();
}

void AResourceManager::InitOrbitsInfo()
{
	OrbitsInfoMap.Add(EOrbit::ELEO, TEXT("低地（球）轨道/近地（球）轨道（LEO：Low Earth Orbit）距地面约200-1200千米的近圆轨道。典型航天器：载人飞船、空间站、对地观测卫星以及一些新型通信卫星系统等。"));
	OrbitsInfoMap.Add(EOrbit::EMEO, TEXT("中地球轨道（MEO：Middle Earth Orbit）轨道高度为1200-36000公里之间；GPS、GLONASS都属于此类轨道。美国GPS系统、俄罗斯GLONASS系统、欧盟伽利略系统和中国北斗系统均使用了高度20000-24000km的约55°倾角的中地球轨道。"));
	OrbitsInfoMap.Add(EOrbit::EGEO, TEXT("即轨道倾角i=0°的地球同步轨道，距地面约36000公里的圆轨道。卫星与地面的相对位置保持不变，轨道周期与地球自转周期一致。典型航天器：通信、对地观测、导航、预警、气象等民用和军用卫星。"));
	OrbitsInfoMap.Add(EOrbit::EGTO, TEXT("地球同步转移轨道（GTO：Geostationary Transfer Orbit ）指距地面近地点约200公里，远地点约36000公里的椭圆轨道。地球同步转移轨道为霍曼转移轨道的运用之一，为椭圆形轨道，经加速后可达地球静止轨道(GEO)。近地点多在1000公里以下，远地点则为地球静止轨道高度36000公里。地球同步转移轨道一般只作为地球同步轨道的过渡轨道。"));
	OrbitsInfoMap.Add(EOrbit::ESSO, TEXT("太阳同步轨道（SSO：Sun-synchronous Orbit ）又称近地太阳同步轨道，典型的太阳同步轨道高度大约是800km，周期在96-100分钟范围，倾角大致在98°附近，以满足任务需要。其轨道平面始终与太阳保持固定的取向，轨道平面自西向东保持360度/年的进动，轨道平面绕地球自转轴旋转的方向与地球公转方向相同。典型航天器：气象卫星、光学遥感卫星等。"));
	OrbitsInfoMap.Add(EOrbit::EIGSO, TEXT("倾斜地球同步轨道（IGSO：Inclined Geosynchronous Orbit ）即轨道倾角i≠0°的地球同步轨道，其星下点轨迹是一条“8”字形的封闭曲线，中国北斗卫星导航系统的其中三颗卫星位于55°倾角的倾斜地球同步轨道。"));
	OrbitsInfoMap.Add(EOrbit::ETLI, TEXT("地月转移轨道（Trans-Lunar injection，缩写为TLI）是指从月球探测器通过不断加速、脱离地球引力、飞向月球开始，到被月球引力捕获、近月制动为止的轨道段。典型的地月转移轨道，近地点在低地球轨道，远地点大约在400000公里的月球轨道。典型的航天器有月球探测器、地月中继卫星、月球着陆器、载人登月飞船等。"));
	OrbitsInfoMap.Add(EOrbit::ETMI, TEXT("地火转移轨道（Trans-Mars injection，TMI），是一类特殊的日心轨道。从地球发射的人造卫星或探测器会通过这类轨道进入火星轨道，典型的地火转移轨道，近日点在1.3个天文单位，远日点在1.6个天文单位，由于地球和火星公转的差异，每隔26个月才会出现一次适合转移的窗口。典型的航天器有火星探测器、火星着陆器等。"));
}

TSubclassOf<UUserWidget> AResourceManager::LoadWidgetFile(FString Path)
{
	return ConstructorHelpers::FClassFinder<UUserWidget>(*Path).Class;
}

void AResourceManager::InitRSWidgetMap()
{
	RSWidgetMap.Add(EWidgetType::EWT_HomePage,LoadWidgetFile(TEXT("'/Game/UMG/WBP_HomePage.WBP_HomePage_C'")));
	RSWidgetMap.Add(EWidgetType::EWT_UserFile,LoadWidgetFile(TEXT("'/Game/UMG/WBP_UserFile.WBP_UserFile_C'")));
	RSWidgetMap.Add(EWidgetType::EWT_HistoryTasks,LoadWidgetFile(TEXT("'/Game/UMG/WBP_HistoryTasks.WBP_HistoryTasks_C'")));
	RSWidgetMap.Add(EWidgetType::EWT_TakeTasks,LoadWidgetFile(TEXT("'/Game/UMG/WBP_TakeTasks.WBP_TakeTasks_C'")));
	RSWidgetMap.Add(EWidgetType::EWT_Rules,LoadWidgetFile(TEXT("'/Game/UMG/WBP_Rules.WBP_Rules_C'")));
	RSWidgetMap.Add(EWidgetType::EWT_Orbits,LoadWidgetFile(TEXT("'/Game/UMG/WBP_Oribit.WBP_Oribit_C'")));
	RSWidgetMap.Add(EWidgetType::EWT_RocketSelect,LoadWidgetFile(TEXT("'/Game/UMG/WBP_RocketSelect.WBP_RocketSelect_C'")));

}

void AResourceManager::InitMediaResource()
{
	ConstructorHelpers::FObjectFinder<UMediaPlayer> MediaPlayer(TEXT("'/Game/UMG/Homepage/MediaVideo/MP_Earth.MP_Earth'"));
	MP= MediaPlayer.Object;
	ConstructorHelpers::FObjectFinder<UMediaSource> MediaSource(TEXT("'/Game/UMG/Homepage/MediaVideo/Earth.Earth'"));
	MS= MediaSource.Object;
}



