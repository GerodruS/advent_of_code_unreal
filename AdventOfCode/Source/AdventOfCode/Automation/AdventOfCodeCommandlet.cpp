#include "AdventOfCodeCommandlet.h"

#include "AdventOfCode/Year2024/Task011.h"
#include "AdventOfCode/Year2024/Task012.h"
#include "AdventOfCode/Year2024/Task021.h"
#include "AdventOfCode/Year2024/Task022.h"
#include "AdventOfCode/Year2024/Task031.h"
#include "AdventOfCode/Year2024/Task032.h"
#include "AdventOfCode/Year2024/Task041.h"
#include "AdventOfCode/Year2024/Task042.h"
#include "Misc/DefaultValueHelper.h"
#include "Misc/Paths.h"
#include "Misc/FileHelper.h"

DECLARE_LOG_CATEGORY_CLASS(LogAdventOfCodeCommandlet, All, All);

UAdventOfCodeCommandlet::UAdventOfCodeCommandlet()
{
	IsServer = false;        // Whether the Commandlet requires a server
	IsClient = false;        // Whether the Commandlet requires a client
	IsEditor = true;         // Whether the Commandlet can run in the editor
	LogToConsole = true;     // Enable console output
}

int32 UAdventOfCodeCommandlet::Main(const FString& Params)
{
	const FString InputFolder = FPaths::ProjectDir() / TEXT("Input/");
	const FString OutputFolder = FPaths::ProjectDir() / TEXT("Output/");
	{
		const FString FileName = "01_1_1.txt";
		Compare(FileName, FTask011::Run(InputFolder / FileName), LoadFile(OutputFolder / FileName));
	}
	{
		const FString FileName = "01_1_2.txt";
		Compare(FileName, FTask011::Run(InputFolder / FileName),LoadFile(OutputFolder / FileName));
	}
	{
		const FString FileName = "01_2_1.txt";
		Compare(FileName, FTask012::Run(InputFolder / FileName),LoadFile(OutputFolder / FileName));
	}
	{
		const FString FileName = "01_2_2.txt";
		Compare(FileName, FTask012::Run(InputFolder / FileName),LoadFile(OutputFolder / FileName));
	}
	{
		const FString FileName = "02_1_1.txt";
		Compare(FileName, FTask021::Run(InputFolder / FileName),LoadFile(OutputFolder / FileName));
	}
	{
		const FString FileName = "02_1_2.txt";
		Compare(FileName, FTask021::Run(InputFolder / FileName),LoadFile(OutputFolder / FileName));
	}
	{
		const FString FileName = "02_2_1.txt";
		Compare(FileName, FTask022::Run(InputFolder / FileName),LoadFile(OutputFolder / FileName));
	}
	{
		const FString FileName = "02_2_2.txt";
		Compare(FileName, FTask022::Run(InputFolder / FileName),LoadFile(OutputFolder / FileName));
	}
	{
		const FString FileName = "03_1_1.txt";
		Compare(FileName, FTask031::Run(InputFolder / FileName),LoadFile(OutputFolder / FileName));
	}
	{
		const FString FileName = "03_1_2.txt";
		Compare(FileName, FTask031::Run(InputFolder / FileName),LoadFile(OutputFolder / FileName));
	}
	{
		const FString FileName = "03_2_1.txt";
		Compare(FileName, FTask032::Run(InputFolder / FileName),LoadFile(OutputFolder / FileName));
	}
	{
		const FString FileName = "03_2_2.txt";
		Compare(FileName, FTask032::Run(InputFolder / FileName),LoadFile(OutputFolder / FileName));
	}
	{
		const FString FileName = "04_1_1.txt";
		Compare(FileName, FTask041::Run(InputFolder / FileName),LoadFile(OutputFolder / FileName));
	}
	{
		const FString FileName = "04_1_2.txt";
		Compare(FileName, FTask041::Run(InputFolder / FileName),LoadFile(OutputFolder / FileName));
	}
	{
		const FString FileName = "04_2_1.txt";
		Compare(FileName, FTask042::Run(InputFolder / FileName),LoadFile(OutputFolder / FileName));
	}
	{
		const FString FileName = "04_2_2.txt";
		Compare(FileName, FTask042::Run(InputFolder / FileName),LoadFile(OutputFolder / FileName));
	}
	return 0; // Return 0 on success
}

void UAdventOfCodeCommandlet::Compare(const FString& FileName, const FString& A, const FString& B)
{
	ensureAlwaysMsgf(A == B, TEXT("Unexpected result! F='%s' A='%s' B='%s'"), *FileName, *A, *B);
}

FString UAdventOfCodeCommandlet::LoadFile(const FString& FileName)
{
	FString FileContent;
	checkf(FFileHelper::LoadFileToString(FileContent, *FileName), TEXT("Failed to read the file: '%s'"), *FileName);
	return FileContent;
}
