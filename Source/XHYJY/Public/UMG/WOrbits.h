// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UMG/BaseWidget.h"
#include "WOrbits.generated.h"

/**
 * 
 */
UCLASS()
class XHYJY_API UWOrbits : public UBaseWidget
{
	GENERATED_BODY()

protected:
	UFUNCTION()
	void LEOClicked();
	UFUNCTION()
	void MEOClicked();
	UFUNCTION()
	void SSOClicked();
	UFUNCTION()
	void GEOClicked();
	UFUNCTION()
	void GTOClicked();
	UFUNCTION()
	void IGSOClicked();
	UFUNCTION()
	void TLIClicked();
	UFUNCTION()
	void TMIClicked();

	UFUNCTION()
	void CreateRocketSelect();

	void InitOrbitInfo();

	void OrbitInfoFunc(EOrbit Orbit);

	UFUNCTION()
	void RightAnswer();

	UFUNCTION()
	void WrongAnswer();

public:
	virtual void InitWidget() override;
	
public:
	FHTQOrbit CurSelectedOrbit;
	
	UPROPERTY(meta=(BindWidget))
	UBaseWidget* WBP_PersonTitle;
	UPROPERTY(meta=(BindWidget))
	UBaseWidget* WBP_Timing;

	UPROPERTY(meta=(BindWidget))
	UOverlay* Left_Orbit;
	UPROPERTY(meta=(BindWidget))
	UTextBlock* OrbitName;
	UPROPERTY(meta=(BindWidget))
	UTextBlock* OrbitInfo;

	UPROPERTY(meta=(BindWidget))
	UButton* LEO;
	UPROPERTY(meta=(BindWidget))
	UButton* MEO;
	UPROPERTY(meta=(BindWidget))
	UButton* SSO;
	UPROPERTY(meta=(BindWidget))
	UButton* GEO;
	UPROPERTY(meta=(BindWidget))
	UButton* GTO;
	UPROPERTY(meta=(BindWidget))
	UButton* IGSO;
	UPROPERTY(meta=(BindWidget))
	UButton* TLI;
	UPROPERTY(meta=(BindWidget))
	UButton* TMI;

	UPROPERTY(Transient, meta=(BindWidgetAnim))
	UWidgetAnimation* Orbit_RightPop;

	UPROPERTY(Transient, meta=(BindWidgetAnim))
	UWidgetAnimation* Orbit_WrongPop;
		
	UPROPERTY(meta=(BindWidget))
	UButton* Button_Ok;
	UPROPERTY(meta=(BindWidget))
	UButton* Button_RightOk;
	UPROPERTY(meta=(BindWidget))
	UButton* Button_WrongAgain;

	TMap<EOrbit, FHTQOrbit> OrbitMap;
	
};
