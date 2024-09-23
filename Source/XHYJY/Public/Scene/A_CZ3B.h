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
	void OnOverlapBox1(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	

protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UBoxComponent* Box;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UBoxComponent* Box0;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UBoxComponent* Box1;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UBoxComponent* Box2;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UBoxComponent* Box3;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UBoxComponent* Box4;

};
