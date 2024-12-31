#include "Task241.h"

#include "InputCoreTypes.h"
#include "Misc/DefaultValueHelper.h"
#include "Misc/FileHelper.h"

DECLARE_LOG_CATEGORY_CLASS(LogTask, All, All);

FString FTask241::Run(const FString& InputFileName)
{
	FString FileContent;
	checkf(FFileHelper::LoadFileToString(FileContent, *InputFileName), TEXT("Failed to read the file: '%s'"), *InputFileName);

	TMap<FString, bool> Vars;
	TMap<FString, TTuple<FString, FString, uint8>> Exprs;
	{
		TArray<FString> Lines;
		FileContent.ParseIntoArrayLines(Lines, false);

		for (FString Line : Lines)
		{
			if (Line.Contains(": "))
			{
				TArray<FString> Columns;
				Line.ParseIntoArray(Columns, TEXT(": "), true);
				FString Key = Columns[0];
				FString Value = Columns[1];
				Vars.Add(Key, Value == "1");
			}
			else if (!Line.IsEmpty())
			{
				TArray<FString> Columns;
				Line.ParseIntoArray(Columns, TEXT(" -> "), true);
				FString Key = Columns[1];
				FString Expr = Columns[0];
				if (Expr.Contains(" AND "))
				{
					Columns.Empty();
					Expr.ParseIntoArray(Columns, TEXT(" AND "), true);
					Exprs.Add(Key, TTuple<FString, FString, uint8>(Columns[0], Columns[1], 0));
				}
				else if (Expr.Contains(" OR "))
				{
					Columns.Empty();
					Expr.ParseIntoArray(Columns, TEXT(" OR "), true);
					Exprs.Add(Key, TTuple<FString, FString, uint8>(Columns[0], Columns[1], 1));
				}
				else // if (Expr.Contains(" XOR "))
				{
					Columns.Empty();
					Expr.ParseIntoArray(Columns, TEXT(" XOR "), true);
					Exprs.Add(Key, TTuple<FString, FString, uint8>(Columns[0], Columns[1], 2));
				}
			}
		}
	}

	int64 Result = 0;

	for (int32 Index = 0; ; Index++)
	{
		FString Key = FString::Printf(TEXT("z%02d"), Index);
		if (!Exprs.Contains(Key))
		{
			break;
		}

		const bool Value = Get(Key, Vars, Exprs);
		if (Value)
		{
			Result = Result | (1ULL << Index);
		}
	}

	return LexToString(Result);
}

bool FTask241::Get(
	const FString& Key,
	TMap<FString, bool>& Vars,
	const TMap<FString, TTuple<FString, FString, uint8>>& Exprs)
{
	const bool* const ValuePtr = Vars.Find(Key);
	if (ValuePtr != nullptr)
	{
		return *ValuePtr;
	}

	const TTuple<FString, FString, uint8>& Expr = Exprs[Key];
	const bool Left = Get(Expr.Get<0>(), Vars, Exprs);
	const bool Right = Get(Expr.Get<1>(), Vars, Exprs);

	bool Result;
	switch (Expr.Get<2>())
	{
		case 0:
			Result = Left & Right;
			break;
		case 1:
			Result = Left | Right;
			break;
		default:
			Result = Left ^ Right;
			break;
	}

	Vars.Add(Key, Result);
	return Result;
}
