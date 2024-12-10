#include "Task101.h"

#include "InputCoreTypes.h"
#include "Misc/DefaultValueHelper.h"
#include "Misc/FileHelper.h"

DECLARE_LOG_CATEGORY_CLASS(LogTask, All, All);

FString FTask101::Run(const FString& InputFileName)
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

	int32 Result = 0;
	TSet<FIntPoint> Points;
	for (int32 y = 0; y < Matrix.Num(); y++)
	{
		const TArray<uint8>& Row = Matrix[y];
		for (int32 x = 0; x < Row.Num(); x++)
		{
			if (Row[x] == 0)
			{
				Points.Empty();
				GetScore(Matrix, FIntPoint(x, y), -1, Points);
				Result += Points.Num();
			}
		}
	}

	return FString::FromInt(Result);
}

void FTask101::GetScore(const TArray<TArray<uint8>>& Matrix, const FIntPoint Position, const int8 PrevValue, TSet<FIntPoint>& Points)
{
	if (!Matrix.IsValidIndex(Position.Y))
	{
		return;
	}

	if (!Matrix[Position.Y].IsValidIndex(Position.X))
	{
		return;
	}

	const uint8 Value = Matrix[Position.Y][Position.X];
	if (PrevValue + 1 != Value)
	{
		return;
	}

	if (Value == 9)
	{
		Points.Add(Position);
		return;
	}

	const FIntPoint Up = Position + FIntPoint(0, -1);
	GetScore(Matrix, Up, Value, Points);

	const FIntPoint Down = Position + FIntPoint(0, +1);
	GetScore(Matrix, Down, Value, Points);

	const FIntPoint Left = Position + FIntPoint(-1, 0);
	GetScore(Matrix, Left, Value, Points);

	const FIntPoint Right = Position + FIntPoint(+1, 0);
	GetScore(Matrix, Right, Value, Points);
}
