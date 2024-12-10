#pragma once

#include "CoreMinimal.h"

class FTask101
{
public:
	static FString Run(const FString& InputFileName);

private:
	static void GetScore(const TArray<TArray<uint8>>& Matrix, const FIntPoint StartPosition, const int8 PrevValue, TSet<FIntPoint>& Points);

};
