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
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	UBoxComponent* EscapeTower;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	UBoxComponent* Cowling;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	UBoxComponent* CoreOneLevel;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	UBoxComponent* CoreTwoLevels;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	UBoxComponent* CoreThreeLevels;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	UBoxComponent* Rollboosters;

};
