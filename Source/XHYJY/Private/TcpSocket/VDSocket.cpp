// Fill out your copyright notice in the Description page of Project Settings.


#include "TcpSocket/VDSocket.h"
#include "SocketSubsystem.h"
#include "Data/DataType.h"
#include "Common/TcpSocketBuilder.h"

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
	FString _ServerIp = L"192.168.15.16";
	int32 Port = 9527;
	Addr->SetIp(*_ServerIp, bIsValid);
	Addr->SetPort(Port);

	_TcpSocket = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateSocket(NAME_Stream, "TCPClient", false);

	// _TcpSocket->SetNonBlocking(true);
	// _TcpSocket->SetMulticastLoopback(true);
	// _TcpSocket->SetBroadcast(false);
	
	bConnect = _TcpSocket->Connect(*Addr);

	if(bConnect)
	{
		UE_LOG(LogTemp, Log, TEXT("链接成功"));

		SendData(EActionCode::ClintIP, _ClientIP);
		SendData(EActionCode::GetCustomerInfo, MyData);
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
	
	// DataArray.Add(reinterpret_cast<const uint8>(&dataAmount));
	// DataArray.Add(reinterpret_cast<const uint8>(&action));
	// DataArray.Add(reinterpret_cast<const uint8>(TCHAR_TO_UTF8(*Data)));

	DataArray.Append(reinterpret_cast<const uint8*>(&dataAmount), sizeof(dataAmount));
	DataArray.Append(reinterpret_cast<const uint8*>(&action), sizeof(action));
	DataArray.Append(reinterpret_cast<const uint8*>(TCHAR_TO_UTF8(*Data)), FCString::Strlen(*Data));
	
	int32 BytesSent = 0;
	_TcpSocket->Send(DataArray.GetData(), DataArray.Num(), BytesSent);
	
	return true;
}

void AVDSocket::ReceiveSocket()
{
	if (!_TcpSocket || !bConnect) return;
	if (ReceiveData.Num() <= 0)	return;
	
	// 获取第5个到第8个字节的子数组   
	 TArray<uint8> Sub58Array;
	
	 Sub58Array.Append(ReceiveData.GetData(), 4);
	
	int32 Value = *(reinterpret_cast<int32*>(Sub58Array.GetData()));
	EActionCode actionCode  = (EActionCode)Value;

	
	if(actionCode == EActionCode::GameStart)
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

// Called every frame
void AVDSocket::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	// if(bConnect && _TcpSocket)
	// {
	// 	uint8 DataBuffer[2048];
	// 	int32 BytesRead = 0;
	// 	bool Result = _TcpSocket->Recv(DataBuffer,sizeof(DataBuffer),BytesRead);
	//
	// 	if(Result)
	// 	{
	// 		FString MyString = FString(UTF8_TO_TCHAR(DataBuffer));
	// 		UE_LOG(LogTemp, Log, TEXT("收到的数据：%s"), *MyString)
	// 	}
	// }
	
	if(_TcpSocket->HasPendingData(size))
	{
		ReceiveData.Init(element,FMath::Min(size,65507u));
		FString ReceivedUE4String = "";
		int32 read = 0;
		_TcpSocket->Recv(ReceiveData.GetData(),ReceiveData.Num(),read);
		ReceivedUE4String = StringFromBinaryArray(ReceiveData);
		UE_LOG(LogTemp, Log, TEXT("收到的数据：%s"), *ReceivedUE4String)
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
