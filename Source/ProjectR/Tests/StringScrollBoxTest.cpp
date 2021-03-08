// Fill out your copyright notice in the Description page of Project Settings.


#if WITH_DEV_AUTOMATION_TESTS


#include "StringScrollBoxTest.h"
#include "UI/StringButtonScrollBox.h"

#include "Tests/AutomationEditorCommon.h"
#include "Commands/CommonPIECommands.h"
#include "Commands/StringScrollBoxTestCommands.h"



bool FUStringButtonScrollBoxIsntNullWhenInstantiatedTest::RunTest(const FString& Parameters)
{
	UStringButtonScrollBox* testScroll = NewObject<UStringButtonScrollBox>();

	TestNotNull(TEXT("The string button scroll box shouldn't be null after instantiating it."), testScroll);
	
	return true;
}


bool FUStringButtonScrollBoxPopulatesScrollBoxWithStringHolderButtonsTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld-StringScrollContainer");
	establishTestMessageTo(FString("populateBox should fill the same number of string buttons as strings passed."));
	establishTickLimitTo(3);

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	
	

	ADD_LATENT_AUTOMATION_COMMAND(FSpawnGameModeDefaultPawn);
	ADD_LATENT_AUTOMATION_COMMAND(FCheckAStringScrollBoxPopulateBoxNumberOfChilds(this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FUStringButtonScrollClickingChildButtonUpdatesSelectedStringTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld-StringScrollContainer");
	establishTestMessageTo(FString("Clicking a child button should update the selected string to it."));
	establishTickLimitTo(3);

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	
	

	ADD_LATENT_AUTOMATION_COMMAND(FSpawnGameModeDefaultPawn);
	ADD_LATENT_AUTOMATION_COMMAND(FCheckAStringScrollBoxChildClicked(nullptr, this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FUStringButtonScrollPopulatingBoxWithDifferentArraysLeavesOnlyTheLastTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld-StringScrollContainer");
	establishTestMessageTo(FString("Populating the scroll box should make it keep only the passed array as children."));
	establishTickLimitTo(3);

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	
	

	ADD_LATENT_AUTOMATION_COMMAND(FSpawnGameModeDefaultPawn);
	ADD_LATENT_AUTOMATION_COMMAND(FCheckAStringScrollBoxKeepsArraySize(nullptr, this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}



#endif //WITH_DEV_AUTOMATION_TESTS