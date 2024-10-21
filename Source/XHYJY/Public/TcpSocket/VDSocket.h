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

	void CreateSocket();

	void CloseSocket();
	
	void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	bool bConnect = false;


public:
	FSocket* _TcpSocket; 
};
