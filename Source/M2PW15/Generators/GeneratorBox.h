// 

#pragma once

// Base:
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

// UE:
#include "Kismet/GameplayStatics.h"

// Generated:
#include "GeneratorBox.generated.h"
//--------------------------------------------------------------------------------------



/* ---   Pre-declaration of classes and structures   --- */

// UE:
class UBoxComponent;
//--------------------------------------------------------------------------------------



UCLASS()
class M2PW15_API AGeneratorBox : public AActor
{
    GENERATED_BODY()

public:

    /* ---   Constructors   --- */

    // Sets default values for this actor's properties
    AGeneratorBox();
    //-------------------------------------------



    /* ---   Components   --- */

    // Область (зона) генерации
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components,
        meta = (AllowPrivateAccess = "true"))
    UBoxComponent* Box;
    //-------------------------------------------



public:

    /* ---   Generator   --- */

    /** Перегенерировать (перезапустить) данный Генератор */
    UFUNCTION(BlueprintCallable, CallInEditor,
        Category = "Generator")
    void ReGenerate();

    /** Удалить сгенерируемые Акторы */
    UFUNCTION(BlueprintCallable, CallInEditor,
        Category = "Generator")
    void DeleteGeneratedObjects();
    //-------------------------------------------



    /* ---   Generator | Settings   --- */

    // Тип генерируемого Актора
    UPROPERTY(EditAnywhere, BlueprintReadOnly,
        Category = "Generator|Settings")
    TSubclassOf<AActor> ActorType;

    // Количество Акторов
    UPROPERTY(EditAnywhere, BlueprintReadOnly,
        Category = "Generator|Settings",
        meta = (ClampMin = "1", UIMin = "1", ClampMax = "1000", UIMax = "1000"))
    int32 NumberOfActors = 10;
    //-------------------------------------------



private:

    /* ---   Generator   --- */

    // Тег для определения объекта, созданной генератором
    FName VerificationTag = FName(GetNameSafe(this));

    //

    /** Сгенерировать Акторы */
    void Generate();
    //-------------------------------------------
};
