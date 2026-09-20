#include "GameplayTagIniLibrary.h"

#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "GameplayTagsManager.h"

TArray<FGameplayTag> UGameplayTagIniLibrary::GetGameplayTagsFromIni(const FString& IniFilePath)
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

int32 UGameplayTagIniLibrary::GetBranchWidth(const TArray<FMissionNode>& Nodes, int32 NodeIndex)
{
	const FMissionNode& Node = Nodes[NodeIndex];

	// 子がない
	if (Node.Children.Num() == 0)
	{
		return 1;
	}

	// 子が1つ
	if (Node.Children.Num() == 1)
	{
		return GetBranchWidth(
			Nodes,
			Node.Children[0]
		);
	}

	// 子が複数
	int32 Width = 0;

	for (int32 ChildIndex : Node.Children)
	{
		Width += GetBranchWidth(
			Nodes,
			ChildIndex
		);
	}

	return Width;
}

void UGameplayTagIniLibrary::SetXPosition(TArray<FMissionNode>& Nodes, int32 NodeIndex, float x, float stepX)
{
	FMissionNode& Node = Nodes[NodeIndex];
	Node.Position.X = x;
	// --------------------------------
	// 子がない場合
	// --------------------------------
	if (Node.Children.Num() == 0)
	{
		return;
	}

	// --------------------------------
	// 子が1つ
	// --------------------------------

	if (Node.Children.Num() == 1)
	{
		SetXPosition(Nodes, Node.Children[0], x, stepX);
		return;
	}

	// --------------------------------
	// 子が複数 → 分岐
	// --------------------------------

	const int32 ChildCount = Node.Children.Num();

	float CurrentX = x;

	for (int32 i = 0; i < ChildCount; ++i)
	{
		SetXPosition(Nodes, Node.Children[i], CurrentX, stepX);
		CurrentX += GetBranchWidth(Nodes, Node.Children[i]) * stepX;
	}
}



TArray<FMissionNode> UGameplayTagIniLibrary::CreateMissionTree(const TArray<FGameplayTag>& GameplayTags ,FVector2D step) {

	TArray<FMissionNode> Nodes;

	// 1. 全GameplayTagをNode化
	for (const FGameplayTag& Tag : GameplayTags)
	{
		FMissionNode Node;
		Node.Tag = Tag;
		Node.Position = FVector2D::ZeroVector;

		Nodes.Add(Node);
	}

	// 2. 親子関係を構築
	for (int32 ChildIndex = 0; ChildIndex < Nodes.Num(); ++ChildIndex)
	{
		const FGameplayTag ChildTag = Nodes[ChildIndex].Tag;

		FGameplayTag ParentTag = ChildTag.RequestDirectParent();

		if (!ParentTag.IsValid())
		{
			continue;
		}

		// 親を検索
		for (int32 ParentIndex = 0; ParentIndex < Nodes.Num(); ++ParentIndex)
		{
			if (Nodes[ParentIndex].Tag == ParentTag)
			{
				Nodes[ParentIndex].Children.Add(ChildIndex);
				break;
			}
		}
	}

	//set depth
	for (FMissionNode& Node : Nodes)
	{
		FString tagstr = Node.Tag.GetTagName().ToString();
		TArray<FString> tagarr;
		tagstr.ParseIntoArray(tagarr, TEXT("."), true);
		int32 depth = tagarr.Num() - 1;
		Node.Position.Y = depth * step.Y;

	}
	SetXPosition(Nodes, 0, 0.0f, step.X);
	return Nodes;
}