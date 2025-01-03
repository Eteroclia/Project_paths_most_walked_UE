// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class Paths_most_walked : ModuleRules
{
	public Paths_most_walked(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] {
    			"Core",
    			"CoreUObject",
    			"Engine",
    			"OpenCV",
    			"OpenCVHelper",
    			"InputCore"
  		});

		PrivateDependencyModuleNames.AddRange(new string[] {
    			"Core",
    			"CoreUObject",
    			"Engine",
    			"Renderer",
    			"RenderCore",
    			"RHI",
    			"RHICore",
    			"D3D12RHI",
    			"OpenCV",
    			"OpenCVHelper"
    		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
