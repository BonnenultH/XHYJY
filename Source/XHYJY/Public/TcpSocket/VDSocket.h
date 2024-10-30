// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Data/DataType.h"
#include "VDSocket.generated.h"



UCLASS()
class XHYJY_API AVDSocket : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AVDSocket();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
	void CreateSocket();

	void CloseSocket();

	bool SendData(EActionCode Action, FString Data);

	void SendData();

	void AnalysisCustomerInfo();

	void SendReportLog();
	
	std::wstring stringToWstring(const std::string& str);

	FString StringFromBinaryArray(const TArray<uint8>& BinaryArray)
	{
		return FString(ANSI_TO_TCHAR(reinterpret_cast<const char*>(BinaryArray.GetData())));
	}
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void GameStart();

	void GameEnd();

public:
	bool bConnect = false;
	FSocket* _TcpSocket;
	FString _ClientIP = L"192.168.50.229";

	FString MyEmptyData = "";
	int32 BytesRead = 0;
	uint32 size;
	uint8 ReceiveArry[4096];
	TArray<uint8> ReceiveData;
	uint8 element = 0;
};
