// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <string>

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "VDGameInstance.generated.h"

DECLARE_DELEGATE(FMySocketConnectionDelegate);

enum class EActionCode;
/**
 * 
 */
UCLASS()
class XHYJY_API UVDGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	virtual void Init() override;

	virtual void Shutdown() override;


protected:
	UFUNCTION()
	void CreateSocket();

	void ShutDownSocket();

	UFUNCTION()
	void CustomTick();

	void AnalysisCustomerInfo();

	bool SendData(EActionCode Action, FString Data);

	void SendData(EActionCode EAction);

	void StartHeartBeat();

	void SendHeartBeat();

	void StopHeartBeat();

	bool CheckConnection();

	void ReConnectSocket();
	


	std::wstring stringToWstring(const std::string& str);

	FString WstringToFstring(std::wstring& str);

public:
	void GameStart();

	void GameEnd();

	void SendData();

	void SendReportLog();
  
	void SendLocalReportLog();
	
	void FullTimeAssessment();

	void LocalDataArchive(EActionCode ECode);

	void ProcessPendingData();

public:
	
	FMySocketConnectionDelegate FMySocketConnectionDelegateState;                                  
	FSocket* TcpSocket;
	int Time;
	bool bConnect = false;

	

protected:
	FTimerHandle TickHandle;
	float TickInternal = 0.06f;

	uint32 size;
	int32 BytesRead = 0;
	
	TArray<uint8> PendingData;
	TArray<uint8> PackageData;

	FTimerHandle HeartbeatTimerHandle;
	float HeartbeatInterval = 3.0f; // 心跳间隔（秒）
    float ReconnectInterval = 5.0f;
	int DisconnectTime = 0;
	
	FTimerHandle ReconnectSocketHandle;
	FTimerHandle ReConnectAttemp;
};
