// Fill out your copyright notice in the Description page of Project Settings.


#include "TcpSocket/VDSocket.h"
#include <codecvt>
#include "SocketSubsystem.h"
#include "Data/DataType.h"
#include "Common/TcpSocketBuilder.h"
#include "GM/VDPawn.h"
#include "Kismet/GameplayStatics.h"
#include "Manager/UIManager.h"
#include "ThirdParty/json-develop/single_include/nlohmann/json.hpp"
#include "UMG/WHomePage.h"

// Sets default values
// 几个版本： 本地版本运行时：Create CLose Tick修改到If
// UIMananger:SendData beginply里 
// Comprehensive :SendData
// BookLaunch: SendData
//本地 Socket关掉 开始按钮打开

//线下开UGAMEINSTANCE

AVDSocket::AVDSocket()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AVDSocket::BeginPlay()
{
	Super::BeginPlay();
    CreateSocket();
	
}

void AVDSocket::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
    CloseSocket();
	
}

void AVDSocket::CreateSocket()
{
	FString _ServerIp;
	int32 Port = 9527;
	
	FString FilePath = FPaths::ProjectDir()/TEXT("Content/Config.ini");
	TArray<FString> FileLines;
	TArray<FString> Words;
	
	if(FFileHelper::LoadFileToStringArray(FileLines, *FilePath))
	{
		for(const FString& Line :FileLines)
		{
			Words.Add(Line);
		}
		_ServerIp = Words[0];
		Time = FCString::Atoi(*Words[1]);
	
	}
	
	TSharedPtr<FInternetAddr> Addr = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();
	bool bIsValid = false;
	
	Addr->SetIp(*_ServerIp, bIsValid);
	Addr->SetPort(Port);

	_TcpSocket = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateSocket(NAME_Stream, "TCPClient", false);
	bConnect = _TcpSocket->Connect(*Addr);

	bool bCanBind = false;
	TSharedRef<FInternetAddr> ClientIP = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->GetLocalHostAddr(*GLog, bCanBind);
	if (ClientIP->IsValid())
	{
		_ClientIP = ClientIP->ToString(false);
	}
	UE_LOG(LogTemp, Log, TEXT("My IP is %s;My Server IP is %s"), *_ClientIP, *_ServerIp)
	
	if(bConnect)
	{
		UE_LOG(LogTemp, Log, TEXT("链接成功"));
		SendData(EActionCode::ClintIP, _ClientIP);
		
		//StartReceiving();
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("链接失败"));
	}

	
}

void AVDSocket::CloseSocket()
{
	if(_TcpSocket)
	{
		_TcpSocket->Close();
		ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->DestroySocket(_TcpSocket);
		_TcpSocket =nullptr;
	}
}



bool AVDSocket::SendData(EActionCode Action, FString Data)
{
	
	TArray<uint8> DataArray;
	
	int32 action = static_cast<int32>(Action);	
	int32 dataAmount = sizeof(action) + FCString::Strlen(*Data);

	if(Action == EActionCode::GetCustomerInfo)
	{
		DataArray.Append(reinterpret_cast<const uint8*>(&dataAmount), sizeof(dataAmount));
		DataArray.Append(reinterpret_cast<const uint8*>(&action), sizeof(action));
	}
	else
	{
		DataArray.Append(reinterpret_cast<const uint8*>(&dataAmount), sizeof(dataAmount));
		DataArray.Append(reinterpret_cast<const uint8*>(&action), sizeof(action));
		DataArray.Append(reinterpret_cast<const uint8*>(TCHAR_TO_UTF8(*Data)), FCString::Strlen(*Data));
	}
	
	int32 BytesSent = 0;
	_TcpSocket->Send(DataArray.GetData(),DataArray.Num(), BytesSent);
	return true;
}

