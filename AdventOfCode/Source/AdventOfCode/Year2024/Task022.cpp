#include "Task022.h"

#include "Misc/DefaultValueHelper.h"
#include "Misc/FileHelper.h"

DECLARE_LOG_CATEGORY_CLASS(LogTask, All, All);

FString FTask022::Run(const FString& InputFileName)
{
	FString FileContent;
	checkf(FFileHelper::LoadFileToString(FileContent, *InputFileName), TEXT("Failed to read the file: '%s'"), *InputFileName);

	TArray<FString> Lines;
	FileContent.ParseIntoArrayLines(Lines);

	TArray<TArray<int32>> Matrix;
	for (const FString& Line : Lines)
	{
		TArray<FString> Columns;
		Line.ParseIntoArray(Columns, TEXT(" "), true); // Split by space or tab

		TArray<int32> Numbers;
		for (const FString& Column : Columns)
		{
			if (Column.IsEmpty())
			{
				continue;
			}

			int32 Number;
			checkf(FDefaultValueHelper::ParseInt(Column, Number), TEXT("Failed to parse number: %s"), *Column);

			Numbers.Add(Number);
		}
		Matrix.Add(Numbers);
	}

	int32 SafeRowCount = 0;
	for (TArray<int32> Row : Matrix)
	{
		bool IsIncreasing = Row[0] < Row[1];
		bool IsSafe = true;
		for (int32 i = 1; i < Row.Num(); i++)
		{
			const int32 d = Row[i] - Row[i - 1];
			if (FMath::Abs(d) < 1 ||
				3 < FMath::Abs(d))
			{
				IsSafe = false;
				break;
			}
			if (IsIncreasing
				? d <= 0
				: 0 <= d)
			{
				IsSafe = false;
				break;
			}
		}
		if (IsSafe)
		{
			SafeRowCount++;
		}
		else
		{
			for (int32 SkipIndex = 0; SkipIndex < Row.Num(); SkipIndex++)
			{
				TArray<int32> NewRow;
				for (int32 i = 0; i < Row.Num(); i++)
				{
					if (i == SkipIndex)
					{
						continue;
					}
					NewRow.Add(Row[i]);
				}

				IsSafe = true;
				IsIncreasing = NewRow[0] < NewRow[1];
				for (int32 i = 1; i < NewRow.Num(); i++)
				{
					const int32 d = NewRow[i] - NewRow[i - 1];
					if (FMath::Abs(d) < 1 ||
						3 < FMath::Abs(d))
					{
						IsSafe = false;
						break;
					}
					if (IsIncreasing
						? d <= 0
						: 0 <= d)
					{
						IsSafe = false;
						break;
					}
				}
				if (IsSafe)
				{
					SafeRowCount++;
					break;
				}
			}
		}
	}

	return FString::FromInt(SafeRowCount);
}
