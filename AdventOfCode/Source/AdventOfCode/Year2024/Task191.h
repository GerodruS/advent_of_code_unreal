#pragma once

#include "CoreMinimal.h"

class FTask191
{
public:
	static FString Run(const FString& InputFileName);

private:
	static bool IsPossible(
		const FString& String,
		const int32 StartIndex,
		const TMap<TCHAR, TArray<FString>>& SubstringsMap);

};
