// Fill out your copyright notice in the Description page of Project Settings.


#include "UMG/WComprehensiveTest.h"

void UWComprehensiveTest::InitWidget()
{
	Super::InitWidget();
	ErrorNums = 3;
		
	WBP_PersonTitle->InitWidget();
	WBP_Timing->InitWidget();
	UIManager->OnUpdateProgress.Broadcast();
	WBP_States->InitWidget();

	Button_Troubles->OnClicked.AddDynamic(this, &UWComprehensiveTest::InitQuestions);
	Button_A->OnClicked.AddDynamic(this, &UWComprehensiveTest::ClickedButtonA);
	Button_B->OnClicked.AddDynamic(this, &UWComprehensiveTest::ClickedButtonB);
	Button_C->OnClicked.AddDynamic(this, &UWComprehensiveTest::ClickedButtonC);
	Button_D->OnClicked.AddDynamic(this, &UWComprehensiveTest::ClickedButtonD);
	
	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle,this, &UWComprehensiveTest::InitTroubles,2.0f,false);
	
}

void UWComprehensiveTest::InitTroubles()
{
	Border_BG->SetBrushFromTexture(ResourceManager->TestWarning);
	HorizontalBox_Troubles->SetVisibility(ESlateVisibility::Collapsed);
	Image_Scan->SetVisibility(ESlateVisibility::Collapsed);
	Button_Troubles->SetVisibility(ESlateVisibility::Visible);
}

void UWComprehensiveTest::InitQuestions()
{
	if(Button_Troubles->GetVisibility() != ESlateVisibility::Collapsed)
	{
		Button_Troubles->SetVisibility(ESlateVisibility::Collapsed);
	}
	TextBlock_TestTitle->SetText(FText::FromString(UIManager->TestsAry[QuesNum].TestTitle));
	TextBlock_A->SetText(FText::FromString(UIManager->TestsAry[QuesNum].AnswerA));
	TextBlock_B->SetText(FText::FromString(UIManager->TestsAry[QuesNum].AnswerB));
	TextBlock_C->SetText(FText::FromString(UIManager->TestsAry[QuesNum].AnswerC));
	TextBlock_D->SetText(FText::FromString(UIManager->TestsAry[QuesNum].AnswerD));
	PlayAnimation(QuestionShow);
}

void UWComprehensiveTest::ClickedButtonA()
{
	CheckSelectRight(TextBlock_A,EAnswer::EA_A);
}

void UWComprehensiveTest::ClickedButtonB()
{
	CheckSelectRight(TextBlock_B,EAnswer::EA_B);
}

void UWComprehensiveTest::ClickedButtonC()
{
	CheckSelectRight(TextBlock_C,EAnswer::EA_C);
}

void UWComprehensiveTest::ClickedButtonD()
{
	CheckSelectRight(TextBlock_D,EAnswer::EA_D);
}

void UWComprehensiveTest::CheckSelectRight(UTextBlock* CurButton, EAnswer ButtonType)
{
	if(!bButtonAble || !CurButton)
		return;
	
	if(UIManager->TestsAry[QuesNum].RightAnswer == ButtonType)
	{
		CurButton->SetColorAndOpacity(FSlateColor(FLinearColor::Yellow));
		FTimerHandle DelayShowNext;
		GetWorld()->GetTimerManager().SetTimer(DelayShowNext,this, &UWComprehensiveTest::SelectRight,0.5f,false);
	}
	else
	{
		CurButton->SetColorAndOpacity(FSlateColor(FLinearColor::Red));
		FTimerHandle DelayWrong;
		GetWorld()->GetTimerManager().SetTimer(DelayWrong,this, &UWComprehensiveTest::SelectWrong, 0.5f, false);
	}
	
	bButtonAble = false;
}

void UWComprehensiveTest::SelectRight()
{
	PlayAnimationReverse(QuestionShow);
	ButtonToWhite();
	FTimerHandle DelayShowNext;
	GetWorld()->GetTimerManager().SetTimer(DelayShowNext,this, &UWComprehensiveTest::ShowNextQue,0.75f,false);
}

void UWComprehensiveTest::SelectWrong()
{
	if(ErrorNums != 0)
	{
		UIManager->MinusGrade(10);
		CountErrorNums();
	}
	ButtonToWhite();
}

void UWComprehensiveTest::ButtonToWhite()
{
	TextBlock_A->SetColorAndOpacity(FSlateColor(FLinearColor::White));
	TextBlock_B->SetColorAndOpacity(FSlateColor(FLinearColor::White));
	TextBlock_C->SetColorAndOpacity(FSlateColor(FLinearColor::White));
	TextBlock_D->SetColorAndOpacity(FSlateColor(FLinearColor::White));
	bButtonAble = true;
}


void UWComprehensiveTest::ShowNextQue()
{
	if(QuesNum >= 2)
	{
		Border_BG->SetBrushFromTexture(ResourceManager->TestBG);
		
		if(ResourceManager->EndingLevelSequencePlayer)
		{
			ResourceManager->EndingLevelSequencePlayer->Play();
			ResourceManager->EndingLevelSequencePlayer->OnFinished.AddDynamic(this, &UWComprehensiveTest::CreateBook);
		}
		
		return;
	}
	
	QuesNum++;
	InitQuestions();
}

void UWComprehensiveTest::CreateBook()
{
	UIManager->CreateVDWidget(EWidgetType::EWT_BookLaunch);
}
