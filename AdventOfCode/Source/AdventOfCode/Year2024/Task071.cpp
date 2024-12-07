#include "Task071.h"

#include "Misc/DefaultValueHelper.h"
#include "Misc/FileHelper.h"

DECLARE_LOG_CATEGORY_CLASS(LogTask, All, All);

FString FTask071::Run(const FString& InputFileName)
{
	FString FileContent;
	checkf(FFileHelper::LoadFileToString(FileContent, *InputFileName), TEXT("Failed to read the file: '%s'"), *InputFileName);

	TArray<TTuple<int64, TArray<int32>>> Data;
	{
		TArray<FString> Lines;
		FileContent.ParseIntoArrayLines(Lines, false);

		for (int32 i = 0; i < Lines.Num(); i++)
		{
			TArray<FString> Numbers;
			Lines[i].ParseIntoArray(Numbers, TEXT(" "), true);
			checkf(2 < Numbers.Num(), TEXT("Unexpected count of Elements %d, Line='%s'"), Numbers.Num(), *Lines[i]);

			const FString LeftValueString = Numbers[0].TrimChar(':');
			int64 LeftValue;
			checkf(FDefaultValueHelper::ParseInt64(LeftValueString, LeftValue), TEXT("Failed to parse LeftValue. Line='%s'"), *Lines[i]);

			TArray<int32> RightValues;
			for (int32 j = 1; j < Numbers.Num(); j++)
			{
				int32 RightValue;
				checkf(FDefaultValueHelper::ParseInt(Numbers[j], RightValue), TEXT("Failed to parse RightValue#%d. Line='%s'"), (j - 1), *Lines[i]);
				RightValues.Add(RightValue);
			}

			Data.Add(TTuple<int64, TArray<int32>>(LeftValue, RightValues));
		}
	}

	int64 Result = 0;
	for (int32 i = 0; i < Data.Num(); i++)
	{
		const TTuple<int64, TArray<int32>>& Element = Data[i];
		const bool Can = CanBeTrue(Element.Get<0>(), Element.Get<1>());
		if (Can)
		{
			Result += Element.Get<0>();
		}
	}

	return LexToString(Result);
}

bool FTask071::CanBeTrue(int64 LeftValue, const TArray<int32>& RightValues)
{
	const int32 N = RightValues.Num() - 1;
	const int32 MaxValue = 1 << N;
	for (int32 Value = 0; Value < MaxValue; Value++)
	{
		int64 R = RightValues[0];
		for (int32 i = 0; i < N; i++)
		{
			const int32 Bit = (Value >> i) & 1;
			if (Bit == 0)
			{
				R += RightValues[i + 1];
			}
			else
			{
				R *= RightValues[i + 1];
			}
		}
		if (R == LeftValue)
		{
			return true;
		}
	}
	return false;
}
