//

#pragma once

// Base:
#include "CoreMinimal.h"
#include "GameFramework/Character.h"

// Generated:
#include "PW_Character.generated.h"
//--------------------------------------------------------------------------------------



/* ---   Pre-declaration of classes   --- */

// UE:
class UCameraComponent;
//--------------------------------------------------------------------------------------



UCLASS()
class M2PW15_API APW_Character : public ACharacter
{
    GENERATED_BODY()

public:

    /* ---   Constructors   --- */

    // Устанавливает значения по умолчанию для свойств этого персонажа
    APW_Character();
    //-------------------------------------------



    /* ---   Components   --- */

    // Камера от первого лица
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components,
        meta = (AllowPrivateAccess = "true"))
    UCameraComponent* FirstPersonCameraComponent;
    //-------------------------------------------



protected:

    /* ---   Base   --- */

    // Called when the game starts or when spawned
    virtual void BeginPlay() override;
    //-------------------------------------------



public:

    /* ---   Base   --- */

    // Called every frame
    virtual void Tick(float DeltaTime) override;
    //-------------------------------------------



    /* ---   Input Action   --- */

    // Флаг блокировки управления игрока
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings|Movement")
    bool bPlayerControlLock = false;

    // Базовая скорость поворота, град/сек
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings|Camera")
    float BaseTurnRate = 1.f;

    // Базовая скорость обзора вверх/вниз в градусах в секунду
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings|Camera")
    float BaseLookUpRate = 1.f;

    //

    // Called to bind functionality to input
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
    //-------------------------------------------



private:

    /* ---   Input Action   --- */

    /** Перемещение вперёд/назад */
    void MoveForward(float Val);

    /** Перемещение влево/вправо */
    void MoveRight(float Val);

    /**	Поворот с заданной скоростью */
    void TurnAtRate(float Rate);

    /**	Обзор вверх/вниз с заданной скоростью */
    void LookUpAtRate(float Rate);
    //-------------------------------------------
};
