#include "Task032.h"

#include "Misc/DefaultValueHelper.h"
#include "Misc/FileHelper.h"

DECLARE_LOG_CATEGORY_CLASS(LogTask, All, All);

FString FTask032::Run(const FString& InputFileName)
{
	FString Text;
	checkf(FFileHelper::LoadFileToString(Text, *InputFileName), TEXT("Failed to read the file: '%s'"), *InputFileName);

	const FString EnableString = TEXT("do()");
	const FString DisableString = TEXT("don't()");
	int32 Index = Text.Find(DisableString, ESearchCase::CaseSensitive, ESearchDir::FromStart, 0);
	while (Index != INDEX_NONE)
	{
		int32 EndIndex = Text.Find(EnableString, ESearchCase::CaseSensitive, ESearchDir::FromStart, Index);
		if (EndIndex == INDEX_NONE)
		{
			EndIndex = Text.Len();
		}
		else
		{
			EndIndex += EnableString.Len();
		}

		Text.RemoveAt(Index, EndIndex - Index, false);
		Index = Text.Find(DisableString, ESearchCase::CaseSensitive, ESearchDir::FromStart, 0);
	}

	const FString StartSubstring = TEXT("mul(");
	const int32 StartSubStringLen = StartSubstring.Len();

	int32 Result = 0;
	Index = Text.Find(StartSubstring, ESearchCase::CaseSensitive, ESearchDir::FromStart, 0);
	while (Index != INDEX_NONE)
	{
		const int32 StartIndex = Index + StartSubStringLen;
		const int32 EndIndex = Text.Find(TEXT(")"), ESearchCase::CaseSensitive, ESearchDir::FromStart, StartIndex);
		if (EndIndex == INDEX_NONE)
		{
			break;
		}

		FString Substring = Text.Mid(StartIndex, EndIndex - StartIndex);
		if (Substring.Contains(","))
		{
			TArray<FString> Elements;
			Substring.ParseIntoArray(Elements, TEXT(","), false);
			int32 NumA, NumB;
			if (Elements.Num() == 2 &&
				FDefaultValueHelper::ParseInt(Elements[0], NumA) &&
				FDefaultValueHelper::ParseInt(Elements[1], NumB))
			{
				Result += NumA * NumB;
			}
		}
		
		Index = Text.Find(StartSubstring, ESearchCase::CaseSensitive, ESearchDir::FromStart, StartIndex);
	}

	return FString::FromInt(Result);
}
