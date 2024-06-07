// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TPSProjectGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class TPSPROJECT_API ATPSProjectGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UStartWidget> startWidget;
	void ShowStart();

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UNextPageWidget> nextWidget;
	void ShowNext();

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UBossWidget> bossWidget;

	//void UpdateProgressBar(float Value);

	UPROPERTY(EditAnywhere)
	class UBossWidget* ProgressBarWidget;

protected:
	//virtual void BeginPlay() override;

public:

	class UStartWidget* startUI;
	class UNextPageWidget* nextUI;
	ATPSProjectGameModeBase();

};
