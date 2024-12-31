#include "Task251.h"

#include "InputCoreTypes.h"
#include "Misc/DefaultValueHelper.h"
#include "Misc/FileHelper.h"

DECLARE_LOG_CATEGORY_CLASS(LogTask, All, All);

FString FTask251::Run(const FString& InputFileName)
{
	const int32 LineLen = 5;
	const int32 Height = 5;

	FString FileContent;
	checkf(FFileHelper::LoadFileToString(FileContent, *InputFileName), TEXT("Failed to read the file: '%s'"), *InputFileName);

	TArray<TArray<uint8>> Keys;
	TArray<TArray<uint8>> Locks;
	{
		TArray<FString> Lines;
		FileContent.ParseIntoArrayLines(Lines, false);

		TArray<uint8> Key;
		Key.Init(0, LineLen);
		bool WasEmptyLine = true;
		bool IsKey = true;
		for (FString Line : Lines)
		{
			if (Line.IsEmpty())
			{
				for (uint8& Value : Key)
				{
					Value--;
				}
				if (IsKey)
				{
					Keys.Add(Key);
				}
				else
				{
					Locks.Add(Key);
				}
				Key.Empty();
				Key.Init(0, LineLen);
				WasEmptyLine = true;
			}
			else
			{
				for (int32 i = 0; i < LineLen; ++i)
				{
					if (Line[i] == TEXT('#'))
					{
						Key[i]++;
					}
				}
				if (WasEmptyLine)
				{
					IsKey = Line[0] == TEXT('#');
				}
				WasEmptyLine = false;
			}
		}
	}

	int32 Result = 0;

	for (const TArray<uint8>& Key : Keys)
	{
		for (const TArray<uint8>& Lock : Locks)
		{
			bool Fit = true;
			for (int32 i = 0; i < LineLen; ++i)
			{
				if (Height < Key[i] + Lock[i])
				{
					Fit = false;
					break;
				}
			}
			if (Fit)
			{
				Result++;
			}
		}
	}

	return FString::FromInt(Result);
}
