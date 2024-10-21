// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
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

	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	bool bConnect = false;
	FSocket* _TcpSocket; 
};
