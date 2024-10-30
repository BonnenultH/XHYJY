// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Scene/BaseCZActor.h"
#include "A_CZ3A.generated.h"

/**
 * 
 */
UCLASS()
class XHYJY_API AA_CZ3A : public ABaseCZActor
{
	GENERATED_BODY()


protected:

	virtual void BeginPlay() override;
	
	UFUNCTION()
	void OnOverlapCOneSBox(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
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
	
};