void AVDSocket::SendData()
{
	TArray<uint8> DataArray;

	nlohmann::json ReportJson;
	CraftDataVO MyCraft;

	std::string NAME;
	
	AVDPawn* Pawn = Cast<AVDPawn>(UGameplayStatics::GetPlayerPawn(this, 0));

	
	if (!Pawn->UIManager->SelectTaskItem)
	{
		NAME = Pawn->ResourceManager->CraftMap[L"东方红一号"];
	}
	else
	{
		NAME = Pawn->ResourceManager->CraftMap[Pawn->UIManager->SelectTaskItem->Name];
	}
	MyCraft.craftModel = NAME;
	MyCraft.grade = Pawn->UIManager->GetGrade();
	ReportJson["craft"]["craftModel"] = MyCraft.craftModel;
	ReportJson["craft"]["grade"] = MyCraft.grade;
	std::string ReportData = to_string(ReportJson);
	FString ReportVRData(ReportData.c_str());
	
	int32 action = static_cast<int32>(EActionCode::SetReportVRLog);
	int32 dataAmount = sizeof(action) +FCString::Strlen(*ReportVRData);
	
	DataArray.Append(reinterpret_cast<const uint8*>(&dataAmount), sizeof(dataAmount));
	DataArray.Append(reinterpret_cast<const uint8*>(&action), sizeof(action));
	DataArray.Append(reinterpret_cast<const uint8*>(TCHAR_TO_UTF8(*ReportVRData)), FCString::Strlen(*ReportVRData));
	
	int32 BytesSent = 0;
	_TcpSocket->Send(DataArray.GetData(),DataArray.Num(), BytesSent);
}


void AVDSocket::StartReceiving()
{
	AsyncTask(ENamedThreads::AnyBackgroundThreadNormalTask, [this]()
	{
		while (_TcpSocket->GetConnectionState() == SCS_Connected)
		{
			BytesRead = 0;
			_TcpSocket->Recv(ReceiveArry,sizeof(ReceiveArry),BytesRead);
			if (BytesRead > 0)
			{
				TArray<uint8> NewData;
				NewData.Append(ReceiveArry, BytesRead);
				ReceivedDataQueue.Enqueue(NewData);
			}
		}
	});
}


// Called every frame
void AVDSocket::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (!_TcpSocket || !bConnect)
	{
		return;
	}

	uint32 PendingSize = 0;
	while (_TcpSocket->HasPendingData(PendingSize) && PendingSize > 0)
	{
		uint8 Buffer[40960];
		const int32 ToRead = static_cast<int32>(
			FMath::Min<uint32>(PendingSize, sizeof(Buffer))
		);

		int32 ReadCount = 0;
		if (!_TcpSocket->Recv(Buffer, ToRead, ReadCount) || ReadCount <= 0)
		{
			break;
		}

		ReceiveData.Append(Buffer, ReadCount);
	}

	while (ReceiveData.Num() >= 4)
	{
		int32 BodyLength = 0;
		FMemory::Memcpy(&BodyLength, ReceiveData.GetData(), 4);

		if (BodyLength < 4 || BodyLength > 1024 * 1024)
		{
			UE_LOG(LogTemp, Error, TEXT("错误的包长：%d"), BodyLength);
			ReceiveData.Empty();
			CloseSocket();
			bConnect = false;
			return;
		}

		const int32 FullLength = 4 + BodyLength;
		if (ReceiveData.Num() < FullLength)
		{
			break;
		}

		TArray<uint8> Frame;
		Frame.Append(ReceiveData.GetData(), FullLength);
		ReceiveData.RemoveAt(0, FullLength);

		int32 Action = 0;
		FMemory::Memcpy(&Action, Frame.GetData() + 4, 4);
		ParseData(Frame);

		if (Action == static_cast<int32>(EActionCode::GameStop))
		{
			return; // GameEnd 会重启关卡
		}
	}
	
 /*	TArray<uint8> ReceivedData;
	while (ReceivedDataQueue.Dequeue(ReceivedData))
	{
		ParseData(ReceivedData);
	}

		 				
	if(_TcpSocket->HasPendingData(size))
	{
		BytesRead = 0;
		_TcpSocket->Recv(ReceiveArry,sizeof(ReceiveArry),BytesRead);
		
		TArray<uint8> SubArray;
		//SubArray[0] = ReceiveArry[4];
		
		SubArray.Append(ReceiveArry + 4, 4);
		
		//int32 Value = *(reinterpret_cast<int32*>(SubArray));
		
		int32 Value = *(reinterpret_cast<int32*>(SubArray.GetData()));
		
		UE_LOG(LogTemp, Log, TEXT("MY Value:%d"),Value)
		EActionCode actionCode  = (EActionCode)Value;

		//本地版本只使用开始和结束指令
		if (actionCode == EActionCode::GetCustomerInfo)
		{
			AnalysisCustomerInfo();
			UE_LOG(LogTemp, Log, TEXT("GET CUSTOMERINFO"))
		}
		else if(actionCode == EActionCode::GameStart)
		{
			GameStart();
			UE_LOG(LogTemp, Log, TEXT("GAME START!!"))
		}
		else if(actionCode == EActionCode::GameStop)
		{
			//FullTimeAssessment();
			//新版的开这个
			GameEnd();
		}
	}
		
*/			
}

