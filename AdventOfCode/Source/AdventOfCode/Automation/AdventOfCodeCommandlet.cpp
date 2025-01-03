#include "AdventOfCodeCommandlet.h"

#include "AdventOfCode/Year2024/Task011.h"
#include "AdventOfCode/Year2024/Task012.h"
#include "AdventOfCode/Year2024/Task021.h"
#include "AdventOfCode/Year2024/Task022.h"
#include "AdventOfCode/Year2024/Task031.h"
#include "AdventOfCode/Year2024/Task032.h"
#include "AdventOfCode/Year2024/Task041.h"
#include "AdventOfCode/Year2024/Task042.h"
#include "AdventOfCode/Year2024/Task051.h"
#include "AdventOfCode/Year2024/Task052.h"
#include "AdventOfCode/Year2024/Task061.h"
#include "AdventOfCode/Year2024/Task062.h"
#include "AdventOfCode/Year2024/Task071.h"
#include "AdventOfCode/Year2024/Task072.h"
#include "AdventOfCode/Year2024/Task081.h"
#include "AdventOfCode/Year2024/Task082.h"
#include "AdventOfCode/Year2024/Task101.h"
#include "AdventOfCode/Year2024/Task102.h"
#include "AdventOfCode/Year2024/Task181.h"
#include "AdventOfCode/Year2024/Task182.h"
#include "AdventOfCode/Year2024/Task191.h"
#include "AdventOfCode/Year2024/Task241.h"
#include "AdventOfCode/Year2024/Task251.h"
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
	{
		const FString FileName = "05_1_1.txt";
		Compare(FileName, FTask051::Run(InputFolder / FileName),LoadFile(OutputFolder / FileName));
	}
	{
		const FString FileName = "05_1_2.txt";
		Compare(FileName, FTask051::Run(InputFolder / FileName),LoadFile(OutputFolder / FileName));
	}
	{
		const FString FileName = "05_2_1.txt";
		Compare(FileName, FTask052::Run(InputFolder / FileName),LoadFile(OutputFolder / FileName));
	}
	{
		const FString FileName = "05_2_2.txt";
		Compare(FileName, FTask052::Run(InputFolder / FileName),LoadFile(OutputFolder / FileName));
	}
	{
		const FString FileName = "06_1_1.txt";
		Compare(FileName, FTask061::Run(InputFolder / FileName),LoadFile(OutputFolder / FileName));
	}
	{
		const FString FileName = "06_1_2.txt";
		Compare(FileName, FTask061::Run(InputFolder / FileName),LoadFile(OutputFolder / FileName));
	}
	{
		const FString FileName = "06_2_1.txt";
		Compare(FileName, FTask062::Run(InputFolder / FileName),LoadFile(OutputFolder / FileName));
	}
	{
		const FString FileName = "06_2_2.txt";
		// Compare(FileName, FTask062::Run(InputFolder / FileName),LoadFile(OutputFolder / FileName));
	}
	{
		const FString FileName = "07_1_1.txt";
		Compare(FileName, FTask071::Run(InputFolder / FileName),LoadFile(OutputFolder / FileName));
	}
	{
		const FString FileName = "07_1_2.txt";
		Compare(FileName, FTask071::Run(InputFolder / FileName),LoadFile(OutputFolder / FileName));
	}
	{
		const FString FileName = "07_2_1.txt";
		Compare(FileName, FTask072::Run(InputFolder / FileName),LoadFile(OutputFolder / FileName));
	}
	{
		const FString FileName = "07_2_2.txt";
		Compare(FileName, FTask072::Run(InputFolder / FileName),LoadFile(OutputFolder / FileName));
	}
	{
		const FString FileName = "08_1_1.txt";
		Compare(FileName, FTask081::Run(InputFolder / FileName),LoadFile(OutputFolder / FileName));
	}
	{
		const FString FileName = "08_1_2.txt";
		Compare(FileName, FTask081::Run(InputFolder / FileName),LoadFile(OutputFolder / FileName));
	}
	{
		const FString FileName = "08_2_1.txt";
		Compare(FileName, FTask082::Run(InputFolder / FileName),LoadFile(OutputFolder / FileName));
	}
	{
		const FString FileName = "08_2_2.txt";
		Compare(FileName, FTask082::Run(InputFolder / FileName),LoadFile(OutputFolder / FileName));
	}
	{
		const FString FileName = "10_1_1.txt";
		Compare(FileName, FTask101::Run(InputFolder / FileName),LoadFile(OutputFolder / FileName));
	}
	{
		const FString FileName = "10_1_2.txt";
		Compare(FileName, FTask101::Run(InputFolder / FileName),LoadFile(OutputFolder / FileName));
	}
	{
		const FString FileName = "10_2_1.txt";
		Compare(FileName, FTask102::Run(InputFolder / FileName),LoadFile(OutputFolder / FileName));
	}
	{
		const FString FileName = "10_2_2.txt";
		Compare(FileName, FTask102::Run(InputFolder / FileName),LoadFile(OutputFolder / FileName));
	}
	{
		const FString FileName = "18_1_1.txt";
		Compare(FileName, FTask181::Run(InputFolder / FileName, 12),LoadFile(OutputFolder / FileName));
	}
	{
		const FString FileName = "18_1_2.txt";
		Compare(FileName, FTask181::Run(InputFolder / FileName, 1024),LoadFile(OutputFolder / FileName));
	}
	{
		const FString FileName = "18_2_1.txt";
		Compare(FileName, FTask182::Run(InputFolder / FileName),LoadFile(OutputFolder / FileName));
	}
	{
		const FString FileName = "18_2_2.txt";
		Compare(FileName, FTask182::Run(InputFolder / FileName),LoadFile(OutputFolder / FileName));
	}
	{
		const FString FileName = "19_1_1.txt";
		Compare(FileName, FTask191::Run(InputFolder / FileName),LoadFile(OutputFolder / FileName));
	}
	{
		const FString FileName = "19_1_2.txt";
		Compare(FileName, FTask191::Run(InputFolder / FileName),LoadFile(OutputFolder / FileName));
	}
	{
		const FString FileName = "24_1_1.txt";
		Compare(FileName, FTask241::Run(InputFolder / FileName),LoadFile(OutputFolder / FileName));
	}
	{
		const FString FileName = "24_1_2.txt";
		Compare(FileName, FTask241::Run(InputFolder / FileName),LoadFile(OutputFolder / FileName));
	}
	{
		const FString FileName = "25_1_1.txt";
		Compare(FileName, FTask251::Run(InputFolder / FileName),LoadFile(OutputFolder / FileName));
	}
	{
		const FString FileName = "25_1_2.txt";
		Compare(FileName, FTask251::Run(InputFolder / FileName),LoadFile(OutputFolder / FileName));
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
