#include "GameplayTagIniLibrary.h"

#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "GameplayTagsManager.h"

TArray<FGameplayTag> UGameplayTagIniLibrary::GetGameplayTagsFromIni(
	const FString& IniFilePath
)
{
	TArray<FGameplayTag> Result;

	// 相対パスならプロジェクトフォルダ基準
	FString FullPath = IniFilePath;

	if (FPaths::IsRelative(FullPath))
	{
		FullPath = FPaths::Combine(
			FPaths::ProjectDir(),
			FullPath
		);
	}

	FPaths::NormalizeFilename(FullPath);

	// INIを読み込む
	FString IniText;

	if (!FFileHelper::LoadFileToString(IniText, *FullPath))
	{
		UE_LOG(
			LogTemp,
			Error,
			TEXT("Failed to load INI: %s"),
			*FullPath
		);

		return Result;
	}

	// GameplayTagList=(Tag="XXXX") を検索
	const FString SearchText =
		TEXT("GameplayTagList=(Tag=\"");

	int32 SearchStart = 0;

	while (true)
	{
		int32 FoundPosition = IniText.Find(
			SearchText,
			ESearchCase::IgnoreCase,
			ESearchDir::FromStart,
			SearchStart
		);

		if (FoundPosition == INDEX_NONE)
		{
			break;
		}

		// Tag=" の直後
		const int32 TagStart =
			FoundPosition + SearchText.Len();

		// 次の " を探す
		const int32 TagEnd = IniText.Find(
			TEXT("\""),
			ESearchCase::IgnoreCase,
			ESearchDir::FromStart,
			TagStart
		);

		if (TagEnd == INDEX_NONE)
		{
			break;
		}

		const FString TagName =
			IniText.Mid(
				TagStart,
				TagEnd - TagStart
			);

		if (!TagName.IsEmpty())
		{
			// GameplayTagとして取得
			FGameplayTag Tag =
				UGameplayTagsManager::Get().RequestGameplayTag(
					FName(*TagName),
					false
				);

			if (Tag.IsValid())
			{
				Result.Add(Tag);
			}
		}

		// 次のタグを検索
		SearchStart = TagEnd + 1;
	}

	return Result;
}