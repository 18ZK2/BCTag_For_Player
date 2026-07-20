#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "UObject/SoftObjectPtr.h"
#include "StageInfo.generated.h"

USTRUCT(BlueprintType)
struct FStageInfo : public FTableRowBase
{
    GENERATED_BODY()

    // 表示名
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FText StageName;

    // このステージを解放するために必要なステージ
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName UnlockStageID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TSoftObjectPtr<UWorld> World;
};