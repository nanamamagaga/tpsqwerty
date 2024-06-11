// Fill out your copyright notice in the Description page of Project Settings.


#include "TPSPlayer.h"
#include <GameFramework/SpringArmComponent.h>
#include <Camera/CameraComponent.h>
#include "Bullet.h"
#include <Blueprint/UserWidget.h>
#include <Kismet/GameplayStatics.h>
#include "EnemyFSM.h"
#include "TPSProjectGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include <GameFramework/CharacterMovementComponent.h>
#include "Particles/ParticleSystemComponent.h"
#include "Animation/AnimInstance.h"
#include "Animation/AnimationAsset.h"
#include "GameFramework/Actor.h"
#include "SkillWidget.h"

ATPSPlayer::ATPSPlayer()
{

 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	

	// TPS ī�޶�
	// SpringArm ������Ʈ ���̱�
	springArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	springArmComp->SetupAttachment(RootComponent);
	springArmComp->SetRelativeLocation(FVector(0, 70, 90));
	springArmComp->TargetArmLength = 400;
	springArmComp->bUsePawnControlRotation = true;
	// Camera ������Ʈ ���̱�
	tpsCamComp = CreateDefaultSubobject<UCameraComponent>(TEXT("TpsCamComp"));
	tpsCamComp->SetupAttachment(springArmComp);
	tpsCamComp->bUsePawnControlRotation = false;

	bUseControllerRotationYaw = true;
	// 2�� ����
	JumpMaxCount = 2;
}

// Called when the game starts or when spawned
void ATPSPlayer::BeginPlay()
{
	Super::BeginPlay();
	
	// �Ϲ� ���� UI
	_crosshairUI = CreateWidget(GetWorld(), crosshairUIFactory);
	_crosshairUI->AddToViewport();



	
	ATPSProjectGameModeBase* currentGameMode = Cast<ATPSProjectGameModeBase>(GetWorld()->GetAuthGameMode());
	if (currentGameMode != nullptr)
	{
		//currentGameMode->ShowStart();
		//currentGameMode->ShowNext();
		currentGameMode->ShowSuccess();
	}


	
}

