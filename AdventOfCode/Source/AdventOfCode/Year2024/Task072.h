#pragma once

#include "CoreMinimal.h"

class FTask072
{
public:
	static FString Run(const FString& InputFileName);

private:
	static bool CanBeTrue(int64 LeftValue, const TArray<int32>& RightValues);

};
