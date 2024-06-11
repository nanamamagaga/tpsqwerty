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

	// ī�޶�
	UPROPERTY(VisibleAnywhere, Category = Camera)
	class USpringArmComponent* springArmComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	class UCameraComponent* tpsCamComp;

	// HP
	float HP = 100;


	// �̵�
	// �̵� �ӵ�
	UPROPERTY(EditAnywhere, Category = PlayerSetting)
	float Normal = 800;

	// �̵� ����
	FVector direction;

	// ��Ÿ
	// �Ѿ� ����
	UPROPERTY(EditDefaultsOnly, Category = BulletFactory)
	TSubclassOf<class ABullet> bulletFactory;

	// �Ѿ� ���� ȿ�� ����
	UPROPERTY(EditAnywhere, Category = BulletEffect)
	class UParticleSystem* bulletEffectFactory;


	// UI
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

	// ��ų & ������
	// Q
	void Q1_Skill();
	void Q2_Skill();
	int32 Q = 0;
	// W
	void W1_Skill();
	void W2_Skill();
	int32 W = 0;
	// E
	void E1_Skill();
	void E2_Skill();
	int32 E = 0;
	//ATPSPlayer* PlayerController;
	// R
	void R1_Skill();
	void R2_Skill();
	int32 R = 0;
	int Rrestrict = 2.5f;
	// ������ 1
	void item1();
	float i1 = 0;
	// ������ 2
	void item2();
	float i2 = 0;

	// ��Ÿ��
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CooldTime")		// ��Ÿ�� bool
		float Q_CoolTime1 = 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CooldTime")		// ��Ÿ�� �ð�
		float Q_CoolTime2 = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CooldTime")		// ��Ÿ�� bool
		float W_CoolTime1 = 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CooldTime")		// ��Ÿ�� �ð�
		float W_CoolTime2 = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CooldTime")		// ��Ÿ�� bool
		float E_CoolTime1 = 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CooldTime")		// ��Ÿ�� �ð�
		float E_CoolTime2 = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CooldTime")		// ��Ÿ�� bool
	float R_CoolTime1 = 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CooldTime")		// ��Ÿ�� �ð�
	float R_CoolTime2 = 0;


	// ��ƼŬ

	UPROPERTY(EditAnywhere, Category = "SkillEffects")
	UParticleSystem* Q_Particle;

	UPROPERTY(EditAnywhere, Category = "SkillEffects")
	UParticleSystem* W_Particle;

	UPROPERTY(EditAnywhere, Category = "SkillEffects")
	UParticleSystem* E_Particle;

	UPROPERTY(EditAnywhere, Category = "SkillEffects")
	UParticleSystem* R_Particle;


	// �ִϸ��̼�

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	class UAnimationAsset* N_Ani;
	void Play_N_Ani();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	class UAnimationAsset* Q_Ani;
	void Play_Q_Ani();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	class UAnimationAsset* W1_Ani;
	void Play_W1_Ani();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	class UAnimationAsset* W2_Ani;
	void Play_W2_Ani();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	class UAnimationAsset* E_Ani;
	void Play_E_Ani();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	class UAnimationAsset* R1_Ani;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	class UAnimationAsset* R2_Ani;
	void Play_R1_Ani();
	void Play_R2_Ani();


};
