#include "Task041.h"

#include "Misc/DefaultValueHelper.h"
#include "Misc/FileHelper.h"

DECLARE_LOG_CATEGORY_CLASS(LogTask, All, All);

FString FTask041::Run(const FString& InputFileName)
{
	FString FileContent;
	checkf(FFileHelper::LoadFileToString(FileContent, *InputFileName), TEXT("Failed to read the file: '%s'"), *InputFileName);

	const FString TargetString = TEXT("XMAS");
	TArray<uint8> TargetArray;
	{
		const FTCHARToUTF8 Converter(*TargetString);
		TargetArray.Append(reinterpret_cast<const uint8*>(Converter.Get()), Converter.Length());
	}

	TArray<TArray<uint8>> Matrix;
	{
		TArray<FString> Lines;
		FileContent.ParseIntoArrayLines(Lines);
		for (const FString& Line : Lines)
		{
			TArray<uint8> Array;
			FTCHARToUTF8 Converter(*Line);
			Array.Append(reinterpret_cast<const uint8*>(Converter.Get()), Converter.Length());
			Matrix.Add(Array);
		}
	}

	int32 Result = 0;

	const int32 RowCount = Matrix.Num();
	if (RowCount < 1)
	{
		return TEXT("0");
	}

	const int32 ColumnCount = Matrix[0].Num();
	for (int32 y = 0; y < RowCount; y++)
	{
		for (int32 x = 0; x < ColumnCount; x++)
		{
			if (TargetArray[0] != Matrix[y][x])
			{
				continue;
			}

			if (Check(x, y, +1, +0, TargetArray, Matrix))
			{
				Result++;
			}
			if (Check(x, y, -1, +0, TargetArray, Matrix))
			{
				Result++;
			}
			if (Check(x, y, +0, +1, TargetArray, Matrix))
			{
				Result++;
			}
			if (Check(x, y, +0, -1, TargetArray, Matrix))
			{
				Result++;
			}
			if (Check(x, y, +1, +1, TargetArray, Matrix))
			{
				Result++;
			}
			if (Check(x, y, +1, -1, TargetArray, Matrix))
			{
				Result++;
			}
			if (Check(x, y, -1, +1, TargetArray, Matrix))
			{
				Result++;
			}
			if (Check(x, y, -1, -1, TargetArray, Matrix))
			{
				Result++;
			}
		}
	}

	return FString::FromInt(Result);
}

bool FTask041::Check(
	const uint32 X, const uint32 Y,
	const uint32 Dx, const uint32 Dy,
	const TArray<uint8>& Array,
	const TArray<TArray<uint8>>& Matrix)
{
	uint32 x = X;
	uint32 y = Y;

	for (int32 i = 0; i < Array.Num(); i++)
	{
		if (!Matrix.IsValidIndex(y))
		{
			return false;
		}

		if (!Matrix[y].IsValidIndex(x))
		{
			return false;
		}

		if (Array[i] != Matrix[y][x])
		{
			return false;
		}

		x += Dx;
		y += Dy;
	}

	return true;
}
