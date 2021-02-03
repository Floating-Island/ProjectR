// Fill out your copyright notice in the Description page of Project Settings.


#if WITH_DEV_AUTOMATION_TESTS


#include "RaceStageTest.h"

#include "GameMode/RaceStages/RaceStage.h"
#include "Commands/RaceStageTestCommands.h"
#include "Commands/CommonPIECommands.h"
#include "Mocks/RaceStageMOCK.h"

#include "Tests/AutomationEditorCommon.h"



bool FARaceStageIsntNullWhenInstantiatedTest::RunTest(const FString& Parameters)
{
	ARaceStage* testRaceStage = NewObject<ARaceStage>();
	TestNotNull(TEXT("The race stage shouldn't be null after instantiating it."), testRaceStage);

	return true;
}


bool FARaceStageNextStageReturnsItselfTest::RunTest(const FString& Parameters)
{
	ARaceStage* testRaceStage = NewObject<ARaceStage>();
	TestTrue(TEXT("The race stage should return itself when calling nextStage."), testRaceStage->nextStage() == testRaceStage);

	return true;
}


bool FARaceStageSubscribesRaceModeToStageEndedEventTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld-RaceGameModeMOCK");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	UClass* raceStageClass = ARaceStageMOCK::StaticClass();
	ADD_LATENT_AUTOMATION_COMMAND(FSpawnInPIEAnActorOfClass(raceStageClass, FTransform()));

	ADD_LATENT_AUTOMATION_COMMAND(FCheckRaceModeSubscribed(this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}

#endif //WITH_DEV_AUTOMATION_TESTS