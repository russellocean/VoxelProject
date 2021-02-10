// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class ProceduralProjectTarget : TargetRules
{
	public ProceduralProjectTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		ExtraModuleNames.Add("ProceduralProject");
	}
}