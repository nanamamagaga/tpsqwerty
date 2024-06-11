// Fill out your copyright notice in the Description page of Project Settings.


#include "FailureWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components/Button.h"
#include "TPSProjectGameModeBase.h"


void UFailureWidget::NativeConstruct()
{
	Super::NativeConstruct();

	button_Fail->OnClicked.AddDynamic(this, &UFailureWidget::Fail);

}


void UFailureWidget::Fail()
{
	ATPSProjectGameModeBase* GameMode = Cast<ATPSProjectGameModeBase>(UGameplayStatics::GetGameMode(this));
	GameMode->failUI->RemoveFromViewport();
	UGameplayStatics::OpenLevel(GetWorld(), "Map1");
	UGameplayStatics::SetGamePaused(GetWorld(), false);
	GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(false);

}

