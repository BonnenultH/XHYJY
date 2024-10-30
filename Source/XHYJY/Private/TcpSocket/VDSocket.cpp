// Fill out your copyright notice in the Description page of Project Settings.


#include "TcpSocket/VDSocket.h"
#include <codecvt>
#include "SocketSubsystem.h"
#include "Data/DataType.h"
#include "Common/TcpSocketBuilder.h"
#include "ThirdParty/json-develop/single_include/nlohmann/json.hpp"

// Sets default values
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
	TSharedPtr<FInternetAddr> Addr = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();
	bool bIsValid = false;
	FString _ServerIp = "192.168.50.238";
	int32 Port = 9527;
	Addr->SetIp(*_ServerIp, bIsValid);
	Addr->SetPort(Port);

	_TcpSocket = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateSocket(NAME_Stream, "TCPClient", false);
	
	bConnect = _TcpSocket->Connect(*Addr);

	if(bConnect)
	{
		UE_LOG(LogTemp, Log, TEXT("链接成功"));

		SendData(EActionCode::ClintIP, _ClientIP);

		
		// nlohmann::json ReportJson;
		// CraftDataVO MyCraft;
		// MyCraft.craftModel = L"东方红一号";
		// MyCraft.grade = 80;
		// ReportJson["craft"]["craftModel"] = MyCraft.craftModel;
		// ReportJson["craft"]["grade"] = MyCraft.grade;
		// std::string ReportData = to_string(ReportJson);
		//
		// SendData(EActionCode::SetReportVRLog, ReportData.c_str());
		
		// FString JsonString;
		// FJsonObjectConverter::UStructToJsonObjectString(CraftDataVO::StaticStruct(),&MyCraft,JsonString,0,0);
		
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
	MyCraft.craftModel = L"东方红一号";
	MyCraft.grade = 80;
	ReportJson["craft"]["craftModel"] = MyCraft.craftModel;
	ReportJson["craft"]["grade"] = MyCraft.grade;
	std::string ReportData = to_string(ReportJson);
	
	int32 action = static_cast<int32>(EActionCode::SetReportVRLog);
	int32 dataAmount = sizeof(action) + sizeof(ReportData);
	DataArray.Append(reinterpret_cast<const uint8*>(&dataAmount), sizeof(dataAmount));
	DataArray.Append(reinterpret_cast<const uint8*>(&action), sizeof(action));
	DataArray.Append(reinterpret_cast<const uint8*>(TCHAR_TO_UTF8(&ReportData)), sizeof(ReportData));
	
	int32 BytesSent = 0;
	_TcpSocket->Send(DataArray.GetData(),DataArray.Num(), BytesSent);
}


// Called every frame
void AVDSocket::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if(_TcpSocket->HasPendingData(size))
	{
		BytesRead = 0;
		_TcpSocket->Recv(ReceiveArry,sizeof(ReceiveArry),BytesRead);
		uint8 SubArray[4];
		for(int i = 4; i < 8; ++i)
		{
			SubArray[i - 4] = ReceiveArry[i];
		}
		
		//TArray<uint8> SubArray;
		SubArray[0] = ReceiveArry[4];
		
		//SubArray.Append(ReceiveArry + 4, 4);
		
		int32 Value = *(reinterpret_cast<int32*>(SubArray));
		
		//int32 Value = *(reinterpret_cast<int32*>(SubArray.GetData()));
		
		UE_LOG(LogTemp, Log, TEXT("MY Value:%d"),Value)
		EActionCode actionCode  = (EActionCode)Value;
		
		if (actionCode == EActionCode::GetCustomerInfo)
		{
			UE_LOG(LogTemp, Log, TEXT("GET CUSTOMERINFO"))
			AnalysisCustomerInfo();
		}
		else if(actionCode == EActionCode::GameStart)
		{
			GameStart();
			UE_LOG(LogTemp, Log, TEXT("GAME START!!"))
		}
		else if(actionCode == EActionCode::GameStop)
		{
			GameEnd();
			UE_LOG(LogTemp, Log, TEXT("GAME END!!"))
		}
	}
	
}

void AVDSocket::AnalysisCustomerInfo()
{
	if(BytesRead != 0)
	{
		uint8 TempArry[5000];
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
		nlohmann::json JsonStr = nlohmann::json::parse(str);

		bool Playerresult = JsonStr.contains("player");
		bool Historyresult = JsonStr.contains("history");
		
		if(Playerresult && Historyresult)
		{
			nlohmann::json player = JsonStr["player"];

			LONG playerId = player["playerId"].get<LONG>();
				
			std::string nickname =player["nickname"].get<std::string>();
			auto Mynickname = stringToWstring(nickname);
				
			std::string accomplishment = player["accomplishment"].get<std::string>();
			auto Myaccomplishment = stringToWstring(accomplishment);
			std::string sex = player["sex"].get<std::string>();
			auto Mysex = stringToWstring(sex);
			if(Mysex == L"男")
			{
				UE_LOG(LogTemp, Log, TEXT("TRUEEEEE !! BOYYYYY"))
			}
			int32 score = player["score"].get<int32>();
			int32 craftNumber = player["craftNumber"].get<int32>();
				
			TArray<CraftDataVO> TestArry;
			nlohmann::json history = JsonStr["history"];
			for (nlohmann::json jsonobj : history)
			{
				CraftDataVO Tempobj;
					
				Tempobj.craftModel = jsonobj["craftModel"].get<std::wstring>();
				//auto MycraftModel = stringToWstring(Tempobj.craftModel);
				Tempobj.finishTime = jsonobj["finishTime"].get<std::string>();
				Tempobj.grade      = jsonobj["grade"].get<int32>();
				
				TestArry.Add(Tempobj);
			}
			
		}
	}
}

void AVDSocket::GameStart()
{
	UE_LOG(LogTemp,Log,TEXT("  GameStart   "));
}

void AVDSocket::GameEnd()
{
	UE_LOG(LogTemp,Log,TEXT("  GameEnd   "));
}


void AVDSocket::SendReportLog()
{
	TArray<uint8> DataSendArray;
	nlohmann::json ReportJson;
	CraftDataVO MyCraft;
	int32 Craftaction = static_cast<int32>(ECraft::DongFangHong);
	ReportJson["craftModel"] = Craftaction;
	ReportJson["Grade"] = 50;
	std::string str = to_string(ReportJson);

	int32 action = static_cast<int32>(EActionCode::SetReportVRLog);
	int32 dataAmount = sizeof(action) + sizeof(str.c_str());
	
	DataSendArray.Append(reinterpret_cast<const uint8*>(&dataAmount), sizeof(dataAmount));
	DataSendArray.Append(reinterpret_cast<const uint8*>(&action), sizeof(action));
	DataSendArray.Append(reinterpret_cast<const uint8*>(TCHAR_TO_UTF8(&str)),sizeof(str));

	int32 BytesSent = 0;
	_TcpSocket->Send(DataSendArray.GetData(),DataSendArray.Num(), BytesSent);
}

std::wstring AVDSocket::stringToWstring(const std::string& str)
{
	std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
	return converter.from_bytes(str);
}
