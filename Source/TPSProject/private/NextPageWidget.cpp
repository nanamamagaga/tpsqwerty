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

	// ���⼭ �۷ι� ���� CountMap�� �����Ѵ�.
	// �� �������� ���� ������ CountMap++;���ָ� ���̴�.
	// if (CountMap == 3) UGameplayStatics::OpenLevel(GetWorld(), "Boss3"); �̷� ������

	CountMap++;

	if(CountMap == 1)
		UGameplayStatics::OpenLevel(GetWorld(), "Map1");
	if(CountMap == 2)
		UGameplayStatics::OpenLevel(GetWorld(), "Map2");
	
	// �ȵȴ�. ����: ��ư�� 1ȸ���̿���...... ��Ȱ���� �� ����? ���� �ð���
	


	UGameplayStatics::SetGamePaused(GetWorld(), false);
	GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(false);

}
