// Fill out your copyright notice in the Description page of Project Settings.


#include "NextPageWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components/Button.h"
#include "TPSProjectGameModeBase.h"


void UNextPageWidget::NativeConstruct()
{
	Super::NativeConstruct();

	button_Next->OnClicked.AddDynamic(this, &UNextPageWidget::Next);

}


void UNextPageWidget::Next()
{
	ATPSProjectGameModeBase* GameMode = Cast<ATPSProjectGameModeBase>(UGameplayStatics::GetGameMode(this));
	GameMode->nextUI->RemoveFromViewport();
	UGameplayStatics::OpenLevel(GetWorld(), "Map2");
	UGameplayStatics::SetGamePaused(GetWorld(), false);
	GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(false);

}
