// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SkillWidget.generated.h"

/**
 * 
 */
UCLASS()
class TPSPROJECT_API USkillWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	// ���α׷��� ���� ���� �����ϴ� �Լ�
	UFUNCTION(BlueprintCallable, Category = "UI")
	void SetProgressBarValue_Q(float Value);
	UFUNCTION(BlueprintCallable, Category = "UI")
	void SetProgressBarValue_W(float Value);
	UFUNCTION(BlueprintCallable, Category = "UI")
	void SetProgressBarValue_E(float Value);
	UFUNCTION(BlueprintCallable, Category = "UI")
	void SetProgressBarValue_R(float Value);
	UFUNCTION(BlueprintCallable, Category = "UI")
	void SetProgressBarValue_I1(float Value);
	UFUNCTION(BlueprintCallable, Category = "UI")
	void SetProgressBarValue_I2(float Value);

	UPROPERTY(meta = (BindWidget))
	class UProgressBar* Q_ProgressBar;
	UPROPERTY(meta = (BindWidget))
	class UProgressBar* W_ProgressBar;
	UPROPERTY(meta = (BindWidget))
	class UProgressBar* E_ProgressBar;
	UPROPERTY(meta = (BindWidget))
	class UProgressBar* R_ProgressBar;
	UPROPERTY(meta = (BindWidget))
	class UProgressBar* I1_ProgressBar;
	UPROPERTY(meta = (BindWidget))
	class UProgressBar* I2_ProgressBar;


	// ��� ���� ������ �����ϴ°� ������
	float Max = 100;
	float Current_Q = 70;
	float Current_W = 60;
	float Current_E = 50;
	float Current_R = 40;
	float Current_I1 = 70;
	float Current_I2 = 60;

protected:
	virtual void NativeConstruct() override;

	
};