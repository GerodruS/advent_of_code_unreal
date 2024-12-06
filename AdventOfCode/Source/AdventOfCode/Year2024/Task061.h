#pragma once

#include "CoreMinimal.h"

class FTask061
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

};
