#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "UObject/SoftObjectPtr.h"
#include "StageInfo.generated.h"

USTRUCT(BlueprintType)
struct FStageInfo : public FTableRowBase
{
    GENERATED_BODY()
    // ?��\?��?��?��?��
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName stageID;

    //if clear UnlockStages open
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FName> UnlockStageIDs;
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TSoftObjectPtr<UWorld> World;
};