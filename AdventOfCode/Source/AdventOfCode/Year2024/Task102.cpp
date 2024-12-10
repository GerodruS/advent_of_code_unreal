#include "Task102.h"

#include "InputCoreTypes.h"
#include "Misc/DefaultValueHelper.h"
#include "Misc/FileHelper.h"

DECLARE_LOG_CATEGORY_CLASS(LogTask, All, All);

FString FTask102::Run(const FString& InputFileName)
{
	FString FileContent;
	checkf(FFileHelper::LoadFileToString(FileContent, *InputFileName), TEXT("Failed to read the file: '%s'"), *InputFileName);

	TArray<TArray<uint8>> Matrix;
	{
		TArray<FString> Lines;
		FileContent.ParseIntoArrayLines(Lines, false);
		for (int32 y = 0; y < Lines.Num(); y++)
		{
			const FString& Line = Lines[y];

			TArray<uint8> Row;
			for (int32 x = 0; x < Line.Len(); x++)
			{
				const uint8 Value = StaticCast<uint8>(Line[x]) - StaticCast<uint8>('0');
				Row.Add(Value);
			}
			Matrix.Add(Row);
		}
	}

	uint32 Result = 0;
	for (int32 y = 0; y < Matrix.Num(); y++)
	{
		const TArray<uint8>& Row = Matrix[y];
		for (int32 x = 0; x < Row.Num(); x++)
		{
			if (Row[x] == 0)
			{
				const uint32 Score = GetScore(Matrix, FIntPoint(x, y), -1);
				Result += Score;
			}
		}
	}

	return FString::FromInt(Result);
}

uint32 FTask102::GetScore(const TArray<TArray<uint8>>& Matrix, const FIntPoint Position, const int8 PrevValue)
{
	if (!Matrix.IsValidIndex(Position.Y))
	{
		return 0;
	}

	if (!Matrix[Position.Y].IsValidIndex(Position.X))
	{
		return 0;
	}

	const uint8 Value = Matrix[Position.Y][Position.X];
	if (PrevValue + 1 != Value)
	{
		return 0;
	}

	if (Value == 9)
	{
		return 1;
	}

	int32 Score = 0;

	const FIntPoint Up = Position + FIntPoint(0, -1);
	Score += GetScore(Matrix, Up, Value);

	const FIntPoint Down = Position + FIntPoint(0, +1);
	Score += GetScore(Matrix, Down, Value);

	const FIntPoint Left = Position + FIntPoint(-1, 0);
	Score += GetScore(Matrix, Left, Value);

	const FIntPoint Right = Position + FIntPoint(+1, 0);
	Score += GetScore(Matrix, Right, Value);

	return Score;
}
