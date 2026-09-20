#pragma once
#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GameplayTagContainer.h"
#include "GameplayTagIniLibrary.generated.h"

#define VTAG "UE C++ book"
#define FTAG "Gameplay Tags"

USTRUCT(BlueprintType)
struct FMissionNode
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = VTAG)
	FGameplayTag Tag;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = VTAG)
	TArray<int32> Children;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = VTAG)
	FVector2D Position;

};

UCLASS()
class BCTAG_FOR_PLAYER_API UGameplayTagIniLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = FTAG,BlueprintPure)
	static TArray<FGameplayTag> GetGameplayTagsFromIni(const FString& IniFilePath);

	UFUNCTION(BlueprintCallable, Category = FTAG,BlueprintPure)
	static TArray<FMissionNode> CreateMissionTree(const TArray<FGameplayTag>& GameplayTags, FVector2D step);

private:
	UFUNCTION(BlueprintCallable, Category = FTAG, BlueprintPure)
	static void SetXPosition(TArray<FMissionNode>& Nodes, int32 NodeIndex, float x, float stepX);

	UFUNCTION(BlueprintCallable, Category = FTAG, BlueprintPure)
	static int32 GetBranchWidth(
		const TArray<FMissionNode>& Nodes,
		int32 NodeIndex
	);

};