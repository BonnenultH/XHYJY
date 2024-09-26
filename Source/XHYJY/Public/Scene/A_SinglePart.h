// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/DataType.h"
#include "GameFramework/Actor.h"
#include "A_SinglePart.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FDelegateRocketClickReturn, AA_SinglePart*)

UCLASS()
class XHYJY_API AA_SinglePart : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AA_SinglePart();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void NotifyActorOnClicked(FKey ButtonPressed) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


public:
	UPROPERTY()
	UStaticMeshComponent* RocketDispatchMesh;

	ERocketPartsType RocketPartType = ERocketPartsType::ERP_None;

	FString  RocketPartName;

	FDelegateRocketClickReturn MouseRocketClickReturn;
};
