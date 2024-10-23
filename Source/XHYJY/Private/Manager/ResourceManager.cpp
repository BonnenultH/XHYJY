// Fill out your copyright notice in the Description page of Project Settings.


#include "Manager/ResourceManager.h"
#include "MediaPlayer.h"
#include "MediaSource.h"
#include "Materials/MaterialParameterCollection.h"
#include "LevelSequence.h"
#include "LevelSequencePlayer.h"
#include "LevelSequenceActor.h"


// Sets default values
AResourceManager::AResourceManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	InitRSWidgetMap();
	InitMediaResource();
	
	ConstructorHelpers::FObjectFinder<UMaterialParameterCollection> GenderObj(TEXT("'/Game/UMG/UserFile/Texture/Meidum_Mat.Meidum_Mat'"));
	GenderMaterial= GenderObj.Object;
	
	ConstructorHelpers::FObjectFinder<UTexture2D> TexProgress(TEXT("'/Game/UMG/Child/PersonInfo/LoadingOk.LoadingOk'"));
	ProgressOkImage= TexProgress.Object;

	ConstructorHelpers::FObjectFinder<UTexture2D> TexSelectBG(TEXT("'/Game/UMG/Child/ItemTask/Selected.Selected'"));
	SelectBG= TexSelectBG.Object;
	
	ConstructorHelpers::FObjectFinder<UTexture2D> TexUnSelectBG(TEXT("'/Game/UMG/Child/ItemTask/Unselect.Unselect'"));
	UnSelectBG= TexUnSelectBG.Object;
	
	ConstructorHelpers::FObjectFinder<UTexture2D> TexCheckBar(TEXT("'/Game/UMG/Child/RocketMode/CheckBar.CheckBar'"));
	CheckBar = TexCheckBar.Object;

	ConstructorHelpers::FObjectFinder<UTexture2D> TexUnCheckBar(TEXT("'/Game/UMG/Child/RocketMode/UnCheckBar.UnCheckBar'"));
	UnCheckBar = TexUnCheckBar.Object;

	ConstructorHelpers::FObjectFinder<UTexture2D> StatesRocketLightOBj(TEXT("'/Game/UMG/Child/Textures/Rocket_Highlight.Rocket_Highlight'"));
	StatesRocketLight = StatesRocketLightOBj.Object;

	ConstructorHelpers::FObjectFinder<UTexture2D> StatesFireplaceLightObj(TEXT("'/Game/UMG/Child/Textures/FirePlace_Highlight.FirePlace_Highlight'"));
	StatesFireplaceLight = StatesFireplaceLightObj.Object;
		
	ConstructorHelpers::FObjectFinder<UDataTable> TableObj(TEXT("'/Game/UMG/DataTable/HTQTask.HTQTask'"));
	HTQTasks= TableObj.Object;
	
	ConstructorHelpers::FObjectFinder<UDataTable> RocketSeleOBj(TEXT("'/Game/UMG/DataTable/RocketTable.RocketTable'"));
	RocketSelect= RocketSeleOBj.Object;

	ConstructorHelpers::FObjectFinder<UDataTable> RocketPartTableObj(TEXT("'/Game/UMG/DataTable/RocketPartDiagram.RocketPartDiagram'"));
	RocketPartTable= RocketPartTableObj.Object;

	ConstructorHelpers::FObjectFinder<UDataTable> ComprehensiveTestObj(TEXT("'/Game/UMG/DataTable/ComprehensiveTest.ComprehensiveTest'"));
	ComprehensiveTest= ComprehensiveTestObj.Object;
	
	ConstructorHelpers::FObjectFinder<UTexture2D> CapacityIconObj(TEXT("'/Game/UMG/Child/RocketMode/Tabel.Tabel'"));
	CapacityIcon= CapacityIconObj.Object;

	ConstructorHelpers::FObjectFinder<UTexture2D> PriceIconObj(TEXT("'/Game/UMG/Child/RocketMode/PriceTable.PriceTable'"));
	PriceIcon= PriceIconObj.Object;
	
	ConstructorHelpers::FObjectFinder<UTexture2D> RocketSeleBGObj(TEXT("'/Game/UMG/Child/RocketMode/BG_Selected.BG_Selected'"));
	RocketSelectedBG= RocketSeleBGObj.Object;

	ConstructorHelpers::FObjectFinder<UTexture2D> RocketUnselectedBGObj(TEXT("'/Game/UMG/Child/RocketMode/BG.BG'"));
	RocketUnselectedBG= RocketUnselectedBGObj.Object;

	ConstructorHelpers::FObjectFinder<UTexture2D> RocketWrongObj(TEXT("'/Game/UMG/Child/RocketMode/WrongBG.WrongBG'"));
	RocketWrong= RocketWrongObj.Object;
	
	ConstructorHelpers::FObjectFinder<UTexture2D> JQObj(TEXT("'/Game/UMG/Launch/button/JQ.JQ'"));
	JQ= JQObj.Object;

	ConstructorHelpers::FObjectFinder<UTexture2D> TYObj(TEXT("'/Game/UMG/Launch/button/TY.TY'"));
	TY= TYObj.Object;
	
	ConstructorHelpers::FObjectFinder<UTexture2D> XCObj(TEXT("'/Game/UMG/Launch/button/XC.XC'"));
	XC= XCObj.Object;
	
	ConstructorHelpers::FObjectFinder<UTexture2D> WCObj(TEXT("'/Game/UMG/Launch/button/WC.WC'"));
	WC= WCObj.Object;
	
	ConstructorHelpers::FObjectFinder<UTexture2D> HoistDownObj(TEXT("'/Game/UMG/Hoisting/ImageDiagram/Down.Down'"));
	HoistDown = HoistDownObj.Object;

	ConstructorHelpers::FObjectFinder<UTexture2D> TestBGObj(TEXT("'/Game/UMG/ComprehensiveTest/BG.BG'"));
	TestBG = TestBGObj.Object;
	
	ConstructorHelpers::FObjectFinder<UTexture2D> TestWarningObj(TEXT("'/Game/UMG/ComprehensiveTest/BG_Warning.BG_Warning'"));
	TestWarning = TestWarningObj.Object;
	
	ConstructorHelpers::FObjectFinder<UMaterial> WarningObj(TEXT("'/Game/UMG/HistoryTasks/Texture/M_Warning.M_Warning'"));
	WarningMaterial= WarningObj.Object;

	ConstructorHelpers::FObjectFinder<UTexture2D> SObj(TEXT("'/Game/UMG/BookLaunch/S.S'"));
	S= SObj.Object;
	ConstructorHelpers::FObjectFinder<UTexture2D> AObj(TEXT("'/Game/UMG/BookLaunch/A.A'"));
	A= AObj.Object;
	ConstructorHelpers::FObjectFinder<UTexture2D> BObj(TEXT("'/Game/UMG/BookLaunch/B.B'"));
	B= BObj.Object;
	ConstructorHelpers::FObjectFinder<UTexture2D> CObj(TEXT("'/Game/UMG/BookLaunch/C.C'"));
	C= CObj.Object;
	ConstructorHelpers::FObjectFinder<UTexture2D> DObj(TEXT("'/Game/UMG/BookLaunch/D.D'"));
	D= DObj.Object;

	ConstructorHelpers::FObjectFinder<USoundWave> BGMSoundUI(TEXT("'/Game/Sound/UIbgm.UIbgm'"));
	BGMSound = BGMSoundUI.Object;

	ConstructorHelpers::FObjectFinder<USoundWave> StartGameOBj(TEXT("'/Game/Sound/Startgame.Startgame'"));
	StartGame = StartGameOBj.Object;

	ConstructorHelpers::FObjectFinder<USoundWave> MenuObj(TEXT("'/Game/Sound/Menu.Menu'"));
	Menu = MenuObj.Object;

	ConstructorHelpers::FObjectFinder<USoundWave> ButtonObj(TEXT("'/Game/Sound/button.button'"));
	Button = ButtonObj.Object;
	
	ConstructorHelpers::FObjectFinder<USoundWave> ReturnObj(TEXT("'/Game/Sound/Page_close.Page_close'"));
	Return = ReturnObj.Object;

	ConstructorHelpers::FObjectFinder<USoundWave> TakeTasksSoundObj(TEXT("'/Game/Sound/Mission_start.Mission_start'"));
	TakeTasksSound = TakeTasksSoundObj.Object;
	
	ConstructorHelpers::FObjectFinder<USoundWave> WrongAnswerObj(TEXT("'/Game/Sound/WrongRocketselection.WrongRocketselection'"));
	WrongSelection= WrongAnswerObj.Object;

	ConstructorHelpers::FObjectFinder<USoundWave> RightSelectionObj(TEXT("'/Game/Sound/rightanswer.rightanswer'"));
	RightSelection= RightSelectionObj.Object;
	
	ConstructorHelpers::FObjectFinder<USoundWave> FactoryObj(TEXT("'/Game/Sound/factoryopen.factoryopen'"));
	FactoryOpen= FactoryObj.Object;

	ConstructorHelpers::FObjectFinder<USoundWave> FactoryBGObj(TEXT("'/Game/Sound/Factorybackgroundsound.Factorybackgroundsound'"));
	FactoryBG= FactoryBGObj.Object;

	ConstructorHelpers::FObjectFinder<USoundWave> ScanObj(TEXT("'/Game/Sound/Scan.Scan'"));
	Scan= ScanObj.Object;

	ConstructorHelpers::FObjectFinder<USoundWave> AnswerRightObj(TEXT("'/Game/Sound/rightanswer.rightanswer'"));
	AnswerRight= AnswerRightObj.Object;
	ConstructorHelpers::FObjectFinder<USoundWave> AnswerWrongObj(TEXT("'/Game/Sound/wronganswer.wronganswer'"));
	AnswerWrong= AnswerWrongObj.Object;
	
	ConstructorHelpers::FObjectFinder<USoundWave> FactoryEndObj(TEXT("'/Game/Sound/factoryend.factoryend'"));
	FactoryEnd= FactoryEndObj.Object;

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
	
	LevelSequence = LoadObject<ULevelSequence>(this,TEXT("'/Game/Model/Sequence/JZ_Sequence.JZ_Sequence'"));
	MainLevelSequencePlayer = MainLevelSequencePlayer->CreateLevelSequencePlayer(GetWorld(), LevelSequence, FMovieSceneSequencePlaybackSettings(),currentLevelSequenceActor);

	LevelEndingSequence = LoadObject<ULevelSequence>(this, TEXT("'/Game/Model/Sequence/CZ_Sequence.CZ_Sequence'")); 
	EndingLevelSequencePlayer = EndingLevelSequencePlayer->CreateLevelSequencePlayer(GetWorld(), LevelEndingSequence, FMovieSceneSequencePlaybackSettings(),EndLevelSequenceActor);

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
	RSWidgetMap.Add(EWidgetType::EWT_Launch,LoadWidgetFile(TEXT("'/Game/UMG/WBP_Launch.WBP_Launch_C'")));
	RSWidgetMap.Add(EWidgetType::EWT_Hoisting, LoadWidgetFile(TEXT("'/Game/UMG/WBP_Hoisting.WBP_Hoisting_C'")));
	RSWidgetMap.Add(EWidgetType::EWT_ComprehensiveTest, LoadWidgetFile(TEXT("'/Game/UMG/WBP_ComprehensiveTest.WBP_ComprehensiveTest_C'")));
	RSWidgetMap.Add(EWidgetType::EWT_BookLaunch, LoadWidgetFile(TEXT("'/Game/UMG/WBP_BookLaunch.WBP_BookLaunch_C'")));

}

void AResourceManager::InitMediaResource()
{
	ConstructorHelpers::FObjectFinder<UMediaPlayer> MediaPlayer(TEXT("'/Game/UMG/Homepage/MediaVideo/MP_Earth.MP_Earth'"));
	MP= MediaPlayer.Object;
	ConstructorHelpers::FObjectFinder<UMediaSource> MediaSource(TEXT("'/Game/UMG/Homepage/MediaVideo/Earth.Earth'"));
	MS= MediaSource.Object;
}



