// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/DataType.h"
#include "GameFramework/Pawn.h"
#include "InputActionValue.h"
#include "VDPawn.generated.h"

class UInputMappingContext;
class UInputAction;

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

	void Move(const FInputActionValue& Value);


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UInputMappingContext* DefaultMappingContext;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UInputAction* MoveAction;

public:
	UPROPERTY()
	class AResourceManager* ResourceManager;
	UPROPERTY()
	class AUIManager* UIManager;
	UPROPERTY()
	class ASceneManager* SceneManager;

	S_UserInfo UserInfoData;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	class UCameraComponent* Camera;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	class USpringArmComponent* MySpringArm;

	bool bMove = false;
};
