#include "AdventOfCodeCommandlet.h"

#include "AdventOfCode/Year2024/Task011.h"
#include "AdventOfCode/Year2024/Task012.h"
#include "AdventOfCode/Year2024/Task021.h"
#include "AdventOfCode/Year2024/Task022.h"
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

	const FString Task0111 = "01_1_1.txt";
	Compare(Task0111, FTask011::Run(InputFolder / Task0111), LoadFile(OutputFolder / Task0111));

	const FString Task0112 = "01_1_2.txt";
	Compare(Task0112, FTask011::Run(InputFolder / Task0112),LoadFile(OutputFolder / Task0112));

	const FString Task0121 = "01_2_1.txt";
	Compare(Task0121, FTask012::Run(InputFolder / Task0121),LoadFile(OutputFolder / Task0121));

	const FString Task0122 = "01_2_2.txt";
	Compare(Task0122, FTask012::Run(InputFolder / Task0122),LoadFile(OutputFolder / Task0122));

	const FString Task0211 = "02_1_1.txt";
	Compare(Task0211, FTask021::Run(InputFolder / Task0211),LoadFile(OutputFolder / Task0211));

	const FString Task0212 = "02_1_2.txt";
	Compare(Task0212, FTask021::Run(InputFolder / Task0212),LoadFile(OutputFolder / Task0212));

	const FString Task0221 = "02_2_1.txt";
	Compare(Task0221, FTask022::Run(InputFolder / Task0221),LoadFile(OutputFolder / Task0221));

	const FString Task0222 = "02_2_2.txt";
	Compare(Task0222, FTask022::Run(InputFolder / Task0222),LoadFile(OutputFolder / Task0222));

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
