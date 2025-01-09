//

#pragma once

// Base:
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"

// Generated:
#include "ChickenCharacter.generated.h"
//--------------------------------------------------------------------------------------



/* ---   Pre-declaration of classes   --- */

// UE:
class UCapsuleComponent;

// Interaction:
class APW_Character;
//--------------------------------------------------------------------------------------



UCLASS()
class M2PW15_API AChickenCharacter : public APawn
{
    GENERATED_BODY()

public:

    /* ---   Constructors   --- */

    // Sets default values for this character's properties
    AChickenCharacter();
    //-------------------------------------------



    /* ---   Components   --- */

    // Капсула основной коллизии
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components,
        meta = (AllowPrivateAccess = "true"))
    UCapsuleComponent* Capsule;

    // Меш визуализации Курицы
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components,
        meta = (AllowPrivateAccess = "true"))
    USkeletalMeshComponent* Mesh;
    //-------------------------------------------



protected:

    /* ---   Base   --- */

    // Called when the game starts or when spawned
    virtual void BeginPlay() override;
    //-------------------------------------------



public:

    /* ---   Reaction   --- */

    // Дистанция, меньше которой скорость перемещения максимальна
    UPROPERTY(EditAnywhere, BlueprintReadWrite,
        Category = "Settings|Reaction")
    float DistanceForMaxSpeed = 200.f;

    // Дистанция, больше которой скорость перемещения минимальна (равна нулю)
    UPROPERTY(EditAnywhere, BlueprintReadWrite,
        Category = "Settings|Reaction")
    float DistanceForMinSpeed = 500.f;

    // Максимальная скорость перемещения
    UPROPERTY(EditAnywhere, BlueprintReadWrite,
        Category = "Settings|Reaction")
    float MaxSpeed = 100.f;

    //

    /** Установить указатель на Игрока */
    void SetCurrentCharacter(APW_Character* Character);
    //-------------------------------------------



    /* ---   Movement   --- */

    // Флаг перемещения данной Курицы (используется в Анимации)
    UPROPERTY(EditAnywhere, BlueprintReadWrite,
        Category = "Settings|Movement")
    bool bIsMoving = false;

    // Скорость перемещения данной Курицы  (используется также в Анимации)
    UPROPERTY(EditAnywhere, BlueprintReadWrite,
        Category = "Settings|Movement")
    float Speed = 0.f;

    // Коэффициент скорость перемещения данной Курицы
    UPROPERTY(EditAnywhere, BlueprintReadWrite,
        Category = "Settings|Movement")
    float ActualSpeedCoeff = 0.02f;

    // Направление (поворот) перемещения данной Курицы  (используется также в Анимации)
    UPROPERTY(EditAnywhere, BlueprintReadWrite,
        Category = "Settings|Movement")
    float Turn = 0.f;
    //-------------------------------------------



private:

    /* ---   Reaction   --- */

    // Указатель на текущего приближающего игрока
    APW_Character* CurrentCharacter;

    // Таймер обновления данных Реакции
    FTimerHandle Timer_Reaction;

    // Локация текущего Игрока
    FVector CurrentCharacterLocation;

    //

    /** Инициализация данных Реакции */
    void InitReaction();

    /** Проверка валидности игрока и его дальность */
    void CheckCharacter();
    //-------------------------------------------



    /* ---   Movement   --- */

    // Таймер обновления данных Перемещения
    FTimerHandle Timer_Movement;

    //

    /** Инициализация данных Перемещения */
    void InitMovement();

    /** Контроль логики перемещения */
    void MovementControl(const bool& bEnable);

    /** Перемещение в сторону от Игрока */
    void MovingAwayFromCharacter();
    //-------------------------------------------



    /* ---   Tools   --- */

    /** Расчёт Скорости перемещения */
    float SpeedCalculation();

    /** Расчёт Направления перемещения */
    float TurnCalculation();

    /** Расчёт относительной Точки (Локации) */
    FVector RelativePointCalculation(
        const float& Distance,
        const FVector& CurrentLocation,
        const FVector& Direction);

    /** Фильтр угла ротации для исправления бага расчёта поворота */
    void RotationFilter(float& Angle);
    //-------------------------------------------
};
