// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class ProceduralProject : ModuleRules
{
	public ProceduralProject(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new[]
		{
			"Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "ProceduralMeshComponent", "Slate",
			"SlateCore", "NoisePlugin"
		});
	}
}