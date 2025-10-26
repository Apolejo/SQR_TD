// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class SQR_TDEditor : ModuleRules
{
	public SQR_TDEditor(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { 
			"Core", 
			"CoreUObject", 
			"Engine", 
			"UnrealEd",
			"SQR_TD"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { 
			"Slate", 
			"SlateCore",
			"ToolMenus",
			"EditorStyle",
			"EditorWidgets",
			"PropertyEditor",
			"DataAssetEditor"
		});
	}
}
