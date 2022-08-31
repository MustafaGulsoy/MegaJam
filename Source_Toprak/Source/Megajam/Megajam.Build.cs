// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Megajam : ModuleRules
{
	public Megajam(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "Niagara" });
	}
}
