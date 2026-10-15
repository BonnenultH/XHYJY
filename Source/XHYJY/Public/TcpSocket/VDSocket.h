// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Data/DataType.h"
#include "VDSocket.generated.h"



//三个版本：本地Offline 局域网Local 线上线下Online
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
	
	void AnalysisCustomerInfo();

	void StartReceiving();

	void ParseData(TArray<uint8>& Data);
	
	std::wstring stringToWstring(const std::string& str);

	FString WstringToFstring(std::wstring& str);

	FString StringFromBinaryArray(const TArray<uint8>& BinaryArray)
	{
		return FString(ANSI_TO_TCHAR(reinterpret_cast<const char*>(BinaryArray.GetData())));
	}
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void GameStart();

	void SendData();

	void SendReportLog();

	//判断时间是否>70%
	void FullTimeAssessment();
	//旧版中控Log
	void SendLocalReportLog();

	void GameEnd();

	void LocalDataArchive(EActionCode ECode);


public:
	bool bConnect = false;
	FSocket* _TcpSocket = nullptr;
	FString _ClientIP;
	int Time;

	FString MyEmptyData = "";
	int32 BytesRead = 0;
	uint32 size;
	uint8 ReceiveArry[40960];
	TArray<uint8> ReceiveData;
	uint8 element = 0;

	//异步接受数据
	TQueue<TArray<uint8>, EQueueMode::Mpsc> ReceivedDataQueue;
};
