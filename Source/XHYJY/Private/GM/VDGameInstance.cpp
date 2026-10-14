// Fill out your copyright notice in the Description page of Project Settings.


#include "GM/VDGameInstance.h"

#include <codecvt>
#include "Sockets.h"
#include "SocketSubsystem.h"
#include "Data/DataType.h"
#include "GM/VDPawn.h"
#include "Kismet/GameplayStatics.h"
#include "Manager/UIManager.h"
#include "UMG/WHomePage.h"
#include "XHYJY/ThirdParty/include/json.hpp"



void UVDGameInstance::Init()
{
	Super::Init();
	FMySocketConnectionDelegateState.BindUObject(this, &UVDGameInstance::CreateSocket);
	GetWorld()->GetTimerManager().SetTimer(TickHandle, this, &UVDGameInstance::CustomTick, TickInternal, true);

	CreateSocket();
	  
}

void UVDGameInstance::Shutdown()
{
	Super::Shutdown();
	
	FMySocketConnectionDelegateState.Unbind();
	if(GetWorld())
	{
		GetWorld()->GetTimerManager().ClearTimer(TickHandle);
		TickHandle.Invalidate(); 
	}
	ShutDownSocket();
	
}

void UVDGameInstance::CreateSocket()
{
	ShutDownSocket();
	
	FString _ServerIp;
	FString _ClientIP;
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
	UE_LOG(LogTemp, Log, TEXT("Config 文件读取"))

	
	//创建FinternetAddr地址
	TSharedPtr<FInternetAddr> Addr = ISocketSubsystem::Get(FName(L"WINDOWS"))->CreateInternetAddr();
	bool bIsValid = false;
	
	Addr->SetIp(*_ServerIp, bIsValid);
	Addr->SetPort(Port);

	//创建TCPSocket   
	TcpSocket = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateSocket(NAME_Stream, "TCPClient", false);
	bConnect = TcpSocket->Connect(*Addr);

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
		DisconnectTime = 0;
		
		GetWorld()->GetTimerManager().ClearTimer(ReConnectAttemp);
		SendData(EActionCode::ClintIP, _ClientIP);
		
		StartHeartBeat();
		
	} 
	else
	{
		UE_LOG(LogTemp, Log, TEXT("链接失败"));
		if(ReconnectSocketHandle.IsValid())
		{
			GetWorld()->GetTimerManager().ClearTimer(ReconnectSocketHandle);
		}
		ReConnectSocket();
	}
}

void UVDGameInstance::ReConnectSocket()
{
	//失败重连
	if(!GetWorld()) return;
	
	GetWorld()->GetTimerManager().SetTimer(ReconnectSocketHandle, this, &UVDGameInstance::CreateSocket, ReconnectInterval, false);
	
}

void UVDGameInstance::ShutDownSocket()
{
	if(TcpSocket)
	{
		UE_LOG(LogTemp, Log, TEXT("Tcp销毁关闭"))
		TcpSocket->Close();
		ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->DestroySocket(TcpSocket);
		TcpSocket =nullptr;
	}
	PendingData.Empty();
	
}

void UVDGameInstance::CustomTick()
{

	// if(CheckConnection())
	// { 
		if(TcpSocket->HasPendingData(size))
		{
			TArray<uint8> TempBuffer;
			TempBuffer.SetNumUninitialized(FMath::Min(static_cast<int32>(size), 40960));

			BytesRead = 0;
			TcpSocket->Recv(TempBuffer.GetData(),TempBuffer.Num(),BytesRead);
			PendingData.Append(TempBuffer.GetData(),BytesRead);
			ProcessPendingData();
		}
	//}
	
	
}

void UVDGameInstance::StartHeartBeat()
{
	if (!TcpSocket || !bConnect) return;
    
	// 获取游戏世界实例
	UWorld* World = GEngine->GetWorldFromContextObjectChecked(this);
	if (!World) return;

	StopHeartBeat();
	// 设置心跳定时器
	GetWorld()->GetTimerManager().SetTimer(HeartbeatTimerHandle,[this]()
		{
			// 先检查连接状态
			if (!CheckConnection())
			{
				StopHeartBeat();
				ShutDownSocket();
				GetWorld()->GetTimerManager().SetTimer(ReConnectAttemp, this,&UVDGameInstance::CreateSocket, HeartbeatInterval, false);
				return; 
			}
            
			// 发送心跳
			SendHeartBeat();
		},
		HeartbeatInterval,
		true // 循环执行
	);
    
	UE_LOG(LogTemp, Log, TEXT("Heartbeat started with interval: %.1fs"), HeartbeatInterval);
}

