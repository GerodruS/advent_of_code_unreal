#include "Task182.h"

#include "InputCoreTypes.h"
#include "Containers/Queue.h"
#include "Misc/DefaultValueHelper.h"
#include "Misc/FileHelper.h"

DECLARE_LOG_CATEGORY_CLASS(LogTask, All, All);

FString FTask182::Run(const FString& InputFileName)
{
	FString FileContent;
	checkf(FFileHelper::LoadFileToString(FileContent, *InputFileName), TEXT("Failed to read the file: '%s'"), *InputFileName);

	FIntPoint Size = FIntPoint::ZeroValue;
	TArray<FIntPoint> BlocksArray;
	{
		TArray<FString> Lines;
		FileContent.ParseIntoArrayLines(Lines, false);
		for (int32 y = 0; y < Lines.Num(); y++)
		{
			const FString& Line = Lines[y];

			TArray<FString> Columns;
			Line.ParseIntoArray(Columns, TEXT(","), true);

			int32 X;
			checkf(FDefaultValueHelper::ParseInt(Columns[0], X), TEXT("Failed to parse Left number: '%s'. Line='%s'"), *Columns[0], *Line);

			int32 Y;
			checkf(FDefaultValueHelper::ParseInt(Columns[1], Y), TEXT("Failed to parse Right number: '%s'. Line='%s'"), *Columns[1], *Line);

			BlocksArray.Add(FIntPoint(X, Y));

			Size.X = FMath::Max(Size.X, X);
			Size.Y = FMath::Max(Size.Y, Y);
		}
	}

	TSet<FIntPoint> Blocks;
	for (FIntPoint Block : BlocksArray)
	{
		Blocks.Add(Block);

		int32 Result = 0;
		TSet<FIntPoint> Visited;
		TQueue<TPair<FIntPoint, int32>> Queue;

		Queue.Enqueue(TPair<FIntPoint, int32>(FIntPoint::ZeroValue, 0));
		while (!Queue.IsEmpty())
		{
			TPair<FIntPoint, int32> Element;
			Queue.Dequeue(Element);

			const FIntPoint Position = Element.Get<0>();
			const int32 Score = Element.Get<1>();

			if (Position == Size)
			{
				Result = Score;
				break;
			}

			if (Position.X < 0 || Size.X < Position.X ||
				Position.Y < 0 || Size.Y < Position.Y)
			{
				continue;
			}

			if (Blocks.Contains(Position))
			{
				continue;
			}

			if (Visited.Contains(Position))
			{
				continue;
			}

			Visited.Add(Position);
			Queue.Enqueue(TPair<FIntPoint, int32>(Position + FIntPoint(+1, +0), Score + 1));
			Queue.Enqueue(TPair<FIntPoint, int32>(Position + FIntPoint(+0, +1), Score + 1));
			Queue.Enqueue(TPair<FIntPoint, int32>(Position + FIntPoint(-1, +0), Score + 1));
			Queue.Enqueue(TPair<FIntPoint, int32>(Position + FIntPoint(+0, -1), Score + 1));
		}

		if (Result == 0)
		{
			return FString::Format(TEXT("{0},{1}"), { Block.X, Block.Y });
		}
	}

	return "--";
}
