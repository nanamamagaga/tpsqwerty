#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MeteorBomb.generated.h"

UCLASS()
class TPSPROJECT_API AMeteorBomb : public AActor
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    AMeteorBomb();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    class USphereComponent* CollisionComponent;

 
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    class UStaticMeshComponent* MeshComponent;


    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
    class UProjectileMovementComponent* ProjectileMovementComponent;

    UStaticMeshComponent* GetMeshComponent() const;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
    FVector TargetLocation;

private:
    UFUNCTION()
    void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
};
