// Fill out your copyright notice in the Description page of Project Settings.


#if WITH_DEV_AUTOMATION_TESTS

#include "ProjectRGameStateTest.h"
#include "Commands/ProjectRGameStateTestCommands.h"
#include "GameState/ProjectRGameState.h"
#include "Tests/AutomationEditorCommon.h"
#include "Commands/CommonPIECommands.h"





bool FAProjectRGameStateIsntNullWhenInstantiatedTest::RunTest(const FString& Parameters)
{
	AProjectRGameState* testGameState = NewObject<AProjectRGameState>();
	TestNotNull(TEXT("The game state shouldn't be null after instantiating it."), testGameState);

	return true;
}


bool FAProjectRGameStateUpdateAnnouncerWithUpdatesTextFromSubscribedAnnouncerUITest::RunTest(const FString& Parameters)
{
		establishInitialMapDirectoryTo(FString("/Game/Tests/TestMaps/VoidWorld-AnnouncerUIContainer"));
	establishTestMessageTo(FString("The projectR game state should update subscribed announcerUIs displayText when calling updateAnnouncerWith."));
	establishTickLimitTo(3);

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(retrieveInitialMapDirectory()));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	ADD_LATENT_AUTOMATION_COMMAND(FSpawnGameModeDefaultPawn);

	ADD_LATENT_AUTOMATION_COMMAND(FCheckGameStateUpdatesAnnouncerUIDisplayText(nullptr, this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}






#endif //WITH_DEV_AUTOMATION_TESTS