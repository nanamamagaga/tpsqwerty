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

ATPSPlayer::ATPSPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 1. ���̷�Ż�޽� �����͸� �ҷ����� �ʹ�.
	ConstructorHelpers::FObjectFinder<USkeletalMesh>
		TempMesh(TEXT("SkeletalMesh'/Game/Mannequin/Character/Mesh/SK_Mannequin.SK_Mannequin'"));
	if (TempMesh.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(TempMesh.Object);
		// 2. Mesh ������Ʈ�� ��ġ�� ȸ�� ���� �����ϰ� �ʹ�.
		GetMesh()->SetRelativeLocationAndRotation(FVector(0, 0, -90), FRotator(0, -90, 0));
	}
	

	// 3. TPS ī�޶� ���̰� �ʹ�.
	// 3-1. SpringArm ������Ʈ ���̱�
	springArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	springArmComp->SetupAttachment(RootComponent);
	springArmComp->SetRelativeLocation(FVector(0, 70, 90));
	springArmComp->TargetArmLength = 400;
	springArmComp->bUsePawnControlRotation = true;
	// 3-2. Camera ������Ʈ ���̱�
	tpsCamComp = CreateDefaultSubobject<UCameraComponent>(TEXT("TpsCamComp"));
	tpsCamComp->SetupAttachment(springArmComp);
	tpsCamComp->bUsePawnControlRotation = false;

	bUseControllerRotationYaw = true;
	// 2�� ����
	JumpMaxCount = 2;

	// 4. �� ���̷�Ż�޽� ������Ʈ ���
	gunMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("GunMeshComp"));
	// 4-1. �θ� ������Ʈ�� Mesh ������Ʈ�� ����
	gunMeshComp->SetupAttachment(GetMesh());
}

// Called when the game starts or when spawned
void ATPSPlayer::BeginPlay()
{
	Super::BeginPlay();
	
	// 1. �������� UI ���� �ν��Ͻ� ����
	_sniperUI = CreateWidget(GetWorld(), sniperUIFactory);
	// 2. �Ϲ� ���� UI ũ�ν���� �ν��Ͻ� ����
	_crosshairUI = CreateWidget(GetWorld(), crosshairUIFactory);
	// 3. �Ϲ� ���� UI ���
	_crosshairUI->AddToViewport();

	// �⺻���� �������۰��� ����ϵ��� ����
	ChangeToSniperGun();


	
	ATPSProjectGameModeBase* currentGameMode = Cast<ATPSProjectGameModeBase>(GetWorld()->GetAuthGameMode());
	if (currentGameMode != nullptr)
	{
		//currentGameMode->ShowStart();
	}
	
}

// Called every frame
void ATPSPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (W == 0 && E == 0 && R == 0)
		Move();


	if (W == 1)		// W�� ������ �� 3�� �̻� ���� ���߿� �����ϸ� ����
	{
		static float Timer = 0.0f;
		Timer += DeltaTime;
		if (Timer >= 3.0f)
		{
			UE_LOG(LogTemp, Display, TEXT("ATTACK!"));
			// Attack!
			Timer = 0;
		}
	}

	if (E == 1)
	{
		// 1. ����
		FVector dir = FTransform(GetControlRotation()).TransformVector(direction);
		// 2. ����ȭ
		dir.Normalize();
		// 3. �̵��� ��ġ ��ǥ�� ���Ѵ�(p = p0 + vt).
		FVector newLocation = GetActorLocation() + dir * 1000;
		// 4. ���� ������ ��ġ ��ǥ�� �տ��� ���� �� ��ǥ�� �����Ѵ�.
		SetActorLocation(newLocation, true);

		UE_LOG(LogTemp, Display, TEXT("Flash!"));
		E++;
	}

	if (R == 1)
	{
		// 1. ����
		FVector dir = FTransform(GetControlRotation()).TransformVector(direction);
		// 2. ����ȭ
		dir.Normalize();
		// 3. �̵��� ��ġ ��ǥ�� ���Ѵ�(p = p0 + vt).
		FVector newLocation = GetActorLocation() + dir * 70;
		// 4. ���� ������ ��ġ ��ǥ�� �տ��� ���� �� ��ǥ�� �����Ѵ�.
		SetActorLocation(newLocation, true);

		UE_LOG(LogTemp, Display, TEXT("Fly!"));
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

	// �� ��ü �̺�Ʈ ó�� �Լ� ���ε�
	PlayerInputComponent->BindAction(TEXT("GrenadeGun"), IE_Pressed, this, &ATPSPlayer::ChangeToGrenadeGun);
	PlayerInputComponent->BindAction(TEXT("SniperGun"), IE_Pressed, this, &ATPSPlayer::ChangeToSniperGun);
	// �������� ���� ��� �̺�Ʈ ó�� �Լ� ���ε�
	PlayerInputComponent->BindAction(TEXT("Sniper"), IE_Pressed, this, &ATPSPlayer::SniperAim);
	PlayerInputComponent->BindAction(TEXT("Sniper"), IE_Released, this, &ATPSPlayer::SniperAim);

	// Q
	PlayerInputComponent->BindAction(TEXT("Q_Skill"), IE_Pressed, this, &ATPSPlayer::Q_Skill);
	PlayerInputComponent->BindAction(TEXT("Q_Skill"), IE_Released, this, &ATPSPlayer::Q_Skill);
	// W(���� ����)
	PlayerInputComponent->BindAction(TEXT("W_Skill"), IE_Pressed, this, &ATPSPlayer::W1_Skill);
	PlayerInputComponent->BindAction(TEXT("W_Skill"), IE_Released, this, &ATPSPlayer::W2_Skill);
	// E
	PlayerInputComponent->BindAction(TEXT("E_Skill"), IE_Pressed, this, &ATPSPlayer::E1_Skill);
	PlayerInputComponent->BindAction(TEXT("E_Skill"), IE_Released, this, &ATPSPlayer::E2_Skill);
	// R
	PlayerInputComponent->BindAction(TEXT("R_Skill"), IE_Pressed, this, &ATPSPlayer::R1_Skill);
	PlayerInputComponent->BindAction(TEXT("R_Skill"), IE_Released, this, &ATPSPlayer::R2_Skill);

}

