// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Sockets.h"
#include "Networking.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Socket.generated.h"

UCLASS()
class XHYJY_API ASocket : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASocket();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	void CreateSocket();

	void StopSocket();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	bool bConnect = false;
	FSocket* _Socket;
};
