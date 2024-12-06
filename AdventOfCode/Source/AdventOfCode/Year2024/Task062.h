#pragma once

#include "CoreMinimal.h"

class FTask062
{
public:
	static FString Run(const FString& InputFileName);

private:
	enum class EDirection : uint8
	{
		Up,
		Right,
		Down,
		Left,
	};

	static bool IsLoop(const TArray<TArray<uint8>>& Map, const FIntPoint StartPosition, const EDirection StartDirection);
};
