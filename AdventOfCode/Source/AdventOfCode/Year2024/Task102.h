#pragma once

#include "CoreMinimal.h"

class FTask102
{
public:
	static FString Run(const FString& InputFileName);

private:
	static uint32 GetScore(const TArray<TArray<uint8>>& Matrix, const FIntPoint Position, const int8 PrevValue);

};
