// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "StageSaveData.h"
#include "MySaveGame.generated.h"

/**
 * 
 */
UCLASS()
class BCTAG_FOR_PLAYER_API UMySaveGame : public USaveGame
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap< FName, FStageSaveData> StageData;
};