void UVDGameInstance::SendHeartBeat()
{
	if (!TcpSocket || !bConnect) return;
    
	
	uint8 HeartbeatByte = 0x00; // 心跳包标识
	int32 BytesSent = 0;
    
	bool bSent = TcpSocket->Send(&HeartbeatByte, sizeof(HeartbeatByte), BytesSent);
    
	if (bSent && (BytesSent == sizeof(HeartbeatByte)))
	{
		//心跳发送成功
		 UE_LOG(LogTemp, Log, TEXT("Heartbeat sent"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to send heartbeat"));
		
		// while (DisconnectTime <= 20)
		// {
		// 	DisconnectTime++;
		// 	UE_LOG(LogTemp, Log, TEXT("DIsconnect"))
		// 	return;
		// }
		// CreateSocket();
	}
}

void UVDGameInstance::StopHeartBeat()
{
	UWorld* World = GEngine->GetWorldFromContextObjectChecked(this);
	if (World && HeartbeatTimerHandle.IsValid())
	{
		World->GetTimerManager().ClearTimer(HeartbeatTimerHandle);
		UE_LOG(LogTemp, Log, TEXT("Heartbeat stopped"));
	}
}

bool UVDGameInstance::CheckConnection()
{
	if (!TcpSocket) return false;
    
	// 方法1：检查Socket状态
	ESocketConnectionState State = TcpSocket->GetConnectionState();
	if (State == SCS_ConnectionError)
	{
		UE_LOG(LogTemp, Warning, TEXT("Socket connection error detected"));
		return false;
	}
	
	
	// 方法2：发送0字节探测  
	uint8 Dummy;
	int32 BytesSent;
	if (!TcpSocket->Send(&Dummy, 0, BytesSent))
	{
		UE_LOG(LogTemp, Warning, TEXT("Connection probe failed"));
		return false;
	}
	
	return true;
}




void UVDGameInstance::ProcessPendingData()
{
	while(PendingData.Num() >= 4)
	{
		int32 PackageSize = 0;
		FMemory::Memcpy(&PackageSize, PendingData.GetData(), 4);

		if(PendingData.Num() >= 4 + PackageSize)
		{
			PackageData.Empty();
			
			PackageData.Append(PendingData.GetData() + 4, PackageSize);
			PendingData.RemoveAt(0, 4 + PackageSize);

			int32 Value = *(reinterpret_cast<int32*>(PackageData.GetData()));
			
			UE_LOG(LogTemp, Log, TEXT("MY Value:%d"),Value)
			EActionCode ActionCode  = (EActionCode)Value;


			/*
				if (ActionCode ==  EActionCode::GetCustomerInfo)
			{
				AnalysisCustomerInfo();
			}
			else
			*/
			
			if(ActionCode == EActionCode::GameStart)
			{
				GameStart();
			}
			else if(ActionCode == EActionCode::GameStop)
			{
				FullTimeAssessment();
				//新版的开这个GameEnd();
				
			}
			
			
		}
	}
}


void UVDGameInstance::AnalysisCustomerInfo()
{
	if(BytesRead != 0)
	{
		PackageData.RemoveAt(0,4);
		std::string StdReceivedJSONString(reinterpret_cast<const char*>(PackageData.GetData()), PackageData.Num());

		nlohmann::json JsonStr = nlohmann::json::parse(StdReceivedJSONString);
		
		bool Playerresult = JsonStr.contains("player");
		bool Historyresult = JsonStr.contains("history");
		
		if(Playerresult && Historyresult)
		{
			nlohmann::json player = JsonStr["player"];
			
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


bool UVDGameInstance::SendData(EActionCode Action, FString Data) 
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
	TcpSocket->Send(DataArray.GetData(),DataArray.Num(), BytesSent);
	return true;
	
}

void UVDGameInstance::SendData(EActionCode EAction)
{
	TArray<uint8> DataArray;
	
	int32 action = static_cast<int32>(EAction);	
	int32 dataAmount = sizeof(action);
	
		DataArray.Append(reinterpret_cast<const uint8*>(&dataAmount), sizeof(dataAmount));
		DataArray.Append(reinterpret_cast<const uint8*>(&action), sizeof(action));
	
	int32 BytesSent = 0;
	TcpSocket->Send(DataArray.GetData(),DataArray.Num(), BytesSent);
}



void UVDGameInstance::SendData()
{
	TArray<uint8> DataArray;

	nlohmann::json ReportJson;
	CraftDataVO MyCraft;

	AVDPawn* Pawn = Cast<AVDPawn>(UGameplayStatics::GetPlayerPawn(this, 0));
	std::string NAME = Pawn->ResourceManager->CraftMap[Pawn->UIManager->SelectTaskItem->Name];
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
	TcpSocket->Send(DataArray.GetData(),DataArray.Num(), BytesSent);
}

void UVDGameInstance::SendReportLog()
{
	SendData(EActionCode::GameStop);

}


void UVDGameInstance::GameStart()
{
	AVDPawn* VdPawn = Cast<AVDPawn>(UGameplayStatics::GetPlayerPawn(this, 0));
	if(VdPawn)
	{
		UWHomePage* HomePage = Cast<UWHomePage>(VdPawn->UIManager->WidgetMap[EWidgetType::EWT_HomePage]);
		HomePage->GameStart();
	}
	LocalDataArchive(EActionCode::GameStart);
	UE_LOG(LogTemp,Log,TEXT("  GameStart   "));
}

void UVDGameInstance::GameEnd()
{
	LocalDataArchive(EActionCode::GameStop);
	//SendData(EActionCode::GameStop);
	GetWorld()->GetFirstPlayerController()->ConsoleCommand(TEXT("RestartLevel"));
	UE_LOG(LogTemp,Log,TEXT("  GameEnd   "));
}


void UVDGameInstance::FullTimeAssessment()
{
	AVDPawn* VdPawn = Cast<AVDPawn>(UGameplayStatics::GetPlayerPawn(this, 0));
	float TotalTime = 60 * Time;
	float UsingTime = TotalTime - ((VdPawn->UIManager->ManagerMinute) * 60.0 +  VdPawn->UIManager->ManagerSecond);
	
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

void UVDGameInstance::SendLocalReportLog()
{
	SendData(EActionCode::SetReportVRLog);
	// TArray<uint8> DataSendArray;
	// nlohmann::json ReportJson;
    // 	
	// ReportJson["experienceLog"]["id"] = NULL;
	// ReportJson["experienceLog"]["member"] = NULL;
	// ReportJson["experienceLog"]["ticket"] = NULL;
	// ReportJson["experienceLog"]["content"] = NULL;
	// ReportJson["experienceLog"]["role"] = NULL;
	// ReportJson["experienceLog"]["equipment"] = NULL;
	// ReportJson["experienceLog"]["startTime"] = NULL;
	// ReportJson["experienceLog"]["endTime"] = NULL;
	// ReportJson["experienceLog"]["finished"] = NULL;
	// ReportJson["experienceLog"]["score"] = 91;
	// ReportJson["experienceLog"]["marks"] = 0;
	// ReportJson["experienceLog"]["shopId"] = NULL;
	//
	// ReportJson["history"];
	// ReportJson["questions"] = NULL;
	//
	// std::string str = to_string(ReportJson);
	// FString ReportLog(str.c_str());
	//
	// int32 action = static_cast<int32>(EActionCode::SetReportVRLog);
	// int32 dataAmount = sizeof(action) + FCString::Strlen(*ReportLog);
 // 	
	// DataSendArray.Append(reinterpret_cast<const uint8*>(&dataAmount), sizeof(dataAmount));
	// DataSendArray.Append(reinterpret_cast<const uint8*>(&action), sizeof(action));
	// DataSendArray.Append(reinterpret_cast<const uint8*>(TCHAR_TO_UTF8(*ReportLog)),FCString::Strlen(*ReportLog));
	//
	// int32 BytesSent = 0;
	// TcpSocket->Send(DataSendArray.GetData(),DataSendArray.Num(), BytesSent);
}


void UVDGameInstance::LocalDataArchive(EActionCode ECode)
{
	FString TextPath = FPaths::ProjectDir() + TEXT("Content/Log.txt");
	TextPath = FPaths::ConvertRelativePathToFull(TextPath);
	
	FDateTime Dt = FDateTime::Now();
	//UE_LOG(LogTemp, Display, TEXT("当前时间:%d年%d月%d日%d时%d分%d秒"), Dt.GetYear(), Dt.GetMonth(), Dt.GetDay(), Dt.GetHour(), Dt.GetMinute(), Dt.GetSecond());
	
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
		FFileHelper::SaveStringToFile(TextContent, *TextPath,FFileHelper::EEncodingOptions::ForceUTF8, &IFileManager::Get(), FILEWRITE_Append);
	}
	else if(ECode == EActionCode::GameStop)
	{
		AVDPawn* VdPawn = Cast<AVDPawn>(UGameplayStatics::GetPlayerPawn(this, 0));
		float TotalTime = 60 * Time;
		float UsingTime = TotalTime - ((VdPawn->UIManager->ManagerMinute) * 60.0 + VdPawn->UIManager->ManagerSecond);
		
		FString GameStop = TEXT("[游戏结束] \n");
		TextContent = TextContent.Append(GameStop);
		FFileHelper::SaveStringToFile(TextContent, *TextPath,FFileHelper::EEncodingOptions::ForceUTF8, &IFileManager::Get(), FILEWRITE_Append);
		FString GameTime = TEXT("体验时长： ");
		GameTime.Append(FString::FromInt(FMath::FloorToInt(UsingTime)));
		GameTime.Append(TEXT("秒    OK\n\n"));
		FFileHelper::SaveStringToFile(GameTime, *TextPath,FFileHelper::EEncodingOptions::ForceUTF8, &IFileManager::Get(), FILEWRITE_Append);
	}
	
}



std::wstring UVDGameInstance::stringToWstring(const std::string& str)
{
	std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
	return converter.from_bytes(str);
}

FString UVDGameInstance::WstringToFstring(std::wstring& str)
{
	FString ReString;
	TCHAR* tchr = const_cast<wchar_t*>(str.c_str());
	ReString = tchr;
	return ReString;
}



