#include "Task061.h"

#include "Misc/DefaultValueHelper.h"
#include "Misc/FileHelper.h"

DECLARE_LOG_CATEGORY_CLASS(LogTask, All, All);

FString FTask061::Run(const FString& InputFileName)
{
	FString FileContent;
	checkf(FFileHelper::LoadFileToString(FileContent, *InputFileName), TEXT("Failed to read the file: '%s'"), *InputFileName);

	TArray<TArray<uint8>> Map;
	FIntPoint StartPosition(INDEX_NONE, INDEX_NONE);
	{
		TArray<FString> Lines;
		FileContent.ParseIntoArrayLines(Lines, false);
		for (int32 y = 0; y < Lines.Num(); y++)
		{
			TArray<uint8> Array;
			FTCHARToUTF8 Converter(*Lines[y]);
			Array.Append(reinterpret_cast<const uint8*>(Converter.Get()), Converter.Length());
			Map.Add(Array);

			const int32 x = Array.Find('^');
			if (x != INDEX_NONE)
			{
				StartPosition = FIntPoint(x, y);
			}
		}
	}
	checkf(StartPosition.X != INDEX_NONE && StartPosition.Y != INDEX_NONE, TEXT("StartPosition not found!"));
	checkf(0 < Map.Num(), TEXT("Map is empty!"));
	checkf(0 < Map[0].Num(), TEXT("Map row is empty!"));

	FIntPoint Position = StartPosition;
	TSet<FIntPoint> Points;

	EDirection Direction = EDirection::Up;
	while (Map.IsValidIndex(Position.Y) &&
		   Map[Position.Y].IsValidIndex(Position.X))
	{
		FIntPoint Delta;
		switch (Direction)
		{
			case EDirection::Up:
				Delta = FIntPoint(+0, -1);
				break;
			case EDirection::Right:
				Delta = FIntPoint(+1, +0);
				break;
			case EDirection::Down:
				Delta = FIntPoint(+0, +1);
				break;
			case EDirection::Left:
				Delta = FIntPoint(-1, +0);
				break;
		}

		Points.Add(Position);
		const FIntPoint NextPosition = Position + Delta;
		if (Map.IsValidIndex(NextPosition.Y) &&
		    Map[NextPosition.Y].IsValidIndex(NextPosition.X) &&
		    Map[NextPosition.Y][NextPosition.X] == StaticCast<uint8>('#'))
		{
			switch (Direction)
			{
				case EDirection::Up:
					Direction = EDirection::Right;
					break;
				case EDirection::Right:
					Direction = EDirection::Down;
					break;
				case EDirection::Down:
					Direction = EDirection::Left;
					break;
				case EDirection::Left:
					Direction = EDirection::Up;
					break;
			}

			switch (Direction)
			{
				case EDirection::Up:
					Delta = FIntPoint(+0, -1);
					break;
				case EDirection::Right:
					Delta = FIntPoint(+1, +0);
					break;
				case EDirection::Down:
					Delta = FIntPoint(+0, +1);
					break;
				case EDirection::Left:
					Delta = FIntPoint(-1, +0);
					break;
			}

			Position += Delta;
		}
		else
		{
			Position = NextPosition;
		}
	}

	const int32 Result = Points.Num();
	return FString::FromInt(Result);
}
