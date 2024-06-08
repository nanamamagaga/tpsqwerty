// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components/WidgetComponent.h"
#include "Components/ProgressBar.h"

void USkillWidget::NativeConstruct()
{
    Super::NativeConstruct();

    if (Q_ProgressBar)
    {
        Q_ProgressBar->SetPercent(Current_Q / Max);
    }
    if (W_ProgressBar)
    {
        W_ProgressBar->SetPercent(Current_W / Max);
    }
    if (E_ProgressBar)
    {
        E_ProgressBar->SetPercent(Current_E / Max);
    }
    if (R_ProgressBar)
    {
        R_ProgressBar->SetPercent(Current_R / Max);
    }
    if (I1_ProgressBar)
    {
        I1_ProgressBar->SetPercent(Current_I1 / Max);
    }
    if (I2_ProgressBar)
    {
        I2_ProgressBar->SetPercent(Current_I2 / Max);
    }
}


void USkillWidget::SetProgressBarValue_Q(float Value)
{
    if (Q_ProgressBar)
    {
        Q_ProgressBar->SetPercent(Current_Q / Max);
    }
}

void USkillWidget::SetProgressBarValue_W(float Value)
{
    if (W_ProgressBar)
    {
        W_ProgressBar->SetPercent(Current_W / Max);
    }
}

void USkillWidget::SetProgressBarValue_E(float Value)
{
    if (E_ProgressBar)
    {
        E_ProgressBar->SetPercent(Current_E / Max);
    }
}

void USkillWidget::SetProgressBarValue_R(float Value)
{
    if (R_ProgressBar)
    {
        R_ProgressBar->SetPercent(Current_R / Max);
    }

}

void USkillWidget::SetProgressBarValue_I1(float Value)
{
    if (I1_ProgressBar)
    {
        I1_ProgressBar->SetPercent(Current_I1 / Max);
    }
}

void USkillWidget::SetProgressBarValue_I2(float Value)
{
    if (I2_ProgressBar)
    {
        I2_ProgressBar->SetPercent(Current_I2 / Max);
    }
}
