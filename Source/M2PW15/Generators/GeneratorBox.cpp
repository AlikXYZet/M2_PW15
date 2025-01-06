//

// Base:
#include "GeneratorBox.h"

// UE:
#include "Components/BillboardComponent.h"
#include "Components/BoxComponent.h"
#include "Kismet/KismetMathLibrary.h"
//--------------------------------------------------------------------------------------



/* ---   Constructors   --- */

// Sets default values
AGeneratorBox::AGeneratorBox()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = false; // Предварительно

    /* ---   Components   --- */

    // Корневой компонент
    RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

    // Билборд для упращения прямого взаимодействия в конструкторе
    Billboard = CreateDefaultSubobject<UBillboardComponent>(TEXT("Billboard Interactions"));
    Billboard->SetupAttachment(RootComponent);
    Billboard->SetComponentTickEnabled(false);

    // Область (зона) генерации
    Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Generation Zone"));
    Box->SetupAttachment(RootComponent);
    Box->SetComponentTickEnabled(false);
    Box->SetBoxExtent(FVector(50.f));
    Box->SetGenerateOverlapEvents(false);
    Box->SetCollisionProfileName(UCollisionProfile::NoCollision_ProfileName);
    //-------------------------------------------
}
//--------------------------------------------------------------------------------------



/* ---   Generator   --- */

void AGeneratorBox::ReGenerate()
{
    DeleteGeneratedActors();
    Generate();
}

void AGeneratorBox::DeleteGeneratedActors()
{
    TArray<AActor*> lResultActors;

    UGameplayStatics::GetAllActorsWithTag(GetWorld(), VerificationTag, lResultActors);

    for (auto& lObjects : lResultActors)
    {
        lObjects->Destroy();
    }
}

void AGeneratorBox::Generate()
{
    if (ActorType)
    {
        FVector lRandomPoint;
        AActor* lNewActor;

        FVector lLocation = GetActorLocation();
        FVector lExtent = Box->Bounds.BoxExtent;

        // Параметр создания: Всегда создавать, но с попыткой изменить локацию
        FActorSpawnParameters lSpawnParameters;
        lSpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

        for (int32 i = 0; i < NumberOfActors; ++i)
        {
            lRandomPoint = UKismetMathLibrary::RandomPointInBoundingBox(lLocation, lExtent);

            lNewActor = GetWorld()->SpawnActor<AActor>(
                ActorType.Get(),
                lRandomPoint,
                FRotator::ZeroRotator,
                lSpawnParameters);

            if (lNewActor)
            {
                // Тег-маркировка Клетки.
                // Необходим для удаления только Генерируемых Клеток
                lNewActor->Tags.Add(VerificationTag);
            }
        }
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("'%s': ActorType is NOT"),
            *GetNameSafe(this));
    }
}
//--------------------------------------------------------------------------------------
