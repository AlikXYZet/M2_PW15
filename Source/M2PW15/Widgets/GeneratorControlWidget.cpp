//

// Base:
#include "GeneratorControlWidget.h"

// Interaction:
#include "M2PW15/Generators/GeneratorBox.h"
//--------------------------------------------------------------------------------------



/* ---   Base   --- */

void UGeneratorControlWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    InitForGenerator();
}

void UGeneratorControlWidget::NativeConstruct()
{
    Super::NativeConstruct();

    //InitForGenerator();
}
//--------------------------------------------------------------------------------------



/* ---   Generator   --- */

void UGeneratorControlWidget::InitForGenerator()
{
    if (!GeneratorBox)
    {
        TArray<AActor*> lResultActors;
        UGameplayStatics::GetAllActorsOfClass(GetWorld(), AGeneratorBox::StaticClass(), lResultActors);

        if (lResultActors.IsValidIndex(0))
        {
            GeneratorBox = Cast<AGeneratorBox>(lResultActors[0]);
        }
        else
        {
            UE_LOG(LogTemp, Error, TEXT("'%s': GeneratorBox is NOT"),
                *GetNameSafe(this));
        }
    }
}

void UGeneratorControlWidget::RegenerateActors()
{
    if (GeneratorBox)
    {
        GeneratorBox->ReGenerate();
    }
}

void UGeneratorControlWidget::DeleteAllGeneratedActors()
{
    if (GeneratorBox)
    {
        GeneratorBox->DeleteGeneratedActors();
    }
}

void UGeneratorControlWidget::SetNumberActors(const int32& iValue)
{
    if (GeneratorBox)
    {
        GeneratorBox->NumberOfActors = iValue;
    }
}

void UGeneratorControlWidget::SetActorType(const FString& TypeName)
{
    if (GeneratorBox)
    {
        FActorType* lNewRow = ActorsTypeTable->FindRow<FActorType>(
            FName(TypeName),
            "UGeneratorControlWidget::SetActorType()");

        if (lNewRow)
        {
            GeneratorBox->ActorType = lNewRow->Type;
        }
    }
}
//--------------------------------------------------------------------------------------
