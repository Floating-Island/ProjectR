// Fill out your copyright notice in the Description page of Project Settings.


#if WITH_DEV_AUTOMATION_TESTS

#include "TrackSelectorWidgetTest.h"
#include "../Public/UI/TrackSelectorWidget.h"
#include "Tests/AutomationEditorCommon.h"
#include "Commands/TrackSelectorWidgetTestCommands.h"



bool FUTrackSelectorWidgetIsntNullWhenInstantiatedTest::RunTest(const FString& Parameters)
{
	UTrackSelectorWidget* testSelector = NewObject<UTrackSelectorWidget>();

	TestNotNull(TEXT("Isn't null when instantiated."), testSelector);
	
	return true;
}


bool FUTrackSelectorWidgetCreatesAmountOfButtonsAsMapsFoundTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld-TrackSelectorContainer");
	establishTestMessageTo(FString("The track selector widget should make as many string holder buttons as maps in the specified folder."));
	establishTickLimitTo(3);

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	ADD_LATENT_AUTOMATION_COMMAND(FCheckTrackSelectorCreatesButtonsAsMapsFound(this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}




#endif //WITH_DEV_AUTOMATION_TESTS