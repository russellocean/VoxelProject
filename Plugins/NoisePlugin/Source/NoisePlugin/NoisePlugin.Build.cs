// Copyright 2018 Yaki Studios, Inc. All Rights Reserved.

using System.IO;
using UnrealBuildTool;

public class NoisePlugin : ModuleRules
{
	public NoisePlugin(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicIncludePaths.Add(Path.Combine(ModuleDirectory, "Public"));
		PrivateIncludePaths.Add(Path.Combine(ModuleDirectory, "Private"));

		PublicDependencyModuleNames.AddRange(
			new[]
			{
				"Core"
				// ... add other public dependencies that you statically link with here ...
			}
		);


		PrivateDependencyModuleNames.AddRange(
			new[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore"
				// ... add private dependencies that you statically link with here ...	
			}
		);


		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				// ... add any modules that your module loads dynamically here ...
			}
		);
	}
}