void ATPSPlayer::Turn(float value)
{
	AddControllerYawInput(value);
}
void ATPSPlayer::LookUp(float value)
{
	AddControllerPitchInput(value);
}

// �¿� �Է� �̺�Ʈ ó�� �Լ�
void ATPSPlayer::InputHorizontal(float value)
{
	direction.Y = value;
}
// ���� �Է� �̺�Ʈ ó�� �Լ�
void ATPSPlayer::InputVertical(float value)
{
	direction.X = value;
}

void ATPSPlayer::InputJump()
{
	Jump();
}

void ATPSPlayer::Move()
{
	// �÷��̾� �̵� ó��
	direction = FTransform(GetControlRotation()).TransformVector(direction);
	AddMovementInput(direction);
	direction = FVector::ZeroVector;
}

void ATPSPlayer::InputFire()
{
	// �� �� ��� ����Ʈ���̽� ����� ����� ����

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


	if (bUsingGrenadeGun)
	{
		if (bbHit)
		{
			// �浹 ó�� -> �Ѿ� ���� ȿ�� ���
			// �Ѿ� ���� ȿ�� Ʈ������
			FTransform bT;
			// �ε��� ��ġ �Ҵ�
			bT.SetLocation(hitInfo.ImpactPoint);
			// �Ѿ� ���� ȿ�� �ν��Ͻ� ����
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), bulletEffectFactory, bT);
		}
	}

	// �������۰� ��� ��
	else
	{
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

			auto hitComp = hitInfo.GetComponent();
			// 1. ���� ������Ʈ�� ������ ����Ǿ� �ִٸ�
			if (hitComp && hitComp->IsSimulatingPhysics())
			{
				// 2. �������� ���� ������ �ʿ�
				FVector force = -hitInfo.ImpactNormal * hitComp->GetMass() * 500000;
				// 3. �� �������� ���������� �ʹ�.
				hitComp->AddForce(force);
			}

			// �ε��� ����� ������ �Ǵ��ϱ�
			auto enemy = hitInfo.GetActor()->GetDefaultSubobjectByName(TEXT("FSM"));
			if (enemy)
			{
				auto enemyFSM = Cast<UEnemyFSM>(enemy);
				enemyFSM->OnDamageProcess();
			}
		}
	}
}

// ��ź������ ����
void ATPSPlayer::ChangeToGrenadeGun()
{
	// ��ź�� ��� ������ üũ
	bUsingGrenadeGun = true;
	gunMeshComp->SetVisibility(true);
}
// �������۰����� ����
void ATPSPlayer::ChangeToSniperGun()
{
	bUsingGrenadeGun = false;
	gunMeshComp->SetVisibility(false);
}

void ATPSPlayer::SniperAim()
{
	// �������۰� ��尡 �ƴ϶�� ó������ �ʴ´�.
	if (bUsingGrenadeGun)
	{
		return;
	}
	// Pressed �Է� ó��
	if (bSniperAim == false)
	{
		// 1. �������� ���� ��� Ȱ��ȭ
		bSniperAim = true;
		// 2. ������������ UI ���
		_sniperUI->AddToViewport();
		// 3. ī�޶��� �þ߰� Field Of View ����
		tpsCamComp->SetFieldOfView(45.0f);
		// 4. �Ϲ� ���� UI ����
		_crosshairUI->RemoveFromParent();
	}
	// Released �Է� ó��
	else
	{
		// 1. �������� ���� ��� ��Ȱ��ȭ
		bSniperAim = false;
		// 2. �������� ���� UI ȭ�鿡�� ����
		_sniperUI->RemoveFromParent();
		// 3. ī�޶� �þ߰� ������� ����
		tpsCamComp->SetFieldOfView(90.0f);
		// 4. �Ϲ� ���� UI ���
		_crosshairUI->AddToViewport();
	}
}

// ��ų


void ATPSPlayer::Q_Skill()
{
	W = 1;	// W�� 1�̸� Tick�Լ��� Move()�� �ߵ� X

}
void ATPSPlayer::W1_Skill()
{
	UE_LOG(LogTemp, Display, TEXT("Focus"));
	W = 1;	// W�� 1�̸� Tick�Լ��� Move()�� �ߵ� X

}
void ATPSPlayer::W2_Skill()
{
	W = 0;	// Move()�� �ٽ� �ߵ��ǰ� ����
	//Attack!
	UE_LOG(LogTemp, Display, TEXT("MoveMoveMove"));
}
void ATPSPlayer::E1_Skill()
{
	E = 1;
}
void ATPSPlayer::E2_Skill()
{
	E = 0;
}

void ATPSPlayer::R1_Skill()
{
	R = 1;
}
void ATPSPlayer::R2_Skill()
{
	R = 0;
}