// Called every frame
void ATPSPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// ������

	if (Q == 0 && W == 0 && E == 0 && R == 0)		// ��ų�� �ƹ��͵� �������� �ʾ��� ��
		Move();

	if (Q == 0 && W == 0 && E == 1 && E_CoolTime1 == 0 && R == 0)	//  e�� ���������� ��Ÿ���� ��
		Move();
	if (Q == 0 && W == 0 && E == 0 && R == 1 && R_CoolTime1 == 0)	//  r�� ���������� ��Ÿ���� ��
		Move();
	if (Q == 0 && W == 1 && W_CoolTime1 == 0 && E == 0 && R == 0)	//  w�� ���������� ��Ÿ���� ��
		Move();
	if (Q == 1 && Q_CoolTime1 == 0 && W == 0 && E == 0 && R == 0)	//  q�� ���������� ��Ÿ���� ��
		Move();


	// ��ų

	if (Q == 1 && Q_CoolTime1 == 1)
	{
		InputFire();
		Play_Q_Ani();
		Q_CoolTime1 = 0;
		Q = 0;
	}

	if (W == 1 && W_CoolTime1 == 1)		// W�� ������ �� 3.16�� ���� ���߿� �����ϸ� ����
	{

		static float Timer = 0.0f;
		Timer += DeltaTime;
		if (Timer >= 3.16f && E == 0 && R == 0)
		{
			// Attack!
			Timer = 0;

			InputFire();
			W = 0;	// W�� ���̻� ������� �ʵ���
			W_CoolTime1 = 0;

		}

		// �ٸ� ��ų�� ���� �������� ����
		if (Q==1 && Q_CoolTime1 == 1|| E == 1 && E_CoolTime1 == 1 || R == 1 && R_CoolTime1 == 1)
		{
			W2_Skill();
		}
	}

	if (E == 1 && E_CoolTime1 == 1)
	{
		// 1. ����
		FVector dir = FTransform(GetControlRotation()).TransformVector(direction);
		// 2. ����ȭ
		dir.Normalize();

		// ��ƼŬ
		// �̵��ϱ� �� ��ġ�� ��ƼŬ�� �����ȴ�.
		FVector nowLocation = GetActorLocation();
		// ��ƼŬ �ν��Ͻ� ����
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), E_Particle, nowLocation);

		// 3. �̵��� ��ġ ��ǥ�� ���Ѵ�(p = p0 + vt).
		FVector newLocation = GetActorLocation() + dir * 1000;

		//��ƼŬ �ν��Ͻ� ����
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), E_Particle, newLocation);

		// 4. ���� ������ ��ġ ��ǥ�� �տ��� ���� �� ��ǥ�� �����Ѵ�.
		SetActorLocation(newLocation, true);
		E = 0;
		// �ִϸ��̼�
		Play_E_Ani();
		// ��Ÿ��
		E_CoolTime1 = 0;	// E_CoolTime1�� 0�̸� ��� �Ұ���
	}

	if (R == 1 && R_CoolTime1 == 1 )
	{
		// R�� ���� �ð� ����
		static float Timer = 0.0f;
		Timer += DeltaTime;
		if (Timer >= Rrestrict)	// Rrestrict��ŭ �����Ѵ�.
		{
			Timer = 0;
			R_CoolTime1 = 0;	// R_CoolTime1�� 0�̸� ��� �Ұ���
		}

		// 1. ����
		FVector dir = FTransform(GetControlRotation()).TransformVector(direction);
		// 2. ����ȭ
		dir.Normalize();

		// ��ƼŬ
		// �̵��ϱ� �� ��ġ�� ��ƼŬ�� �����ȴ�.
		FVector nowLocation = GetActorLocation();
		// ��ƼŬ �ν��Ͻ� ����
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), R_Particle, nowLocation);

		// 3. �̵��� ��ġ ��ǥ�� ���Ѵ�(p = p0 + vt).
		FVector newLocation = GetActorLocation() + dir * 55;

		//��ƼŬ �ν��Ͻ� ����
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), R_Particle, newLocation);

		// 4. ���� ������ ��ġ ��ǥ�� �տ��� ���� �� ��ǥ�� �����Ѵ�.
		SetActorLocation(newLocation, true);

	}


	static float Timer = 0.0f;
	Timer += DeltaTime;
	if (Timer >= 1.0f)
	{
		class ATPSProjectGameModeBase* currentGameMode = Cast<ATPSProjectGameModeBase>(GetWorld()->GetAuthGameMode());
		if (currentGameMode != nullptr)
		{
			//currentGameMode->ShowNext();
		}
		Timer = 0.0f; // Ÿ�̸� �ʱ�ȭ
	}
}

