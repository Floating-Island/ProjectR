// Fill out your copyright notice in the Description page of Project Settings.



#if WITH_DEV_AUTOMATION_TESTS

#include "ProjectRGameInstanceTestCommands.h"
#include "GameInstance/ProjectRGameInstance.h"
#include "../Utilities/PIESessionUtilities.h"
#include "UI/MainMenu.h"
#include "UI/SingleplayerMenu.h"


//Test preparation commands:










//Test check commands:




bool FCheckIsSetAsProjectGameInstance::Update()
{
	if (GEditor->IsPlayingSessionInEditor())
	{
		PIESessionUtilities sessionUtilities = PIESessionUtilities();
		UProjectRGameInstance* testInstance = Cast<UProjectRGameInstance, UGameInstance>(sessionUtilities.defaultPIEWorld()->GetGameInstance());

		test->TestNotNull(TEXT("ProjectR game instance should be set as project instance."), testInstance);
		return true;
	}
	return false;
}


bool FCheckCreatesMainMenu::Update()
{
	if (GEditor->IsPlayingSessionInEditor())
	{
		PIESessionUtilities sessionUtilities = PIESessionUtilities();
		UProjectRGameInstance* testInstance = Cast<UProjectRGameInstance, UGameInstance>(sessionUtilities.defaultPIEWorld()->GetGameInstance());

		UMainMenu* testMenu = testInstance->loadMainMenu();

		test->TestTrue(TEXT("loadMainMenu should bring the main menu instance and add it to viewport."), testMenu && testMenu->IsInViewport());
		return true;
	}
	return false;
}


bool FCheckCreatesOneMainMenu::Update()
{
	if (GEditor->IsPlayingSessionInEditor())
	{
		PIESessionUtilities sessionUtilities = PIESessionUtilities();
		UProjectRGameInstance* testInstance = Cast<UProjectRGameInstance, UGameInstance>(sessionUtilities.defaultPIEWorld()->GetGameInstance());

		UMainMenu* testMenu = testInstance->loadMainMenu();
		UMainMenu* anotherTestMenu = testInstance->loadMainMenu();

		aTest->TestTrue(TEXT("loadMainMenu should create only one instance of main menu."), testMenu == anotherTestMenu);
		return true;
	}
	return false;
}


bool FCheckCreatesSingleplayerMenu::Update()
{
	if (GEditor->IsPlayingSessionInEditor())
	{
		PIESessionUtilities sessionUtilities = PIESessionUtilities();
		UProjectRGameInstance* testInstance = Cast<UProjectRGameInstance, UGameInstance>(sessionUtilities.defaultPIEWorld()->GetGameInstance());

		USingleplayerMenu* testMenu = testInstance->loadSingleplayerMenu();

		aTest->TestTrue(TEXT("loadSingleplayerMenu should bring the singleplayer menu instance and add it to viewport."), testMenu && testMenu->IsInViewport());
		return true;
	}
	return false;
}


bool FCheckCreatesOneSingleplayerMenu::Update()
{
	if (GEditor->IsPlayingSessionInEditor())
	{
		PIESessionUtilities sessionUtilities = PIESessionUtilities();
		UProjectRGameInstance* testInstance = Cast<UProjectRGameInstance, UGameInstance>(sessionUtilities.defaultPIEWorld()->GetGameInstance());

		USingleplayerMenu* testMenu = testInstance->loadSingleplayerMenu();
		USingleplayerMenu* anotherTestMenu = testInstance->loadSingleplayerMenu();

		aTest->TestTrue(TEXT("loadSingleplayerMenu should create only one instance of singleplayer menu."), testMenu == anotherTestMenu);
		return true;
	}
	return false;
}


bool FCheckShowsCursorInMainMenu::Update()
{
	if (GEditor->IsPlayingSessionInEditor())
	{
		PIESessionUtilities sessionUtilities = PIESessionUtilities();
		UProjectRGameInstance* testInstance = Cast<UProjectRGameInstance, UGameInstance>(sessionUtilities.defaultPIEWorld()->GetGameInstance());

		UMainMenu* testMenu = testInstance->loadMainMenu();
		bool controllerShowsMouseCursor = sessionUtilities.defaultPIEWorld()->GetFirstPlayerController()->ShouldShowMouseCursor();

		aTest->TestTrue(TEXT("loadMainMenu should make the controller show the mouse cursor."), testMenu && controllerShowsMouseCursor);
		return true;
	}
	return false;
}


bool FCheckShowsCursorInSingleplayerMenu::Update()
{
	if (GEditor->IsPlayingSessionInEditor())
	{
		PIESessionUtilities sessionUtilities = PIESessionUtilities();
		UProjectRGameInstance* testInstance = Cast<UProjectRGameInstance, UGameInstance>(sessionUtilities.defaultPIEWorld()->GetGameInstance());

		USingleplayerMenu* testMenu = testInstance->loadSingleplayerMenu();
		bool controllerShowsMouseCursor = sessionUtilities.defaultPIEWorld()->GetFirstPlayerController()->ShouldShowMouseCursor();

		aTest->TestTrue(TEXT("loadSingleplayerMenu should make the controller show the mouse cursor."), testMenu && controllerShowsMouseCursor);
		return true;
	}
	return false;
}


bool FCheckNecessaryPlayersAreTheExpected::Update()
{
	if (GEditor->IsPlayingSessionInEditor())
	{
		PIESessionUtilities sessionUtilities = PIESessionUtilities();
		UProjectRGameInstance* testInstance = Cast<UProjectRGameInstance, UGameInstance>(sessionUtilities.defaultPIEWorld()->GetGameInstance());

		int expectedPlayers = 4;

		testInstance->expectedPlayers(expectedPlayers);

		int necessaryPlayers = testInstance->necessaryPlayers();

		aTest->TestTrue(TEXT("necessaryPlayers returns the expected number of players in the game."), necessaryPlayers == expectedPlayers);
		return true;
	}
	return false;
}




#endif //WITH_DEV_AUTOMATION_TESTS
