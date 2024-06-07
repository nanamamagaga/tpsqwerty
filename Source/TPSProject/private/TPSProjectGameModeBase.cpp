// Copyright Epic Games, Inc. All Rights Reserved.


#include "TPSProjectGameModeBase.h"
#include "TPSProject.h"
#include "StartWidget.h"
#include "NextPageWidget.h"
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
		GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(true);
	}
}