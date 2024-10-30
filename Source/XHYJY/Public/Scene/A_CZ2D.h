// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Scene/BaseCZActor.h"
#include "A_CZ2D.generated.h"

/**
 * 
 */
UCLASS()
class XHYJY_API AA_CZ2D : public ABaseCZActor
{
	GENERATED_BODY()

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

public:
	virtual void BeginPlay() override;

	virtual void ShowAllMesh() override;


protected:
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	UBoxComponent* Cowling;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	UStaticMeshComponent* CowlingS;
	
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	UBoxComponent* CoreOneLevel;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	UStaticMeshComponent* CoreOneLevelS;
	
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	UBoxComponent* CoreTwoLevels;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	UStaticMeshComponent* CoreTwoLevelsS;
	
};
