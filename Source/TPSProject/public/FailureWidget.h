// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FailureWidget.generated.h"

/**
 * 
 */
UCLASS()
class TPSPROJECT_API UFailureWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* button_Fail;

	UFUNCTION()
	void Fail();


protected:
	virtual void NativeConstruct() override;
	
};
