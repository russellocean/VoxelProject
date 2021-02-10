// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class ProceduralProjectEditorTarget : TargetRules
{
	public ProceduralProjectEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		ExtraModuleNames.Add("ProceduralProject");
	}
}