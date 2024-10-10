// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCZActor.h"
#include "A_CZ3C.generated.h"

class UBoxComponent;

UCLASS()
class XHYJY_API AA_CZ3C : public ABaseCZActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AA_CZ3C();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnOverlapCOneSBox(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapRBBox(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapCowBox(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapCThreeSBox(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapCTwoSBox(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void ShowAllMesh() override;

	
protected:
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	UBoxComponent* RB1_BoxC;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	UStaticMeshComponent* RollBooster1C;
	
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	UBoxComponent* COneS_BoxC;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	UStaticMeshComponent* CoreOneStageC;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	UBoxComponent* Cow_BoxC;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	UStaticMeshComponent* CowlingC;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	UBoxComponent* CThreeS_BoxC;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	UStaticMeshComponent* CoreThreeStageC;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	UBoxComponent* RB2_BoxC;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	UStaticMeshComponent* RollBooster2C;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	UBoxComponent* CTwoS_BoxC;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	UStaticMeshComponent* CoreTwoStageC;

};

