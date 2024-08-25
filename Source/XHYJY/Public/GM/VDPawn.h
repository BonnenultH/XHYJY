// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "VDPawn.generated.h"

UCLASS()
class XHYJY_API AVDPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AVDPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void CreateManagers();
	void InitManagers();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	UPROPERTY()
	class AResourceManager* ResourceManager;

	UPROPERTY()
	class AUIManager* UIManager;
	
};
