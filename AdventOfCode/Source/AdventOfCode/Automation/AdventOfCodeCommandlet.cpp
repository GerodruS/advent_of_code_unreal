#include "AdventOfCodeCommandlet.h"

#include "AdventOfCode/Year2024/Task011.h"
#include "AdventOfCode/Year2024/Task012.h"
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
	Compare(FTask011::Run(InputFolder / Task0111), LoadFile(OutputFolder / Task0111));

	const FString Task0112 = "01_1_2.txt";
	Compare(FTask011::Run(InputFolder / Task0112),LoadFile(OutputFolder / Task0112));

	const FString Task0121 = "01_2_1.txt";
	Compare(FTask012::Run(InputFolder / Task0121),LoadFile(OutputFolder / Task0121));

	const FString Task0122 = "01_2_2.txt";
	Compare(FTask012::Run(InputFolder / Task0122),LoadFile(OutputFolder / Task0122));

	return 0; // Return 0 on success
}

void UAdventOfCodeCommandlet::Compare(const FString& A, const FString& B)
{
	ensureAlwaysMsgf(A == B, TEXT("Unexpected result! A='%s' B='%s'"), *A, *B);
}

FString UAdventOfCodeCommandlet::LoadFile(const FString& FileName)
{
	FString FileContent;
	checkf(FFileHelper::LoadFileToString(FileContent, *FileName), TEXT("Failed to read the file: '%s'"), *FileName);
	return FileContent;
}
