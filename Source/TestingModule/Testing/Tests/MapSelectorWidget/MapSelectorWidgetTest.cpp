// Fill out your copyright notice in the Description page of Project Settings.


#if WITH_DEV_AUTOMATION_TESTS

#include "MapSelectorWidgetTest.h"
#include "UI/MapSelectorWidget.h"
#include "Tests/AutomationEditorCommon.h"
#include "../../Commands/CommonPIECommands.h"
#include "MapSelectorWidgetTestCommands.h"



bool FUMapSelectorWidgetIsntNullWhenInstantiatedTest::RunTest(const FString& Parameters)
{
	UMapSelectorWidget* testSelector = NewObject<UMapSelectorWidget>();

	TestNotNull(TEXT("Isn't null when instantiated."), testSelector);
	
	return true;
}


bool FUMapSelectorWidgetCreatesAmountOfButtonsAsMapsFoundTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld-MapSelectorContainer");
	establishTestMessageTo(FString("The map selector widget should make as many string holder buttons as maps in the specified folder."));
	establishTickLimitTo(3);

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	
	

	ADD_LATENT_AUTOMATION_COMMAND(FSpawnGameModeDefaultPawn);
	ADD_LATENT_AUTOMATION_COMMAND(FCheckMapSelectorCreatesButtonsAsMapsFound(this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}




#endif //WITH_DEV_AUTOMATION_TESTS