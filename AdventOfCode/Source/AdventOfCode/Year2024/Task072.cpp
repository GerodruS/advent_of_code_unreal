#include "Task072.h"

#include "Math/Int128.h"
#include "Misc/DefaultValueHelper.h"
#include "Misc/FileHelper.h"

DECLARE_LOG_CATEGORY_CLASS(LogTask, All, All);

FString FTask072::Run(const FString& InputFileName)
{
	FString FileContent;
	checkf(FFileHelper::LoadFileToString(FileContent, *InputFileName), TEXT("Failed to read the file: '%s'"), *InputFileName);

	TArray<TTuple<int64, TArray<int32>>> Data;
	TArray<FString> Lines;
	{
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

	uint64 Result = 0;
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

bool FTask072::CanBeTrue(int64 LeftValue, const TArray<int32>& RightValues)
{
	const int32 N = RightValues.Num() - 1;
	const int32 MaxValue = StaticCast<int32>(FMath::Pow(3.0f, N));
	for (int32 Value = 0; Value < MaxValue; Value++)
	{
		int32 MutValue = Value;
		uint64 R = RightValues[0];
		for (int32 i = 0; i < N; i++)
		{
			const int32 Bit = MutValue % 3;
			MutValue /= 3;
			if (Bit == 0)
			{
				R += RightValues[i + 1];
			}
			else if (Bit == 1)
			{
				R *= RightValues[i + 1];
			}
			else
			{
				// FMath::FloorToInt64(FMath::LogX(10.0, 10.0)) return 0!

				// double a = 2.30258509299404590109361379290930926799774169921875;
				// double b = 2.30258509299404590109361379290930926799774169921875;
				// a / b => 0.999999999999999888977697537484345957636833190917968750

				const uint64 RightValue = RightValues[i + 1];
				int64 NewValue;
				checkf(FDefaultValueHelper::ParseInt64(LexToString(R) + LexToString(RightValue), NewValue), TEXT("Failed to parse LeftValue. Line='%s'"), *(LexToString(R) + LexToString(RightValue)));
				R = NewValue;
			}
		}
		if (R == StaticCast<uint64>(LeftValue))
		{
			return true;
		}
	}
	return false;
}
