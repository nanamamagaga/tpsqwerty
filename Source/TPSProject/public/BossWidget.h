// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BossWidget.generated.h"
/**
 * 
 */
UCLASS()
class TPSPROJECT_API UBossWidget : public UUserWidget
{
	GENERATED_BODY()
public:

	// ���α׷��� ���� ���� �����ϴ� �Լ�
	UFUNCTION(BlueprintCallable, Category = "UI")
	void SetProgressBarValue(float Value);

	UPROPERTY(meta = (BindWidget))
	class UProgressBar* ProgressBar;


	// ��� ���� ������ �����ϴ°� ������
	float MaxHp = 100;
	float CurrentHp = 70;

protected:
	virtual void NativeConstruct() override;
	
};
