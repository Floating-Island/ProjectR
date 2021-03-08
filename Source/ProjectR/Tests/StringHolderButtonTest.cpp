// Fill out your copyright notice in the Description page of Project Settings.


#if WITH_DEV_AUTOMATION_TESTS


#include "StringHolderButtonTest.h"
#include "UI/StringHolderButton.h"
#include "Tests/AutomationEditorCommon.h"
#include "Commands/CommonPIECommands.h"
#include "Commands/StringHolderButtonTestCommands.h"


bool FUStringHolderButtonIsntNullWhenInstantiatedTest::RunTest(const FString& Parameters)
{
	UStringHolderButton* testButton = NewObject<UStringHolderButton>();

	TestNotNull(TEXT("The string holder button shouldn't be null after instantiating it."), testButton);
	
	return true;
}


bool FUStringHolderButtonStoresStringsTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld-StringHolderContainer");
	establishTestMessageTo(FString("The string holder button should be able to store a FString."));
	establishTickLimitTo(3);

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	
	

	ADD_LATENT_AUTOMATION_COMMAND(FSpawnGameModeDefaultPawn);
	ADD_LATENT_AUTOMATION_COMMAND(FCheckAStringHolderButtonStoresAndRetrievesString(this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}



#endif //WITH_DEV_AUTOMATION_TESTS