// Fill out your copyright notice in the Description page of Project Settings.


#if WITH_DEV_AUTOMATION_TESTS

#include "ProjectRGameInstanceTestCommands.h"
#include "GameInstance/ProjectRGameInstance.h"
#include "../Utilities/PIESessionUtilities.h"
#include "../TestBaseClasses/SimplePIETestBase.h"
#include "UI/MainMenu.h"
#include "UI/SingleplayerMenu.h"
#include "UI/LocalMultiplayerMenu.h"
#include "UI/LanMultiplayerMenu.h"
#include "UI/LobbyMenu.h"




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

		test->TestTrue(TEXT("loadMainMenu should create only one instance of main menu."), testMenu == anotherTestMenu);
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

		test->TestTrue(TEXT("loadSingleplayerMenu should bring the singleplayer menu instance and add it to viewport."), testMenu && testMenu->IsInViewport());
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

		test->TestTrue(TEXT("loadSingleplayerMenu should create only one instance of singleplayer menu."), testMenu == anotherTestMenu);
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

		test->TestTrue(TEXT("loadMainMenu should make the controller show the mouse cursor."), testMenu && controllerShowsMouseCursor);
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

		test->TestTrue(TEXT("loadSingleplayerMenu should make the controller show the mouse cursor."), testMenu && controllerShowsMouseCursor);
		return true;
	}
	return false;
}


bool FCheckCreatesSplitscreenMenu::Update()
{
	if (GEditor->IsPlayingSessionInEditor())
	{
		PIESessionUtilities sessionUtilities = PIESessionUtilities();
		UProjectRGameInstance* testInstance = Cast<UProjectRGameInstance, UGameInstance>(sessionUtilities.defaultPIEWorld()->GetGameInstance());

		ULocalMultiplayerMenu* testMenu = testInstance->loadLocalMultiplayerMenu();

		test->TestTrue(TEXT("loadLocalMultiplayerMenu should bring the splitscreen menu instance and add it to viewport."), testMenu && testMenu->IsInViewport());
		return true;
	}
	return false;
}


bool FCheckCreatesOneSplitscreenMenu::Update()
{
	if (GEditor->IsPlayingSessionInEditor())
	{
		PIESessionUtilities sessionUtilities = PIESessionUtilities();
		UProjectRGameInstance* testInstance = Cast<UProjectRGameInstance, UGameInstance>(sessionUtilities.defaultPIEWorld()->GetGameInstance());

		ULocalMultiplayerMenu* testMenu = testInstance->loadLocalMultiplayerMenu();
		ULocalMultiplayerMenu* anotherTestMenu = testInstance->loadLocalMultiplayerMenu();

		test->TestTrue(TEXT("loadLocalMultiplayerMenu should create only one instance of splitscreen menu."), testMenu == anotherTestMenu);
		return true;
	}
	return false;
}


bool FCheckShowsCursorInSplitscreenMenu::Update()
{
	if (GEditor->IsPlayingSessionInEditor())
	{
		PIESessionUtilities sessionUtilities = PIESessionUtilities();
		UProjectRGameInstance* testInstance = Cast<UProjectRGameInstance, UGameInstance>(sessionUtilities.defaultPIEWorld()->GetGameInstance());

		ULocalMultiplayerMenu* testMenu = testInstance->loadLocalMultiplayerMenu();
		bool controllerShowsMouseCursor = sessionUtilities.defaultPIEWorld()->GetFirstPlayerController()->ShouldShowMouseCursor();

		test->TestTrue(TEXT("loadLocalMultiplayerMenu should make the controller show the mouse cursor."), testMenu && controllerShowsMouseCursor);
		return true;
	}
	return false;
}

