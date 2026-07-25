//

#pragma once

// Core:
#include "Kismet/BlueprintFunctionLibrary.h"

//#include "AnimationSharingTypes.h"
#include "AnimationSharingManager.h"

// Generated:
#include "AnimationSharingBlueprintLibrary.generated.h"
//--------------------------------------------------------------------------------------



/* ---   RTS Ability System Blueprint Library   --- */

UCLASS(meta = (BlueprintThreadSafe, ScriptName = "Animation Sharing Blueprint Library"))
class M2PW15_API UAnimationSharingBlueprintLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

    /* ---   AS | Manager   --- */

    UFUNCTION(BlueprintCallable,
        Category = "Utilities|Animation Sharing")
    static void UnregisterActorInAnimSharing(UPARAM(ref) UAnimationSharingManager* Manager, AActor* Actor)
    {
        if (Manager && Actor)
        {
            Manager->UAnimationSharingManager::UnregisterActor(Actor);
        }
    };
    //-------------------------------------------
};
//--------------------------------------------------------------------------------------