// Called to bind functionality to input
void ATPSPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ATPSPlayer::Turn);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &ATPSPlayer::LookUp);
	// �¿� �Է� �̺�Ʈ ó�� �Լ� ���ε�
	PlayerInputComponent->BindAxis(TEXT("Horizontal"), this, &ATPSPlayer::InputHorizontal);
	// ���� �Է� �̺�Ʈ ó�� �Լ� ���ε�
	PlayerInputComponent->BindAxis(TEXT("Vertical"), this, &ATPSPlayer::InputVertical);
	// ���� �Է� �̺�Ʈ ó�� �Լ� ���ε�
	PlayerInputComponent->BindAction(TEXT("Jump"), IE_Pressed, this, &ATPSPlayer::InputJump);
	// �Ѿ� �߻� �̺�Ʈ ó�� �Լ� ���ε�
	PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &ATPSPlayer::InputFire);


	// Q
	PlayerInputComponent->BindAction(TEXT("Q_Skill"), IE_Pressed, this, &ATPSPlayer::Q1_Skill);
	PlayerInputComponent->BindAction(TEXT("Q_Skill"), IE_Released, this, &ATPSPlayer::Q2_Skill);
	// W(���� ����)
	PlayerInputComponent->BindAction(TEXT("W_Skill"), IE_Pressed, this, &ATPSPlayer::W1_Skill);
	PlayerInputComponent->BindAction(TEXT("W_Skill"), IE_Released, this, &ATPSPlayer::W2_Skill);
	// E
	PlayerInputComponent->BindAction(TEXT("E_Skill"), IE_Pressed, this, &ATPSPlayer::E1_Skill);
	PlayerInputComponent->BindAction(TEXT("E_Skill"), IE_Released, this, &ATPSPlayer::E2_Skill);
	// R
	PlayerInputComponent->BindAction(TEXT("R_Skill"), IE_Pressed, this, &ATPSPlayer::R1_Skill);
	PlayerInputComponent->BindAction(TEXT("R_Skill"), IE_Released, this, &ATPSPlayer::R2_Skill);

	// ������
	PlayerInputComponent->BindAction(TEXT("item1"), IE_Pressed, this, &ATPSPlayer::item1);
	PlayerInputComponent->BindAction(TEXT("item2"), IE_Pressed, this, &ATPSPlayer::item2);
}

void ATPSPlayer::Turn(float value)
{
	AddControllerYawInput(value);
}
void ATPSPlayer::LookUp(float value)
{
	AddControllerPitchInput(value);
}

// �¿�
void ATPSPlayer::InputHorizontal(float value)
{
	direction.Y = value;
}
// ����
void ATPSPlayer::InputVertical(float value)
{
	direction.X = value;
}

void ATPSPlayer::InputJump()
{
	Jump();
}

// �̵�
void ATPSPlayer::Move()
{
	direction = FTransform(GetControlRotation()).TransformVector(direction);
	AddMovementInput(direction);
	direction = FVector::ZeroVector;
}

void ATPSPlayer::InputFire()
{

	// LineTrace �� ���� ��ġ
	FVector startPos = tpsCamComp->GetComponentLocation();
	// LineTrace �� ���� ��ġ
	FVector endPos = tpsCamComp->GetComponentLocation() + tpsCamComp->GetForwardVector() * 5000;
	// LineTrace �� �浹 ������ ���� ����
	FHitResult hitInfo;
	// �浹 �ɼ� ���� ����
	FCollisionQueryParams params;
	// �ڱ� �ڽ�(�÷��̾�) �� �浹���� ����
	params.AddIgnoredActor(this);
	// Channel ���͸� �̿��� LineTrace �浹 ����(�浹 ����, ���� ��ġ, ���� ��ġ, ���� ä��, �浹 �ɼ�)
	bool bHit = GetWorld()->LineTraceSingleByChannel(hitInfo, startPos, endPos, ECC_Visibility, params);

	float SphereRadius = 50.0f;
	bool bbHit = GetWorld()->SweepSingleByChannel(hitInfo, startPos, endPos, FQuat::Identity, ECC_Visibility, FCollisionShape::MakeSphere(SphereRadius), params);

	// Q ��ų
	if ( Q == 1 && Q_CoolTime1 == 1)
	{
		UE_LOG(LogTemp, Display, TEXT("success"));

		if (bbHit) {
			// �Ѿ� ���� ȿ�� Ʈ������
			FTransform bT;
			// �ε��� ��ġ �Ҵ�
			bT.SetLocation(hitInfo.ImpactPoint);
			// �Ѿ� ���� ȿ�� �ν��Ͻ� ����
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Q_Particle, bT);

			// �ε��� ����� ������ �Ǵ��ϱ�
			auto enemy = hitInfo.GetActor()->GetDefaultSubobjectByName(TEXT("FSM"));
			if (enemy)
			{
				UE_LOG(LogTemp, Display, TEXT("In Area, enemy hp - 10"));

				//auto enemyFSM = Cast<UEnemyFSM>(enemy);
				//enemyFSM->OnDamageProcess();
			}
		}
	}
	// W ��ų
	if (W == 1 && W_CoolTime1 == 1)
	{
		if (bbHit) {
			UE_LOG(LogTemp, Display, TEXT("success"));
			// �Ѿ� ���� ȿ�� Ʈ������
			FTransform bT;
			// �ε��� ��ġ �Ҵ�
			bT.SetLocation(hitInfo.ImpactPoint);
			// �Ѿ� ���� ȿ�� �ν��Ͻ� ����
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), W_Particle, bT);

			// �ε��� ����� ������ �Ǵ��ϱ�
			auto enemy = hitInfo.GetActor()->GetDefaultSubobjectByName(TEXT("FSM"));
			if (enemy)
			{
				//auto enemyFSM = Cast<UEnemyFSM>(enemy);
				//enemyFSM->OnDamageProcess();
			}
		}
	}

	// ��Ÿ ��� ��
	else
	{
		Play_N_Ani();
		// LineTrace�� �ε����� ��
		if (bHit)
		{
			// �浹 ó�� -> �Ѿ� ���� ȿ�� ���
			// �Ѿ� ���� ȿ�� Ʈ������
			FTransform bulletTrans;
			// �ε��� ��ġ �Ҵ�
			bulletTrans.SetLocation(hitInfo.ImpactPoint);
			// �Ѿ� ���� ȿ�� �ν��Ͻ� ����
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), bulletEffectFactory, bulletTrans);
		}
	}
}

