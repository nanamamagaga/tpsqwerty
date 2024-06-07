#include "MeteorBomb.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
AMeteorBomb::AMeteorBomb()
{
    PrimaryActorTick.bCanEverTick = true;

    // �浹ü ������Ʈ ���� �� ����
    CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComponent"));
    CollisionComponent->InitSphereRadius(50.0f);
    RootComponent = CollisionComponent;
    CollisionComponent->OnComponentHit.AddDynamic(this, &AMeteorBomb::OnHit); // �浹 �̺�Ʈ ���ε�

    // �浹 ����
    CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    CollisionComponent->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
    CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
    CollisionComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Block);
    CollisionComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldStatic, ECollisionResponse::ECR_Block);

    // �޽� ������Ʈ ���� �� ����
    MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
    MeshComponent->SetupAttachment(RootComponent);
    static ConstructorHelpers::FObjectFinder<UStaticMesh> MeteorMesh(TEXT("StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));
    if (MeteorMesh.Succeeded())
    {
        MeshComponent->SetStaticMesh(MeteorMesh.Object);
    }

    // ������Ʈ ������ ������Ʈ ���� �� ����
    ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
    ProjectileMovementComponent->SetUpdatedComponent(CollisionComponent);
    ProjectileMovementComponent->InitialSpeed = 600.0f;  // �ӵ� ����
    ProjectileMovementComponent->MaxSpeed = 600.0f;  // �ӵ� ����
    ProjectileMovementComponent->bRotationFollowsVelocity = true;
    ProjectileMovementComponent->bShouldBounce = false;
    ProjectileMovementComponent->ProjectileGravityScale = 0.0f; // �߷� ���� ����
}

// Called when the game starts or when spawned
void AMeteorBomb::BeginPlay()
{
    Super::BeginPlay();

    // ��ǥ ��ġ�� ���ϴ� �ӵ� ����
    FVector Direction = (TargetLocation - GetActorLocation()).GetSafeNormal();
    ProjectileMovementComponent->Velocity = Direction * ProjectileMovementComponent->InitialSpeed;
}

// Called every frame
void AMeteorBomb::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

UStaticMeshComponent* AMeteorBomb::GetMeshComponent() const
{
    return MeshComponent;
}

void AMeteorBomb::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
    // �浹 �� ��������� ó��
    if (OtherActor && OtherActor != this && OtherActor != GetOwner())
    {
        Destroy();
    }
}
