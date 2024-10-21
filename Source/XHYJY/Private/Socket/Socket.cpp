// Fill out your copyright notice in the Description page of Project Settings.


#include "Socket/Socket.h"

#include "Common/TcpSocketBuilder.h"

// Sets default values
ASocket::ASocket()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASocket::BeginPlay()
{
	Super::BeginPlay();
	CreateSocket();
	
}

void ASocket::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	StopSocket();
}

void ASocket::CreateSocket()
{
	TSharedPtr<FInternetAddr> Addr = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();
	bool bIsValid;
	FString _LocalIP("192.168.101.20");
	int32 _LocalPort = 8912;
	Addr->SetIp(*_LocalIP,bIsValid);
	Addr->SetPort(_LocalPort);
	
	if(!bIsValid)
	{
		UE_LOG(LogTemp, Log, TEXT("Ip设置失败！"))
		return;
	}
	
	_Socket = FTcpSocketBuilder(TEXT("DJMSocket"))
		.AsReusable()
		.BoundToAddress(FIPv4Address::Any)
		.BoundToPort(8430)
		.WithSendBufferSize(2048)
		.WithReceiveBufferSize(2048);

	_Socket->SetNonBlocking(true);
	_Socket->SetMulticastLoopback(true);
	_Socket->SetBroadcast(false);

	bConnect = _Socket->Connect(*Addr);
}

void ASocket::StopSocket()
{
	if(_Socket)
	{
		_Socket->Close();
		ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->DestroySocket(_Socket);
		FPlatformProcess::Sleep(0.5f);
	}
}

// Called every frame
void ASocket::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if(bConnect && _Socket)
	{
		uint8 DataBuffer[2048];
		int32 BytesRead = 0;
		bool Result = _Socket->Recv(DataBuffer,sizeof(DataBuffer),BytesRead);
		
		if(Result)
		{
			FString MyString = FString(UTF8_TO_TCHAR(DataBuffer));
			UE_LOG(LogTemp, Log, TEXT("收到的数据：%s"), *MyString)
		}
	}
}

