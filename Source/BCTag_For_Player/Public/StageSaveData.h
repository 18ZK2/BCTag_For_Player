

#pragma once

#include "CoreMinimal.h"
#include "StageSaveData.generated.h"
/**
 * 
 */
USTRUCT(BlueprintType)
struct FStageSaveData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bCleared = false;


    
};