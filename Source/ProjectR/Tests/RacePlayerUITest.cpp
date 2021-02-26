// Fill out your copyright notice in the Description page of Project Settings.


#if WITH_DEV_AUTOMATION_TESTS


#include "RacePlayerUITest.h"
#include "UI/RacePlayerUI.h"
#include "Tests/AutomationEditorCommon.h"
#include "Commands/CommonPIECommands.h"
#include "Commands/RacePlayerUITestCommands.h"


bool FARacePlayerUIIsntNullWhenInstantiatedTest::RunTest(const FString& Parameters)
{
	URacePlayerUI* testPlayerUI = NewObject<URacePlayerUI>();

	TestNotNull(TEXT("Shouldn't be null when instantiated"), testPlayerUI);
	
	return true;
}


bool FARacePlayerUISetTotalLapsToChangesTotalLapsTextTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld-RacePlayerUIContainer");
	establishTestMessageTo(FString("The race player UI should change its totalLapsText when calling setTotalLaps."));
	establishTickLimitTo(3);

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	ADD_LATENT_AUTOMATION_COMMAND(FSpawnGameModeDefaultPawn);
	ADD_LATENT_AUTOMATION_COMMAND(FCheckARacePlayerUIChangesTotalLapsText(this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FARacePlayerUISetTotalLapsChangesTotalLapsTextOnceTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld-RacePlayerUIContainer");
	establishTestMessageTo(FString("The race player UI should change its totalLapsText when calling setTotalLaps, but only the first time."));
	establishTickLimitTo(3);

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	ADD_LATENT_AUTOMATION_COMMAND(FSpawnGameModeDefaultPawn);
	ADD_LATENT_AUTOMATION_COMMAND(FCheckARacePlayerUIChangesTotalLapsTextOnce(this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}




#endif //WITH_DEV_AUTOMATION_TESTS