bool FCheckLoadMainMenuSetsExpectedPlayersToOne::Update()
{
	if (GEditor->IsPlayingSessionInEditor())
	{
		PIESessionUtilities sessionUtilities = PIESessionUtilities();
		UProjectRGameInstance* testInstance = Cast<UProjectRGameInstance, UGameInstance>(sessionUtilities.defaultPIEWorld()->GetGameInstance());

		int arbitraryExpectedJets = 2;
		testInstance->expectedPlayers(arbitraryExpectedJets);
		
		UMainMenu* testMenu = testInstance->loadMainMenu();

		test->TestTrue(TEXT("loadMainMenu should set the expected players to one."), testInstance->necessaryPlayers() == 1);
		return true;
	}
	return false;
}

bool FCheckSessionManagerSetInGameInstance::Update()
{
	if (GEditor->IsPlayingSessionInEditor())
	{
		PIESessionUtilities sessionUtilities = PIESessionUtilities();
		UProjectRGameInstance* testInstance = Cast<UProjectRGameInstance, UGameInstance>(sessionUtilities.defaultPIEWorld()->GetGameInstance());

		test->TestTrue(TEXT("The session manager should be set and configured."), testInstance->sessionManagerIsConfigured());
		return true;
	}
	return false;
}


bool FCheckCreatesLANMultiplayerMenu::Update()
{
	if (GEditor->IsPlayingSessionInEditor())
	{
		PIESessionUtilities sessionUtilities = PIESessionUtilities();
		UProjectRGameInstance* testInstance = Cast<UProjectRGameInstance, UGameInstance>(sessionUtilities.defaultPIEWorld()->GetGameInstance());

		ULanMultiplayerMenu* testMenu = testInstance->loadLANMUltiplayerMenu();

		test->TestTrue(TEXT("loadLANMUltiplayerMenu should bring the lanMultiplayer menu instance and add it to viewport."), testMenu && testMenu->IsInViewport());
		return true;
	}
	return false;
}


bool FCheckCreatesOneLANMultiplayerMenu::Update()
{
	if (GEditor->IsPlayingSessionInEditor())
	{
		PIESessionUtilities sessionUtilities = PIESessionUtilities();
		UProjectRGameInstance* testInstance = Cast<UProjectRGameInstance, UGameInstance>(sessionUtilities.defaultPIEWorld()->GetGameInstance());

		ULanMultiplayerMenu* testMenu = testInstance->loadLANMUltiplayerMenu();
		ULanMultiplayerMenu* testAnotherMenu = testInstance->loadLANMUltiplayerMenu();

		test->TestTrue(TEXT("loadLANMUltiplayerMenu should create only one instance of lanMultiplayer menu."), testMenu == testAnotherMenu);
		return true;
	}
	return false;
}


bool FCheckShowsCursorInLanMultiplayerMenu::Update()
{
	if (GEditor->IsPlayingSessionInEditor())
	{
		PIESessionUtilities sessionUtilities = PIESessionUtilities();
		UProjectRGameInstance* testInstance = Cast<UProjectRGameInstance, UGameInstance>(sessionUtilities.defaultPIEWorld()->GetGameInstance());

		ULanMultiplayerMenu* testMenu = testInstance->loadLANMUltiplayerMenu();
		bool controllerShowsMouseCursor = sessionUtilities.defaultPIEWorld()->GetFirstPlayerController()->ShouldShowMouseCursor();

		test->TestTrue(TEXT("loadLanMultiplayerMenu should make the controller show the mouse cursor."), testMenu && controllerShowsMouseCursor);
		return true;
	}
	return false;
}


bool FCheckCreatesLobbyMenu::Update()
{
	if (GEditor->IsPlayingSessionInEditor())
	{
		PIESessionUtilities sessionUtilities = PIESessionUtilities();
		UProjectRGameInstance* testInstance = Cast<UProjectRGameInstance, UGameInstance>(sessionUtilities.defaultPIEWorld()->GetGameInstance());

		ULobbyMenu* testMenu = testInstance->loadLobbyMenu();

		test->TestTrue(test->conditionMessage(), testMenu && testMenu->IsInViewport());
		return true;
	}
	return false;
}






#endif //WITH_DEV_AUTOMATION_TESTS
