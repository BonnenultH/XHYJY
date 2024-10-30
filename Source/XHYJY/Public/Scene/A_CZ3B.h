// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCZActor.h"
#include "GameFramework/Actor.h"
#include "A_CZ3B.generated.h"

class UBoxComponent;

UCLASS()
class XHYJY_API AA_CZ3B : public ABaseCZActor
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
	void OnOverlapCowlingBox(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapCoreOneLevelBox(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapCoreTwoLevelsBox(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UFUNCTION()
	void OnOverlapCoreThreeLevelsBox(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapRollboostersBox(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:
	virtual void ShowAllMesh() override;
	
protected:
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	UBoxComponent* Cowling;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	UStaticMeshComponent* CowlingC;
	
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	UBoxComponent* CoreOneLevel;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	UStaticMeshComponent* CoreOneLevelC;
	
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	UBoxComponent* CoreTwoLevels;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	UStaticMeshComponent* CoreTwoLevelsC;
	
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	UBoxComponent* CoreThreeLevels;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	UStaticMeshComponent* CoreThreeLevelsC;
	
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	UBoxComponent* Rollboosters;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	UStaticMeshComponent* RollboostersC;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	UBoxComponent* Rollboosters2;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	UStaticMeshComponent* RollboostersC2;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	UBoxComponent* Rollboosters3;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	UStaticMeshComponent* RollboostersC3;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	UBoxComponent* Rollboosters4;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	UStaticMeshComponent* RollboostersC4;

};
