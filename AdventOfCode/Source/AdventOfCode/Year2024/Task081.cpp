#include "Task081.h"

#include "InputCoreTypes.h"
#include "Misc/DefaultValueHelper.h"
#include "Misc/FileHelper.h"

DECLARE_LOG_CATEGORY_CLASS(LogTask, All, All);

FString FTask081::Run(const FString& InputFileName)
{
	FString FileContent;
	checkf(FFileHelper::LoadFileToString(FileContent, *InputFileName), TEXT("Failed to read the file: '%s'"), *InputFileName);

	TArray<TArray<uint8>> Matrix;
	{
		TArray<FString> Lines;
		FileContent.ParseIntoArrayLines(Lines, false);
		for (int32 y = 0; y < Lines.Num(); y++)
		{
			TArray<uint8> Array;
			FTCHARToUTF8 Converter(*Lines[y]);
			Array.Append(reinterpret_cast<const uint8*>(Converter.Get()), Converter.Length());
			Matrix.Add(Array);
		}
	}

	TSet<FIntPoint> Points;

	TMap<uint8, TArray<FIntPoint>> SymbolToPositions;
	for (int32 y = 0; y < Matrix.Num(); y++)
	{
		for (int32 x = 0; x < Matrix[y].Num(); x++)
		{
			const FIntPoint PositionA = FIntPoint(x, y);
			const uint8 Symbol = Matrix[y][x];
			if (Symbol != StaticCast<uint8>('.'))
			{
				TArray<FIntPoint>* Positions = SymbolToPositions.Find(Symbol);
				if (Positions == nullptr)
				{
					TArray<FIntPoint> P;
					P.Add(FIntPoint(x, y));
					SymbolToPositions.Add(Symbol, P);
				}
				else
				{
					for (const FIntPoint& PositionB : *Positions)
					{
						const FIntPoint D = PositionB - PositionA;
						const FIntPoint A = PositionA - D;
						if (Matrix.IsValidIndex(A.Y) && Matrix[A.Y].IsValidIndex(A.X))
						{
							Points.Add(A);
						}
						const FIntPoint B = PositionB + D;
						if (Matrix.IsValidIndex(B.Y) && Matrix[B.Y].IsValidIndex(B.X))
						{
							Points.Add(B);
						}
						// UE_LOG(LogTask, Display, TEXT("[TEST] %d %s %s d=%s a=%s b=%s"), Result, *PositionA.ToString(), *PositionB.ToString(), *D.ToString(), *A.ToString(), *B.ToString());
					}
					Positions->Add(FIntPoint(x, y));
				}
			}
		}
	}

	return FString::FromInt(Points.Num());
}
