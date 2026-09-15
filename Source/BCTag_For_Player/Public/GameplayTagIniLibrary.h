#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GameplayTagContainer.h"
#include "GameplayTagIniLibrary.generated.h"

UCLASS()
class BCTAG_FOR_PLAYER_API UGameplayTagIniLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "Gameplay Tags",BlueprintPure)
	static TArray<FGameplayTag> GetGameplayTagsFromIni(
		const FString& IniFilePath
	);
};