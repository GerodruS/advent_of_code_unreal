#include "Task191.h"

#include "InputCoreTypes.h"
#include "Misc/DefaultValueHelper.h"
#include "Misc/FileHelper.h"

DECLARE_LOG_CATEGORY_CLASS(LogTask, All, All);

FString FTask191::Run(const FString& InputFileName)
{
	FString FileContent;
	checkf(FFileHelper::LoadFileToString(FileContent, *InputFileName), TEXT("Failed to read the file: '%s'"), *InputFileName);

	TMap<TCHAR, TArray<FString>> Substrings;
	TArray<FString> Strings;
	{
		TArray<FString> Lines;
		FileContent.ParseIntoArrayLines(Lines, false);

		TArray<FString> SubstringsArray;
		Lines[0].ParseIntoArray(SubstringsArray, TEXT(", "), true);
		for (FString Substring : SubstringsArray)
		{
			Substrings.FindOrAdd(Substring[0]).Add(Substring);
		}

		for (TTuple<wchar_t, TArray<FString>>& Elem : Substrings)
		{
			Elem.Value.Sort();
		}

		// for (const auto& Pair : Substrings)
		// {
		// 	UE_LOG(LogTask, Error, TEXT("Key: %c"), Pair.Key);
		//
		// 	for (const FString& Value : Pair.Value)
		// 	{
		// 		UE_LOG(LogTask, Error, TEXT("  %s"), *Value);
		// 	}
		// }

		for (int32 i = 2; i < Lines.Num(); i++)
		{
			// UE_LOG(LogTask, Display, TEXT("[TEST] Lines '%s'"), *Lines[i]);
			Strings.Add(Lines[i]);
		}
	}

	int32 Result = 0;
	for (const FString& String : Strings)
	{
		// TSet<FString> Used;
		if (IsPossible(String, 0, Substrings))
		{
			// UE_LOG(LogTask, Display, TEXT("[TEST] poss '%s'"), *String);
			Result++;
		}
		else
		{
			// UE_LOG(LogTask, Display, TEXT("[TEST] imps '%s'"), *String);
		}
	}

	return FString::FromInt(Result);
}

bool FTask191::IsPossible(
	const FString& String,
	const int32 StartIndex,
	const TMap<TCHAR, TArray<FString>>& SubstringsMap)
{
	const int32 StringLen = String.Len();
	if (StartIndex == StringLen)
	{
		return true;
	}

	const TArray<FString>* const Substrings = SubstringsMap.Find(String[StartIndex]);
	if (Substrings == nullptr)
	{
		return false;
	}

	for (const FString& Substring : *Substrings)
	{
		const int32 SubstringLen = Substring.Len();
		if (StringLen < StartIndex + SubstringLen)
		{
			continue;
		}

		bool IsEquals = true;
		for (int32 i = 1; i < SubstringLen; i++)
		{
			if (String[StartIndex + i] < Substring[i])
			{
				return false;
			}

			if (Substring[i] < String[StartIndex + i])
			{
				IsEquals = false;
				break;
			}
		}

		if (IsEquals)
		{
			if (IsPossible(String, StartIndex + SubstringLen, SubstringsMap))
			{
				// UE_LOG(LogTask, Display, TEXT("[TEST] %d '%s' '%s'"), StartIndex, *NewString, *Substring);
				return true;
			}
		}
	}

	return false;
}
