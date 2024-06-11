// Copyright Epic Games, Inc. All Rights Reserved.


#include "TPSProjectGameModeBase.h"
#include "TPSProject.h"
#include "StartWidget.h"
#include "NextPageWidget.h"
#include "BossWidget.h"
#include "SkillWidget.h"
#include "SuccessWidget.h"
#include "FailureWidget.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"



ATPSProjectGameModeBase::ATPSProjectGameModeBase()
{
	PRINT_LOG(TEXT("My Log : %s"), TEXT("TPS project!!"));
}

void ATPSProjectGameModeBase::ShowStart()
{
	if (startWidget != nullptr)
	{
		startUI = CreateWidget<UStartWidget>(GetWorld(), startWidget);
	}
	if (startUI != nullptr)
	{
		startUI->AddToViewport();
		UGameplayStatics::SetGamePaused(GetWorld(), true);
		GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(true);
	}
}


void ATPSProjectGameModeBase::ShowNext()
{
	if (nextWidget != nullptr)
	{
		nextUI = CreateWidget<UNextPageWidget>(GetWorld(), nextWidget);
	}
	if (nextUI != nullptr)
	{
		nextUI->AddToViewport();
		UGameplayStatics::SetGamePaused(GetWorld(), true);
		GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(true);
	}
}


void ATPSProjectGameModeBase::ShowBoss()
{
	if (bossWidget != nullptr)
	{
		bossUI = CreateWidget<UBossWidget>(GetWorld(), bossWidget);
	}
	if (bossUI != nullptr)
	{
		bossUI->AddToViewport();
	}
}

void ATPSProjectGameModeBase::ShowSkill()
{
	if (skillWidget != nullptr)
	{
		skillUI = CreateWidget<USkillWidget>(GetWorld(), skillWidget);
	}
	if (skillUI != nullptr)
	{
		skillUI->AddToViewport();
	}
}


void ATPSProjectGameModeBase::ShowSuccess()
{
	if (successWidget != nullptr)
	{
		successUI = CreateWidget<USuccessWidget>(GetWorld(), successWidget);
	}
	if (successUI != nullptr)
	{
		UGameplayStatics::SetGamePaused(GetWorld(), true);
		GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(true);
		successUI->AddToViewport();
	}
}

void ATPSProjectGameModeBase::ShowFail()
{
	if (failWidget != nullptr)
	{
		failUI = CreateWidget<UFailureWidget>(GetWorld(), failWidget);
	}
	if (failUI != nullptr)
	{
		failUI->AddToViewport();
		UGameplayStatics::SetGamePaused(GetWorld(), true);
		GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(true);
	}
}