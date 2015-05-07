// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

namespace UnrealBuildTool.Rules
{
	public class HasteEditor : ModuleRules
	{
		public HasteEditor(TargetInfo Target)
		{
			PublicIncludePaths.AddRange(
				new string[] {
					// ... add public include paths required here ...
				}
				);

			PrivateIncludePaths.AddRange(
				new string[] {
					"HasteEditor/Private",
				    "Editor/GraphEditor/Private",
				    "Editor/GraphEditor/Private/KismetNodes",
				    "Editor/GraphEditor/Private/KismetPins",
					// ... add other private include paths required here ...
				}
				);

            PrivateIncludePathModuleNames.AddRange(
                new string[] {
				"Settings",
				"IntroTutorials",
                "AssetTools"
			}
            );

			PublicDependencyModuleNames.AddRange(
				new string[]
				{
					"Core",
					"CoreUObject",
                    "Engine",
                    "Slate",
                    "EditorStyle",
                    "UnrealEd",
				    "KismetWidgets",
                    "GraphEditor",
				    "Kismet",  // for FWorkflowCentricApplication
					// ... add other public dependencies that you statically link with here ...
				}
				);

			PrivateDependencyModuleNames.AddRange(
				new string[]
				{
                    "InputCore",
                    "SlateCore",
				    "RenderCore",
                    "PropertyEditor",
                    "WorkspaceMenuStructure",
                    "LevelEditor",
				    "EditorStyle",
				    "ContentBrowser"
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
}