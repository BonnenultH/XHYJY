// Fill out your copyright notice in the Description page of Project Settings.


#include "TcpSocket/VDSocket.h"
#include "SocketSubsystem.h"
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
	FString _ServerIp = L"192.168.101.20";
	int32 Port = 8912;
	Addr->SetIp(*_ServerIp, bIsValid);
	Addr->SetPort(Port);

	_TcpSocket = FTcpSocketBuilder(TEXT("TcpClient"))
					.AsReusable()
					.BoundToAddress(FIPv4Address::Any)
					.BoundToPort(8431)
					.WithReceiveBufferSize(2048)
					.WithSendBufferSize(2048);

	_TcpSocket->SetNonBlocking(true);
	_TcpSocket->SetMulticastLoopback(true);
	_TcpSocket->SetBroadcast(false);
	
	bConnect = _TcpSocket->Connect(*Addr);
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

// Called every frame
void AVDSocket::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if(bConnect && _TcpSocket)
	{
		uint8 DataBuffer[2048];
		int32 BytesRead = 0;
		bool Result = _TcpSocket->Recv(DataBuffer,sizeof(DataBuffer),BytesRead);
	
		if(Result)
		{
			FString MyString = FString(UTF8_TO_TCHAR(DataBuffer));
			UE_LOG(LogTemp, Log, TEXT("收到的数据：%s"), *MyString)
		}
	}
	

}