// ��ų


void ATPSPlayer::Q1_Skill()
{
	Q_CoolTime2 = 3.0f;
	Q = 1;
}
void ATPSPlayer::Q2_Skill()
{
	Q = 0;
}
void ATPSPlayer::W1_Skill()
{
	// �ִϸ��̼�
	if (W_CoolTime1 == 1)
		Play_W1_Ani();

	W_CoolTime2 = 1.5f;
	W = 1;	// W�� 1�̸� Tick�Լ��� Move()�� �ߵ� X

}
void ATPSPlayer::W2_Skill()
{
	W = 0;	// Move()�� �ٽ� �ߵ��ǰ� ����

	W_CoolTime1 = 0;
	Play_W2_Ani();

}
void ATPSPlayer::E1_Skill()
{
	E_CoolTime2 = 8.0f;
	E = 1;
}
void ATPSPlayer::E2_Skill()
{
	E = 0;
}

void ATPSPlayer::R1_Skill()
{
	R = 1;
	R_CoolTime2 = 8.0f;
	// �ִϸ��̼�
	if (R_CoolTime1 == 1)
		Play_R1_Ani();
}
void ATPSPlayer::R2_Skill()
{
	R = 0;

	// �ִϸ��̼�
	Play_R2_Ani();
	R_CoolTime1 = 0;
}
void ATPSPlayer::item1()
{
	if (i1 < 3) {
		HP += 10;
		i1++;
	}
}
void ATPSPlayer::item2()
{
	if (i2 < 3) {
		Q_CoolTime1 = 1;
		W_CoolTime1 = 1;
		E_CoolTime1 = 1;
		R_CoolTime1 = 1;

		i2++;
	}
}

// �ִϸ��̼�
void ATPSPlayer::Play_N_Ani()
{
	GetMesh()->PlayAnimation(N_Ani, false);
}
void ATPSPlayer::Play_Q_Ani()
{
	GetMesh()->PlayAnimation(Q_Ani, false);
}
void ATPSPlayer::Play_E_Ani()
{
	GetMesh()->PlayAnimation(E_Ani, false);
}
void ATPSPlayer::Play_W1_Ani()
{
	GetMesh()->PlayAnimation(W1_Ani, false);
}
void ATPSPlayer::Play_W2_Ani()
{
	GetMesh()->PlayAnimation(W2_Ani, false);
}
void ATPSPlayer::Play_R1_Ani()
{
	GetMesh()->PlayAnimation(R1_Ani, true);
}
void ATPSPlayer::Play_R2_Ani()
{
	GetMesh()->PlayAnimation(R2_Ani, false);
}
