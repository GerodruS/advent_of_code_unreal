#pragma once

#include "CoreMinimal.h"
#include "Commandlets/Commandlet.h"
#include "AdventOfCodeCommandlet.generated.h"

UCLASS()
class ADVENTOFCODE_API UAdventOfCodeCommandlet : public UCommandlet
{
	GENERATED_BODY()

public:
	UAdventOfCodeCommandlet();

	virtual int32 Main(const FString& Params) override;

private:
	static void Compare(const FString& FileName, const FString& A, const FString& B);
	static FString LoadFile(const FString& FileName);

};
