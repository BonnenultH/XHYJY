// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Manager/BaseManager.h"
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

public:
	void InitManager() override;

	void InitSingleMesh();

	void SwitchViewByHoist();

	void BindHoistUIDelegate();
protected:
	FVector SinglePartLocation = FVector(-46243.709164,-37700.620589,409.999977);
	FDiagramUITable* UIDiagram;
	int32 ClickedNum = 0;
	UPROPERTY()
	AA_SinglePart* CurSingleMesh;
	
public:
	UPROPERTY()
	AActor* HoistCamera;
	UPROPERTY()
	TArray<AA_SinglePart*> SingleArray;
};
