// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class AdventureGame : ModuleRules
{
	public AdventureGame(ReadOnlyTargetRules Target) : base(Target)
	{
        PrivatePCHHeaderFile = "AsaiMaki_TPGame.h";

		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
        
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "GameplayAbilities", "GameplayTasks", "GameplayTags" });
	}
}
