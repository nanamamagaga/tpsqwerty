// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TPSPlayer.generated.h"

UCLASS()
class TPSPROJECT_API ATPSPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATPSPlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:

	// �� �ʹ� ī�޶� �κ�
	UPROPERTY(VisibleAnywhere, Category = Camera)
	class USpringArmComponent* springArmComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	class UCameraComponent* tpsCamComp;


	// �̵�
	// �̵� �ӵ�
	UPROPERTY(EditAnywhere, Category = PlayerSetting)
	float Normal = 800;

	// �̵� ����
	FVector direction;

	// ��Ÿ
	// �� ���̷�Ż�޽�
	UPROPERTY(EditAnywhere, Category = GunMesh)
	class USkeletalMeshComponent* gunMeshComp;
	// �Ѿ� ����
	UPROPERTY(EditDefaultsOnly, Category = BulletFactory)
	TSubclassOf<class ABullet> bulletFactory;
	// ��ź�� ��� ������ ����
	bool bUsingGrenadeGun = true;
	// �������� ���� ������ ����
	bool bSniperAim = false;
	// �Ѿ� ���� ȿ�� ����
	UPROPERTY(EditAnywhere, Category = BulletEffect)
	class UParticleSystem* bulletEffectFactory;


	// UI
	// �������� UI ���� ����
	UPROPERTY(EditDefaultsOnly, Category = SniperUI)
	TSubclassOf<class UUserWidget> sniperUIFactory;
	// �������� UI ���� �ν��Ͻ�
	class UUserWidget* _sniperUI;
	// �Ϲ� ���� ũ�ν����UI ����
	UPROPERTY(EditDefaultsOnly, Category = SniperUI)
	TSubclassOf<class UUserWidget> crosshairUIFactory;
	// ũ�ν���� UI ���� �ν��Ͻ�
	class UUserWidget* _crosshairUI;



	// ���ε�

	// �¿� ȸ�� �Է� ó��
	void Turn(float value);
	// ���� ȸ�� �Է� ó��
	void LookUp(float value);
	// �¿� �̵� �Է� �̺�Ʈ ó�� �Լ�
	void InputHorizontal(float value);
	// ���� �̵� �Է� �̺�Ʈ ó�� �Լ�
	void InputVertical(float value);
	// ���� �Է� �̺�Ʈ ó�� �Լ�
	void InputJump();
	// �÷��̾� �̵� ó��
	void Move();
	// �Ѿ� �߻� ó�� �Լ�
	void InputFire();

	/*
	// �������۰� ����ƽ�޽� �߰�
	UPROPERTY(VisibleAnywhere, Category = GunMesh)
	class UStaticMeshComponent* sniperGunComp;
	*/
	// ��ź������ ����
	void ChangeToGrenadeGun();
	// �������۰����� ����
	void ChangeToSniperGun();
	// �������� ����
	void SniperAim();
	// Q
	void Q_Skill();
	// W
	void W1_Skill();
	void W2_Skill();
	int32 W = 0;
	// E
	void E1_Skill();
	void E2_Skill();
	int32 E = 0;
	ATPSPlayer* PlayerController;
	// R
	void R1_Skill();
	void R2_Skill();
	int32 R = 0;
};
