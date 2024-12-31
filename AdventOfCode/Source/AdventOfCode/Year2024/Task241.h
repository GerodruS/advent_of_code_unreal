#pragma once

#include "CoreMinimal.h"

class FTask241
{
public:
	static FString Run(const FString& InputFileName);

private:
	static bool Get(
		const FString& Key,
		TMap<FString, bool>& Vars,
		const TMap<FString, TTuple<FString, FString, uint8>>& Exprs);

};
