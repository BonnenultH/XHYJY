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

void AVDSocket::CreateSocket()
{
	TSharedPtr<FInternetAddr> _Socket = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();
	bool bIsValid = false;
	FString _ServerIp = L"192.168.15.17";
	int32 Port = 8080;
	_Socket->SetIp(*_ServerIp, bIsValid);
	_Socket->SetPort(Port);
	
	_TcpSocket = FTcpSocketBuilder(TEXT("TcpClient"))
					.AsBlocking()
					.AsReusable()
					.WithReceiveBufferSize(2048)
					.WithSendBufferSize(2048);
	
		
	_TcpSocket->SetBroadcast(false);
	bConnect = _TcpSocket->Connect(*_Socket);
}

void AVDSocket::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	CloseSocket();
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

	if(bConnect)
	{
		UE_LOG(LogTemp, Log, TEXT("连接成功"))
	}
	

}

