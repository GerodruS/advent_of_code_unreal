#include "Task012.h"

#include "CoreMinimal.h"
#include "Compute/AgentMessage.h"
#include "Misc/DefaultValueHelper.h"
#include "Misc/FileHelper.h"

DECLARE_LOG_CATEGORY_CLASS(LogTask, All, All);

FString FTask012::Run(const FString& InputFileName)
{
	FString FileContent;
	checkf(FFileHelper::LoadFileToString(FileContent, *InputFileName), TEXT("Failed to read the file: '%s'"), *InputFileName);

	TArray<FString> Lines;
	FileContent.ParseIntoArrayLines(Lines);

	TArray<int32> LeftColumn;
	TMap<int32, int32> RightColumn;
	for (const FString& Line : Lines)
	{
		TArray<FString> Columns;
		Line.ParseIntoArray(Columns, TEXT(" "), true);

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

		LeftColumn.Add(Numbers[0]);
		RightColumn.FindOrAdd(Numbers[1])++;
	}

	int32 Sum = 0;
	for (const int32 Value : LeftColumn)
	{
		const int32* const CountPtr = RightColumn.Find(Value);
		const int32 Count = CountPtr ? *CountPtr : 0;
		Sum += Value * Count;
	}

	return FString::FromInt(Sum);
}