void AVDSocket::ParseData(TArray<uint8>& Data)
{
	if (Data.Num() < 8)
	{
		return;
	}
	
	TArray<uint8> SubArray;
	SubArray.Append(Data.GetData() + 4, 4);
	int32 Value = *(reinterpret_cast<int32*>(SubArray.GetData()));
	UE_LOG(LogTemp, Log, TEXT("MY Value:%d"),Value)
	EActionCode actionCode  = (EActionCode)Value;

	//本地版本只使用开始和结束指令
	// if (actionCode == EActionCode::GetCustomerInfo)
	// {
	// 	AnalysisCustomerInfo();
	// 	UE_LOG(LogTemp, Log, TEXT("GET CUSTOMERINFO"))
	// }
	//
	if(actionCode == EActionCode::GameStart)
	{
		GameStart();
		UE_LOG(LogTemp, Log, TEXT("GAME START!!"))
	}
	else if(actionCode == EActionCode::GameStop)
	{
		GameEnd();
	}
}
/*	if(actionCode == EActionCode::GameStart)
	{
		GameStart();
		UE_LOG(LogTemp, Log, TEXT("GAME START!!"))
	}
	else if(actionCode == EActionCode::GameStop)
	{
		GameEnd();
	}

}

*/
void AVDSocket::AnalysisCustomerInfo()
{
	if(BytesRead != 0)
	{
/*		uint8 TempArry[40960];
		int i = 0;
		for(auto st : ReceiveArry)
		{
			if(i > 7)
			{
				TempArry[i - 8] = st;
			}
			++i;
		}
		std::string str((char*)TempArry);
	//	UE_LOG(LogTemp, Log, TEXT("Parsed string: %s"), *FString(str.c_str()));  

		nlohmann::json JsonStr = nlohmann::json::parse(str);
*/
		uint8* DataStart = ReceiveArry + 8;
		std::string StdReceivedJSONString(reinterpret_cast<char*>(DataStart), BytesRead - 8);
		nlohmann::json JsonStr = nlohmann::json::parse(StdReceivedJSONString);
		
		bool Playerresult = JsonStr.contains("player");
		bool Historyresult = JsonStr.contains("history");
		
		if(Playerresult && Historyresult)
		{
			nlohmann::json player = JsonStr["player"];

		//	LONG playerId = player["playerId"].get<LONG>();
				
			std::string nickname =player["nickname"].get<std::string>();
			std::wstring Mynickname = stringToWstring(nickname);
			TCHAR* Mynicknametchr = const_cast<wchar_t*>(Mynickname.c_str());
			
			AVDPawn* Pawn = Cast<AVDPawn>(UGameplayStatics::GetPlayerPawn(this, 0));
			Pawn->UserInfoData.IDName = Mynicknametchr;
			
			std::string accomplishment = player["accomplishment"].get<std::string>();
			std::wstring Myaccomplishment = stringToWstring(accomplishment);
			TCHAR* Myaccomplishmenttchr = const_cast<wchar_t*>(Myaccomplishment.c_str());
			Pawn->UserInfoData.Accomplishment = Myaccomplishmenttchr;
			
			std::string sex = player["sex"].get<std::string>();
			auto Mysex = stringToWstring(sex);
			if(Mysex == L"男")
			{
				Pawn->UserInfoData.Gender = EGender::EG_Man;
			}
			else
			{
				Pawn->UserInfoData.Gender = EGender::EG_Woman;
			}
			
			int32 score = player["score"].get<int32>();
			Pawn->UserInfoData.Grades = score;
			
			int32 craftNumber = player["craftNumber"].get<int32>();
			Pawn->UserInfoData.HTQNumbers = craftNumber;
			TArray<FMyCraftData> TestArry;
			nlohmann::json history = JsonStr["history"];
			for (nlohmann::json jsonobj : history)
			{
				FMyCraftData Tempobj;
					
				std::string craftModel = jsonobj["craftModel"].get<std::string>();
				std::wstring MycraftModel = stringToWstring(craftModel);
				Tempobj.craftModel = WstringToFstring(MycraftModel);
				
				std::string finishTime = jsonobj["finishTime"].get<std::string>();
				std::wstring MyfinishTime = stringToWstring(finishTime);
				Tempobj.finishTime = WstringToFstring(MyfinishTime);
				
				Tempobj.grade   = jsonobj["grade"].get<int32>();
				
				TestArry.Add(Tempobj);
			}
			Pawn->UIManager->HistoryArry = TestArry;
			
		}
	}
}


