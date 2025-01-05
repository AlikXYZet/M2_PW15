//

// Base:
#include "PW_Character.h"

// UE:
#include "Camera/CameraComponent.h"
//--------------------------------------------------------------------------------------



/* ---   Constructors   --- */

// Sets default values
APW_Character::APW_Character()
{
    // Set this character to call Tick() every frame.
    // You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = false; // Предварительно


    /* ---   Components   --- */

    // Камера от первого лица
    FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("First Person Camera"));
    FirstPersonCameraComponent->SetupAttachment(RootComponent);
    FirstPersonCameraComponent->SetRelativeLocation(FVector(0.f, 0.f, 48.f));
    //FirstPersonCameraComponent->SetRelativeRotation(FRotator(0.f, 90.f, -90.f));
    FirstPersonCameraComponent->bUsePawnControlRotation = true;
    //-------------------------------------------
}
//--------------------------------------------------------------------------------------



/* ---   Base   --- */

// Called when the game starts or when spawned
void APW_Character::BeginPlay()
{
    Super::BeginPlay();

}

// Called every frame
void APW_Character::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

}
//--------------------------------------------------------------------------------------



/* ---   Input Action   --- */

// Called to bind functionality to input
void APW_Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    // Перемещение:
    PlayerInputComponent->BindAxis("MoveForward", this, &APW_Character::MoveForward);
    PlayerInputComponent->BindAxis("MoveRight", this, &APW_Character::MoveRight);

    // Поворот мышью:
    PlayerInputComponent->BindAxis("TurnRate", this, &APW_Character::TurnAtRate);
    PlayerInputComponent->BindAxis("LookUpRate", this, &APW_Character::LookUpAtRate);
}

void APW_Character::MoveForward(float Value)
{
    if (Value != 0.0f)
    {
        // add movement in that direction
        AddMovementInput(GetActorForwardVector(), Value);
    }
}

void APW_Character::MoveRight(float Value)
{
    if (Value != 0.0f)
    {
        // add movement in that direction
        AddMovementInput(GetActorRightVector(), Value);
    }
}

void APW_Character::TurnAtRate(float Rate)
{
    if (!bPlayerControlLock)
    {
        // Вычисление дельты для текущего кадра на основе информации о скорости
        AddControllerYawInput(Rate * BaseTurnRate);
    }
}

void APW_Character::LookUpAtRate(float Rate)
{
    if (!bPlayerControlLock)
    {
        // Вычисление дельты для текущего кадра на основе информации о скорости
        AddControllerPitchInput(-Rate * BaseLookUpRate);
    }
}
//--------------------------------------------------------------------------------------
