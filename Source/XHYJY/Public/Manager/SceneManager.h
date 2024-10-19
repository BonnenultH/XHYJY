// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "Components/TimelineComponent.h"
#include "Manager/BaseManager.h"
#include "Scene/BaseCZActor.h"
#include "SceneManager.generated.h"

class AA_SinglePart;

/**
 * 
 */
UCLASS()
class XHYJY_API ASceneManager : public ABaseManager
{
	GENERATED_BODY()

protected:
	void SingleMeshClick(AA_SinglePart* SinglePart);

	void CheckClickMesh();

	void DelayAttach();

	void DelaySelect();

	void DestroySingle();

public:
	
	void InitManager() override;

	void InitSingleMesh();

	void InitTargetRocket();

	void SwitchViewByHoist();

	void SwitchViewByFront();

	void BindHoistUIDelegate();

	void PlayBGMSound();
	void PlayFactorySound();
	void PlayHoistBG();


	void SetSelectable(bool bSelect)
	{
		bSelectable = bSelect;
	}
	
	bool GetSelectable()
	{
		return bSelectable;
	}
	
	void AssemblySuccess();

	void SetbStartUIBGM()
	{
		bStartUIBGM = false;
	}

	void StartbHoistBGM()
	{
		bHoist = true;
	}
	void StopbHoistBGM()
	{
		bHoist = false;
	}
	

protected:
	FVector SinglePartLocation = FVector(-46243.709164,-37700.620589,409.999977);
	FDiagramUITable* UIDiagram;
	int32 ClickedNum = 0;
	UPROPERTY()
	AA_SinglePart* CurSingleMesh;

	AA_SinglePart* TempMesh;
	bool bSelectable = false;
	UPROPERTY()

	ABaseCZActor* TargetRocket;

	TMap<ERocketType, UClass*> TargetRocketBPMap;

	bool bStartUIBGM = true;
	bool bHoist = false;
	UAudioComponent* AudioComponent;


public:
	UPROPERTY()
	AActor* HoistCamera;

	UPROPERTY()
	AActor* FrontCamera;
	
	UPROPERTY()
	TArray<AA_SinglePart*> SingleArray;

	
};
