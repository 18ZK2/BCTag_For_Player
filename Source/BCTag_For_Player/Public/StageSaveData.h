

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

    /*
    * プレイしたステージの情報を保持
    * 
    */
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bCleared = false;
     


    
};