void AVDSocket::GameStart()
{
	AVDPawn* VdPawn = Cast<AVDPawn>(UGameplayStatics::GetPlayerPawn(this, 0));
	if(VdPawn)
	{
	UWHomePage* HomePage = Cast<UWHomePage>(VdPawn->UIManager->WidgetMap[EWidgetType::EWT_HomePage]);
	HomePage->GameStart();
	}
	//LocalDataArchive(EActionCode::GameStart);
	UE_LOG(LogTemp,Log,TEXT("  GameStart   "));
}

void AVDSocket::GameEnd()
{
	//LocalDataArchive(EActionCode::GameStop);
	GetWorld()->GetFirstPlayerController()->ConsoleCommand(TEXT("RestartLevel"));
	UE_LOG(LogTemp,Log,TEXT("  GameEnd   "));
}

void AVDSocket::LocalDataArchive(EActionCode ECode)
{
	FString TextPath = FPaths::ProjectDir() + TEXT("Content/Log.txt");
	TextPath = FPaths::ConvertRelativePathToFull(TextPath);
	TArray<FString> TextLines;
	
	FDateTime Dt = FDateTime::Now();
	//UE_LOG(LogTemp, Display, TEXT("当前时间:%d年%d月%d日%d时%d分%d秒"), Dt.GetYear(), Dt.GetMonth(), Dt.GetDay(), Dt.GetHour(), Dt.GetMinute(), Dt.GetSecond());
	//%d月%d日%d时%d分%d秒  , Dt.GetMonth(), Dt.GetDay(), Dt.GetHour(), Dt.GetMinute(), Dt.GetSecond()

	
	FString TextContent = FString::FromInt(Dt.GetYear());
	TextContent.Append(TEXT("年"));
	TextContent.Append(FString::FromInt(Dt.GetMonth()));
	TextContent.Append(TEXT("月"));
	TextContent.Append(FString::FromInt(Dt.GetDay()));
	TextContent.Append(TEXT("日"));
	TextContent.Append(FString::FromInt(Dt.GetHour()));
	TextContent.Append(TEXT("时"));
	TextContent.Append(FString::FromInt(Dt.GetMinute()));
	TextContent.Append(TEXT("分"));
	TextContent.Append(FString::FromInt(Dt.GetSecond()));
	TextContent.Append(TEXT("秒    "));

	if (ECode == EActionCode::GameStart)
	{
		FString GameStart = TEXT("[游戏开始] \n");
		TextContent = TextContent.Append(GameStart);
		TextLines.Add(TextContent);
		FFileHelper::SaveStringArrayToFile(TextLines, *TextPath,FFileHelper::EEncodingOptions::ForceUTF8);
	}
	else if(ECode == EActionCode::GameStop)
	{
		AVDPawn* VdPawn = Cast<AVDPawn>(UGameplayStatics::GetPlayerPawn(this, 0));
		float TotalTime = 60 * Time;
		float UsingTime = TotalTime - ((VdPawn->UIManager->ManagerMinute) * 60.0 + VdPawn->UIManager->ManagerSecond);
		
		FString GameStop = TEXT("[游戏结束] \n");
		TextContent = TextContent.Append(GameStop);
		TextLines.Add(TextContent);
		TextLines.Add(TEXT("体验时长： "));
		TextLines.Add(FString::FromInt(FMath::FloorToInt(UsingTime)));
		TextLines.Add(TEXT("秒    OK\n\n"));
		
	}
	
}

