#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EnemyFSM.generated.h"

// ����� ���� ����
UENUM(BlueprintType)
enum class EEnemyState : uint8
{
    Idle,
    Move,
    Attack,
    Damage,
    Die,
    Meteor,
    WhiteSphere,
    Charge
};

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TPSPROJECT_API UEnemyFSM : public UActorComponent
{
    GENERATED_BODY()

public:
    // Sets default values for this component's properties
    UEnemyFSM();

protected:
    // Called when the game starts
    virtual void BeginPlay() override;

public:
    // Called every frame
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
    // ���� ����
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = FSM)
    EEnemyState mState = EEnemyState::WhiteSphere; // �ʱ� ���¸� WhiteSphere�� ����

    // ��� ����
    void IdleState();
    // �̵� ����
    void MoveState();
    // ���� ����
    void AttackState();
    // �ǰ� ����
    void DamageState();
    // ���� ����
    void DieState();
    // ���׿� ����
    void MeteorState();
    // WhiteSphere ����
    void WhiteSphereState();
    void ChargeState();

    // ��� �ð�
    UPROPERTY(EditDefaultsOnly, Category = FSM)
    float idleDelayTime = 2;
    // ��� �ð�
    float currentTime = 0;
    // ���׿� ��ų ��� �ֱ�
    UPROPERTY(EditDefaultsOnly, Category = FSM)
    float meteorInterval = 10.0f;
    // WhiteSphere ��ų ��� �ֱ�
    UPROPERTY(EditDefaultsOnly, Category = FSM)
    float whiteSphereInterval = 15.0f; // WhiteSphere ��� �ֱ�
    // ���׿� ��ų ��� �ð�
    UPROPERTY(EditDefaultsOnly, Category = FSM)
    float meteorWarningTime = 3.0f;

    // Ÿ��
    UPROPERTY(EditAnywhere, Category = FSM)
    class ATempMan* target;

    // ���� ����
    UPROPERTY()
    class AEnemy* me;

    // ���� ����
    UPROPERTY(EditAnywhere, Category = FSM)
    float attackRange = 150.0f;

    // ���� ��� �ð�
    UPROPERTY(EditAnywhere, Category = FSM)
    float attackDelayTime = 2.0f;

    // �ǰ� �˸� �̺�Ʈ �Լ�
    void OnDamageProcess();

    // ü��
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = FSM)
    int32 hp = 3;
    // �ǰ� ��� �ð�
    UPROPERTY(EditAnywhere, Category = FSM)
    float damageDelayTime = 2.0f;

    // �Ʒ��� ������� �ӵ�
    UPROPERTY(EditAnywhere, Category = FSM)
    float dieSpeed = 50.0f;

    // ���׿� ��ų�� ���� �Լ���
    void LaunchMeteors();
    // WhiteSphere ��ų�� ���� �Լ���
    void LaunchWhiteSphere();
    void ChargeWarning();
    //ȭ��Ʈ ���Ǿ� 
    void Initialize(class AEnemy* InEnemy);


private:
    UStaticMesh* WarningCircleMesh;
    UStaticMesh* MeteorMesh;
    UStaticMesh* WhiteSphereMesh; // WhiteSphere �޽�


    bool bWhiteSphereExecuted; // WhiteSphere ���� �� �� ���� ����
};
