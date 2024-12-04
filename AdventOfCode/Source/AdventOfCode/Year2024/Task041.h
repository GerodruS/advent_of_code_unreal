#pragma once

#include "CoreMinimal.h"

class FTask041
{
public:
	static FString Run(const FString& InputFileName);

private:
	static bool Check(
		const uint32 X, const uint32 Y,
		const uint32 Dx, const uint32 Dy,
		const TArray<uint8>& Array,
		const TArray<TArray<uint8>>& Matrix);
};
