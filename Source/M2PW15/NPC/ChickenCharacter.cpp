//

// Base:
#include "ChickenCharacter.h"

// UE:
#include "Components/CapsuleComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"

// Interaction:
#include "M2PW15/Core/PW_Character.h"
//--------------------------------------------------------------------------------------



/* ---   Constructors   --- */

// Sets default values
AChickenCharacter::AChickenCharacter()
{
    // Set this character to call Tick() every frame.
    // You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = false; // Предварительно
    //-------------------------------------------



    /* ---   Components   --- */

    // Капсула основной коллизии
    Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Collision"));
    RootComponent = Capsule;

    // Меш визуализации Курицы
    Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Visualization"));
    Mesh->SetupAttachment(RootComponent);
    //-------------------------------------------
}
//--------------------------------------------------------------------------------------



/* ---   Base   --- */

// Called when the game starts or when spawned
void AChickenCharacter::BeginPlay()
{
    Super::BeginPlay();

    InitReaction();
    InitMovement();
}
//--------------------------------------------------------------------------------------



/* ---   Reaction   --- */

void AChickenCharacter::SetCurrentCharacter(APW_Character* iCharacter)
{
    CurrentCharacter = iCharacter;

    if (CurrentCharacter)
    {
        GetWorldTimerManager().UnPauseTimer(Timer_Reaction);
    }
}

void AChickenCharacter::InitReaction()
{
    GetWorldTimerManager().SetTimer(
        Timer_Reaction,
        this,
        &AChickenCharacter::CheckCharacter,
        0.1f,
        true);

    GetWorldTimerManager().PauseTimer(Timer_Reaction);
}

void AChickenCharacter::CheckCharacter()
{
    if (CurrentCharacter)
    {
        CurrentCharacterLocation = CurrentCharacter->GetActorLocation();

        Speed = SpeedCalculation();
        Turn = TurnCalculation();

        MovementControl(true);
    }
    else
    {
        GetWorldTimerManager().PauseTimer(Timer_Reaction);

        MovementControl(false);
    }
}
//--------------------------------------------------------------------------------------



/* ---   Movement   --- */

void AChickenCharacter::InitMovement()
{
    GetWorldTimerManager().SetTimer(
        Timer_Movement,
        this,
        &AChickenCharacter::MovingAwayFromCharacter,
        0.02f,
        true);

    GetWorldTimerManager().PauseTimer(Timer_Movement);
}

void AChickenCharacter::MovementControl(const bool& ibEnable)
{
    if (GetWorldTimerManager().IsTimerActive(Timer_Movement) != ibEnable)
    {
        bIsMoving = ibEnable;

        if (ibEnable)
        {
            GetWorldTimerManager().UnPauseTimer(Timer_Movement);
        }
        else
        {
            GetWorldTimerManager().PauseTimer(Timer_Movement);
        }
    }
}

void AChickenCharacter::MovingAwayFromCharacter()
{
    // Плавное изменение ротации
    AddActorWorldRotation(
        FRotator(
            0.f,
            Turn * 0.1f,
            0.f));

    // Движение вперёд с расчётной скоростью (чем игрок ближе, тем выше скорость)
    AddActorWorldOffset(GetActorForwardVector() * Speed * ActualSpeedCoeff);
}
//--------------------------------------------------------------------------------------



/* ---   Tools   --- */

float AChickenCharacter::SpeedCalculation()
{
    float lSpeed = FVector::Distance(CurrentCharacterLocation, GetActorLocation());
    lSpeed -= DistanceForMaxSpeed;
    lSpeed *= MaxSpeed / DistanceForMinSpeed;
    lSpeed = MaxSpeed - lSpeed;

    // Clamp:
    if (lSpeed < 0.f)
    {
        lSpeed = 0.f;
    }
    else if (lSpeed > MaxSpeed)
    {
        lSpeed = MaxSpeed;
    }

    return lSpeed;
}

float AChickenCharacter::TurnCalculation()
{
    FVector lCurrentLocation = GetActorLocation();
    float lTraceRadius = 100.f;

    // Переменная суммирования Локации перемещения
    FVector lSumImpactPoints = RelativePointCalculation(
        Speed,
        lCurrentLocation,
        CurrentCharacterLocation);

    // Переменная-Заглушка
    TArray<AActor*> lActorArray;

    // Результаты трассировки
    TArray<FHitResult> lHits;

    UKismetSystemLibrary::SphereTraceMulti(
        GetWorld(),
        lCurrentLocation,
        lCurrentLocation,
        lTraceRadius,
        ETraceTypeQuery::TraceTypeQuery2,
        false,
        lActorArray,
        EDrawDebugTrace::None,
        lHits,
        true);

    float lHitDistance;

    // Учёт каждого препятствия с приоритетом от дистанции
    // (чем ближе, тем выше приоритет)
    // и суммирование их в общий вектор
    for (auto& Hit : lHits)
    {
        lHitDistance = (lTraceRadius - FVector::Distance(lCurrentLocation, Hit.ImpactPoint))
            * (Cast<AChickenCharacter>(Hit.Actor) ? 0.2f : 1.f);

        lSumImpactPoints += RelativePointCalculation(
            lHitDistance,
            lCurrentLocation,
            Hit.ImpactPoint);
    }

    float lResult = UKismetMathLibrary::FindLookAtRotation(lSumImpactPoints, FVector::ZeroVector).Yaw;
    lResult -= GetActorRotation().Yaw;

    RotationFilter(lResult);

    return lResult;
}

FVector AChickenCharacter::RelativePointCalculation(
    const float& iDistance,
    const FVector& iCurrentLocation,
    const FVector& iDirection)
{
    FVector lPoint = UKismetMathLibrary::GetForwardVector(
        UKismetMathLibrary::FindLookAtRotation(
            iCurrentLocation,
            iDirection));

    return lPoint * iDistance;
}

void AChickenCharacter::RotationFilter(float& iAngle)
{
    iAngle -= int8(iAngle / 180) * 380;
}
//--------------------------------------------------------------------------------------
