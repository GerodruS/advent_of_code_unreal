#include "Task011.h"

#include "Misc/DefaultValueHelper.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"

DECLARE_LOG_CATEGORY_CLASS(LogTask, All, All);

FString FTask011::Run(const FString& InputFileName)
{
	const FString FilePath = FPaths::ProjectDir() / TEXT("Input/012.txt");
	FString FileContent;
	checkf(FFileHelper::LoadFileToString(FileContent, *InputFileName), TEXT("Failed to read the file: '%s'"), *InputFileName);

	TArray<FString> Lines;
	FileContent.ParseIntoArrayLines(Lines);

	TArray<int32> LeftColumn;
	TArray<int32> RightColumn;
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

		LeftColumn.Add(Numbers[0]);
		RightColumn.Add(Numbers[1]);
	}

	LeftColumn.Sort();
	RightColumn.Sort();

	int32 Sum = 0;
	for (int32 i = 0; i < LeftColumn.Num(); i++)
	{
		const int32 d = FMath::Abs(LeftColumn[i] - RightColumn[i]);
		Sum += d;
	}

	return FString::FromInt(Sum);
}
