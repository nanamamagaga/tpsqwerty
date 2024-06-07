#include "WhiteSphere.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Enemy.h"

// Sets default values
AWhiteSphere::AWhiteSphere()
{
    PrimaryActorTick.bCanEverTick = true;

    // �浹ü ������Ʈ ���� �� ����
    CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComponent"));
    CollisionComponent->InitSphereRadius(50.0f);
    RootComponent = CollisionComponent;
    CollisionComponent->OnComponentHit.AddDynamic(this, &AWhiteSphere::OnHit); // �浹 �̺�Ʈ ���ε�

    // �浹 ����
    CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    CollisionComponent->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
    CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
    CollisionComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Block);
    CollisionComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldStatic, ECollisionResponse::ECR_Block);

    // �޽� ������Ʈ ���� �� ����
    MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
    MeshComponent->SetupAttachment(RootComponent);
    static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereMesh(TEXT("StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));
    if (SphereMesh.Succeeded())
    {
        MeshComponent->SetStaticMesh(SphereMesh.Object);
    }

    // ������Ʈ ������ ������Ʈ ���� �� ����
    ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
    ProjectileMovementComponent->SetUpdatedComponent(CollisionComponent);

    // �ӵ��� õõ�� �̵��ϵ��� ����
    ProjectileMovementComponent->InitialSpeed = 50.0f;
    ProjectileMovementComponent->MaxSpeed = 50.0f;

    ProjectileMovementComponent->bRotationFollowsVelocity = true;
    ProjectileMovementComponent->bShouldBounce = false;
    ProjectileMovementComponent->ProjectileGravityScale = 0.0f; // �߷� ���� ����
}

// Called when the game starts or when spawned
void AWhiteSphere::BeginPlay()
{
    Super::BeginPlay();
}

// Called every frame
void AWhiteSphere::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (Enemy)
    {
        FVector Direction = (Enemy->GetActorLocation() - GetActorLocation()).GetSafeNormal();
        ProjectileMovementComponent->Velocity = Direction * ProjectileMovementComponent->InitialSpeed;
    }
}

void AWhiteSphere::Initialize(AEnemy* InEnemy)
{
    this->Enemy = InEnemy;
}

void AWhiteSphere::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
    if (OtherActor && OtherActor != this)
    {
        if (OtherActor == Enemy)
        {
            // ���׹̿� �浹�ϸ� ������ ��� ó�� (�ּ� ó��)
            // if (ATempMan* TempMan = Cast<ATempMan>(Target))
            // {
            //     TempMan->Die();
            // }
        }
        else if (OtherActor == Enemy)
        {
            // ���׹̿� �浹�ϸ� ������ �����
            Destroy();
        }
    }
}