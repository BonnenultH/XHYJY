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
AVDSocket::AVDSocket()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AVDSocket::BeginPlay()
{
	Super::BeginPlay();

//	CreateSocket();
	
}

void AVDSocket::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
//	CloseSocket();
}

void AVDSocket::CreateSocket()
{
	TSharedPtr<FInternetAddr> Addr = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();
	bool bIsValid = false;
	FString _ServerIp = "192.168.50.99";
	int32 Port = 9527;
	Addr->SetIp(*_ServerIp, bIsValid);
	Addr->SetPort(Port);

	_TcpSocket = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateSocket(NAME_Stream, "TCPClient", false);
	
	bConnect = _TcpSocket->Connect(*Addr);

	if(bConnect)
	{
		UE_LOG(LogTemp, Log, TEXT("链接成功"));

		SendData(EActionCode::ClintIP, _ClientIP);
		
		
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
	_TcpSocket->Send(DataArray.GetData(),DataArray.Num(), BytesSent);
}


// Called every frame
void AVDSocket::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
/*	if(_TcpSocket->HasPendingData(size))
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
*/	
	
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
	AVDPawn* VdPawn = nullptr;
	VdPawn = Cast<AVDPawn>(UGameplayStatics::GetPlayerPawn(this, 0));
	if(VdPawn)
	{
	UWHomePage* HomePage = Cast<UWHomePage>(VdPawn->UIManager->WidgetMap[EWidgetType::EWT_HomePage]);
	HomePage->GameStart();
	}
	UE_LOG(LogTemp,Log,TEXT("  GameStart   "));
}

void AVDSocket::GameEnd()
{
	UE_LOG(LogTemp,Log,TEXT("  GameEnd   "));
}


// void AVDSocket::SendReportLog()
// {
// 	TArray<uint8> DataSendArray;
// 	nlohmann::json ReportJson;
// 	CraftDataVO MyCraft;
// 	int32 Craftaction = static_cast<int32>(ECraft::DongFangHong);
// 	ReportJson["craftModel"] = Craftaction;
// 	ReportJson["Grade"] = 50;
// 	std::string str = to_string(ReportJson);
//
// 	int32 action = static_cast<int32>(EActionCode::SetReportVRLog);
// 	int32 dataAmount = sizeof(action) + sizeof(str.c_str());
// 	
// 	DataSendArray.Append(reinterpret_cast<const uint8*>(&dataAmount), sizeof(dataAmount));
// 	DataSendArray.Append(reinterpret_cast<const uint8*>(&action), sizeof(action));
// 	DataSendArray.Append(reinterpret_cast<const uint8*>(TCHAR_TO_UTF8(&str)),sizeof(str));
//
// 	int32 BytesSent = 0;
// 	_TcpSocket->Send(DataSendArray.GetData(),DataSendArray.Num(), BytesSent);
// }

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
