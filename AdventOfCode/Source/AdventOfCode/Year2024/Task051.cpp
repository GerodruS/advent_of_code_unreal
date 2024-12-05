#include "Task051.h"

#include "Misc/DefaultValueHelper.h"
#include "Misc/FileHelper.h"

DECLARE_LOG_CATEGORY_CLASS(LogTask, All, All);

FString FTask051::Run(const FString& InputFileName)
{
	FString FileContent;
	checkf(FFileHelper::LoadFileToString(FileContent, *InputFileName), TEXT("Failed to read the file: '%s'"), *InputFileName);

	TArray<TTuple<int32, int32>> Rules;
	TArray<TArray<int32>> Sequences;
	{
		TArray<FString> Lines;
		FileContent.ParseIntoArrayLines(Lines, false);

		const int32 FoundIndex = Lines.Find(TEXT(""));
		checkf(FoundIndex != INDEX_NONE, TEXT("Empty line not found!"));

		for (int32 i = 0; i < FoundIndex; i++)
		{
			TArray<FString> Columns;
			Lines[i].ParseIntoArray(Columns, TEXT("|"), true);
			checkf(Columns.Num() == 2, TEXT("Unexpected count of column! Line='%s' i=%d"), *Lines[i], i);

			int32 Left;
			checkf(FDefaultValueHelper::ParseInt(Columns[0], Left), TEXT("Failed to parse Left number: '%s'. Line='%s' i=%d"), *Columns[0], *Lines[i], i);

			int32 Right;
			checkf(FDefaultValueHelper::ParseInt(Columns[1], Right), TEXT("Failed to parse Right number: '%s'. Line='%s' i=%d"), *Columns[1], *Lines[i], i);

			Rules.Add(TTuple<int32, int32>(Left, Right));
		}

		for (int32 i = FoundIndex + 1; i < Lines.Num(); i++)
		{
			TArray<FString> Numbers;
			Lines[i].ParseIntoArray(Numbers, TEXT(","), true);
			checkf(1 < Numbers.Num(), TEXT("Unexpected count of numbers! Line='%s' i=%d"), *Lines[i], i);

			TArray<int32> Sequence;
			for (FString Number : Numbers)
			{
				int32 Value;
				checkf(FDefaultValueHelper::ParseInt(Number, Value), TEXT("Failed to parse number. Line='%s' i=%d"), *Lines[i], i);
				Sequence.Add(Value);
			}
			Sequences.Add(Sequence);
		}
	}

	int32 Result = 0;
	for (int32 i = 0; i < Sequences.Num(); i++)
	{
		const TArray<int32>& Sequence = Sequences[i];

		bool IsCorrect = true;
		for (TTuple<int32, int32> Rule : Rules)
		{
			const int32 Left = Sequence.Find(Rule.Get<0>());
			if (Left == INDEX_NONE)
			{
				continue;
			}

			const int32 Right = Sequence.Find(Rule.Get<1>());
			if (Right == INDEX_NONE)
			{
				continue;
			}

			if (Right < Left)
			{
				IsCorrect = false;
				break;
			}
		}
		if (IsCorrect)
		{
			const int32 Index = Sequence.Num() / 2;
			const int32 Value = Sequence[Index];
			Result += Value;
		}
	}

	return FString::FromInt(Result);
}