void AVDSocket::SendReportLog()
 {
 	TArray<uint8> DataSendArray;
 	nlohmann::json ReportJson;
 	
	ReportJson["experienceLog"]["id"] = NULL;
	ReportJson["experienceLog"]["member"] = NULL;
	ReportJson["experienceLog"]["ticket"] = NULL;
	ReportJson["experienceLog"]["content"] = NULL;
	ReportJson["experienceLog"]["role"] = NULL;
	ReportJson["experienceLog"]["equipment"] = NULL;
	ReportJson["experienceLog"]["startTime"] = NULL;
	ReportJson["experienceLog"]["endTime"] = NULL;
	ReportJson["experienceLog"]["finished"] = NULL;
	ReportJson["experienceLog"]["score"] = 91;
	ReportJson["experienceLog"]["marks"] = 0;
	ReportJson["experienceLog"]["shopId"] = NULL;

	ReportJson["history"];
	ReportJson["questions"] = NULL;
	
	std::string str = to_string(ReportJson);
	FString ReportLog(str.c_str());

 	int32 action = static_cast<int32>(EActionCode::SetReportVRLog);
 	int32 dataAmount = sizeof(action) + FCString::Strlen(*ReportLog);
 	
 	DataSendArray.Append(reinterpret_cast<const uint8*>(&dataAmount), sizeof(dataAmount));
 	DataSendArray.Append(reinterpret_cast<const uint8*>(&action), sizeof(action));
 	DataSendArray.Append(reinterpret_cast<const uint8*>(TCHAR_TO_UTF8(*ReportLog)),FCString::Strlen(*ReportLog));

	int32 BytesSent = 0;
 	_TcpSocket->Send(DataSendArray.GetData(),DataSendArray.Num(), BytesSent);

	
 }

void AVDSocket::FullTimeAssessment()
{
	AVDPawn* VdPawn = Cast<AVDPawn>(UGameplayStatics::GetPlayerPawn(this, 0));
	float TotalTime = 60 * Time;
	float UsingTime;
	UsingTime = TotalTime - ((VdPawn->UIManager->ManagerMinute) * 60.0 +  VdPawn->UIManager->ManagerSecond);
	
	if (UsingTime >= TotalTime * 0.7)
	{
		SendLocalReportLog();
		GameEnd();
	}
	else
	{
		GameEnd();
	}
}

void AVDSocket::SendLocalReportLog()
{
	SendData(EActionCode::SetReportVRLog,"");
}


std::wstring AVDSocket::stringToWstring(const std::string& str)
{
	std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
	return converter.from_bytes(str);
}

FString AVDSocket::WstringToFstring(std::wstring& str)
{
	FString ReString;
	TCHAR* tchr = const_cast<wchar_t*>(str.c_str());
	ReString = tchr;
	return ReString;
}
