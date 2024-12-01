$EngineDir = "C:/Games/Epic Games/UE_5.4"
$ProjectName = "AdventOfCode"
$ProjectDir = "C:/Docs/Code/advent_of_code_unreal/$ProjectName"

$BuildGraphScript = "$ProjectDir/BuildGraph/AdventOfCode.xml"
$BuildGraphTarget = "BuildAndRunCommandlet"

& clear
& "$EngineDir/Engine/Build/BatchFiles/RunUAT.bat" BuildGraph -script="$BuildGraphScript" -Target="$BuildGraphTarget" -set:ProjectRoot="$ProjectDir" -set:ProjectName="$ProjectName" -verbose
