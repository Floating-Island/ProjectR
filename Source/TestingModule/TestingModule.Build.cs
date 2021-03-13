using UnrealBuildTool;

public class TestingModule : ModuleRules
{
    public TestingModule(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
        PublicDependencyModuleNames.AddRange(new string[] {
            "Core", 
            "CoreUObject", 
            "Engine", 
            "InputCore", 
            "UnrealEd", 
            "UMG", 
            "OnlineSubsystem", 
            "OnlineSubsystemUtils"
        });
        PrivateDependencyModuleNames.AddRange(
            new string[] 
            {
                "ProjectR", 
                "Slate", 
                "SlateCore"
            });

        DynamicallyLoadedModuleNames.Add("OnlineSubsystemNull");
    }
}