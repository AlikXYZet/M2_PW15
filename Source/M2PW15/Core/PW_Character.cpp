//

// Base:
#include "PW_Character.h"

// UE:
#include "Camera/CameraComponent.h"
#include "Components/SphereComponent.h"

// Interaction:
#include "M2PW15/NPC/ChickenCharacter.h"
//--------------------------------------------------------------------------------------



/* ---   Constructors   --- */

// Sets default values
APW_Character::APW_Character()
{
    // Set this character to call Tick() every frame.
    // You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = false; // Предварительно
    //-------------------------------------------



    /* ---   Components   --- */

    // Камера от первого лица
    FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("First Person Camera"));
    FirstPersonCameraComponent->SetupAttachment(RootComponent);
    FirstPersonCameraComponent->SetRelativeLocation(FVector(0.f, 0.f, 48.f));
    //FirstPersonCameraComponent->SetRelativeRotation(FRotator(0.f, 90.f, -90.f));
    FirstPersonCameraComponent->bUsePawnControlRotation = true;

    // Сфера коллизии для запуска реакции
    ReactionsCollision = CreateDefaultSubobject<USphereComponent>(TEXT("Reactions"));
    ReactionsCollision->SetupAttachment(RootComponent);
    ReactionsCollision->OnComponentBeginOverlap.AddDynamic(this, &APW_Character::BeginOverlap_Reaction);
    ReactionsCollision->OnComponentEndOverlap.AddDynamic(this, &APW_Character::EndOverlap_Reaction);
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



/* ---   Components   --- */

void APW_Character::BeginOverlap_Reaction(
    UPrimitiveComponent* OverlappedComponent,
    AActor* OtherActor,
    UPrimitiveComponent* OtherComp,
    int32 OtherBodyIndex,
    bool bFromSweep,
    const FHitResult& SweepResult)
{
    if (AChickenCharacter* lChicken = Cast<AChickenCharacter>(OtherActor))
    {
        lChicken->SetCurrentCharacter(this);
    }
}

void APW_Character::EndOverlap_Reaction(
    UPrimitiveComponent* OverlappedComponent,
    AActor* OtherActor,
    UPrimitiveComponent* OtherComp,
    int32 OtherBodyIndex)
{
    if (AChickenCharacter* lChicken = Cast<AChickenCharacter>(OtherActor))
    {
        lChicken->SetCurrentCharacter(nullptr);
    }
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
