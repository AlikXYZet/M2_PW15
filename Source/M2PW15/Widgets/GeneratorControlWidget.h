// 

#pragma once

// Base:
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

// UE:
#include "Engine/DataTable.h"

// Generated:
#include "GeneratorControlWidget.generated.h"
//--------------------------------------------------------------------------------------



/* ---   Pre-declaration of classes and structures   --- */

// UE:
class AGeneratorBox;
class UDataTable;
//--------------------------------------------------------------------------------------



// Структура типа Актора
USTRUCT(BlueprintType)
struct FActorType : public FTableRowBase
{
    GENERATED_BODY()

    // Тип создаваемого Актора
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TSubclassOf<AActor> Type;
};



UCLASS()
class M2PW15_API UGeneratorControlWidget : public UUserWidget
{
    GENERATED_BODY()

public:

    /* ---   Base   --- */

    /** Аналогичен OnInitialized() */
    virtual void NativeOnInitialized() override;

    /** Аналогичен Construct() */
    virtual void NativeConstruct() override;
    //--------------------------------------------



    /* ---   Generator   --- */

    // Таблица данных типов генерируемого Актора
    UPROPERTY(EditAnywhere, BlueprintReadWrite,
        Category = "Settings|Generator",
        meta = (RequiredAssetDataTags = "RowStructure=ActorType"))
    UDataTable* ActorsTypeTable;

    //

    /** Перегенерировать (перезапустить) данный Генератор */
    UFUNCTION(BlueprintCallable, CallInEditor,
        Category = "Generator")
    void RegenerateActors();

    /** Удалить сгенерируемые Акторы */
    UFUNCTION(BlueprintCallable, CallInEditor,
        Category = "Generator")
    void DeleteAllGeneratedActors();

    /** Установить новое количество генерируемых Акторов */
    UFUNCTION(BlueprintCallable, CallInEditor,
        Category = "Generator")
    void SetNumberActors(const int32& Value);

    /** Установить новый тип генерируемых Акторов */
    UFUNCTION(BlueprintCallable, CallInEditor,
        Category = "Generator")
    void SetActorType(const FString& TypeName);
    //--------------------------------------------



private:

    /* ---   Generator   --- */

    // Указатель на управляемый Генератор
    AGeneratorBox* GeneratorBox = nullptr;

    //

    /** Инициализация данных для Генератора */
    void InitForGenerator();
    //-------------------------------------------
};
