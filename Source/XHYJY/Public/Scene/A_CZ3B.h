// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Actor.h"
#include "A_CZ3B.generated.h"

class UBoxComponent;

UCLASS()
class XHYJY_API AA_CZ3B : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AA_CZ3B();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UFUNCTION()
	void OnOverlapBox(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	

protected:
    //逃逸塔
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UBoxComponent* EscapeTower;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UBoxComponent* Cowling;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UBoxComponent* CoreOneLevel;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UBoxComponent* CoreTwoLevels;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UBoxComponent* CoreThreeLevels;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UBoxComponent* Rollboosters;

};
