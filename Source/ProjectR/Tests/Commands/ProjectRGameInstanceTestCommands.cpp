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
	if(GEditor->IsPlayingSessionInEditor())
	{
		PIESessionUtilities sessionUtilities = PIESessionUtilities();
		UProjectRGameInstance* testInstance = Cast<UProjectRGameInstance, UGameInstance>(sessionUtilities.currentPIEWorld()->GetGameInstance());

		test->TestNotNull(TEXT("ProjectR game instance should be set as project instance."), testInstance);
		return true;
	}
	return false;
}


bool FCheckCreatesMainMenu::Update()
{
	if(GEditor->IsPlayingSessionInEditor())
	{
		PIESessionUtilities sessionUtilities = PIESessionUtilities();
		UProjectRGameInstance* testInstance = Cast<UProjectRGameInstance, UGameInstance>(sessionUtilities.currentPIEWorld()->GetGameInstance());

		UMainMenu* testMenu = testInstance->loadMainMenu();
		
		test->TestTrue(TEXT("loadMainMenu should bring the main menu instance and add it to viewport."), testMenu && testMenu->IsInViewport());
		return true;
	}
	return false;
}


bool FCheckCreatesOneMainMenu::Update()
{
	if(GEditor->IsPlayingSessionInEditor())
	{
		PIESessionUtilities sessionUtilities = PIESessionUtilities();
		UProjectRGameInstance* testInstance = Cast<UProjectRGameInstance, UGameInstance>(sessionUtilities.currentPIEWorld()->GetGameInstance());

		UMainMenu* testMenu = testInstance->loadMainMenu();
		UMainMenu* anotherTestMenu = testInstance->loadMainMenu();
		
		aTest->TestTrue(TEXT("loadMainMenu should create only one instance of main menu."), testMenu == anotherTestMenu);
		return true;
	}
	return false;
}


bool FCheckCreatesSingleplayerMenu::Update()
{
	if(GEditor->IsPlayingSessionInEditor())
	{
		PIESessionUtilities sessionUtilities = PIESessionUtilities();
		UProjectRGameInstance* testInstance = Cast<UProjectRGameInstance, UGameInstance>(sessionUtilities.currentPIEWorld()->GetGameInstance());

		USingleplayerMenu* testMenu = testInstance->loadSingleplayerMenu();
		
		aTest->TestTrue(TEXT("loadSingleplayerMenu should bring the singleplayer menu instance and add it to viewport."), testMenu && testMenu->IsInViewport());
		return true;
	}
	return false;
}


bool FCheckCreatesOneSingleplayerMenu::Update()
{
	if(GEditor->IsPlayingSessionInEditor())
	{
		PIESessionUtilities sessionUtilities = PIESessionUtilities();
		UProjectRGameInstance* testInstance = Cast<UProjectRGameInstance, UGameInstance>(sessionUtilities.currentPIEWorld()->GetGameInstance());

		USingleplayerMenu* testMenu = testInstance->loadSingleplayerMenu();
		USingleplayerMenu* anotherTestMenu = testInstance->loadSingleplayerMenu();
		
		aTest->TestTrue(TEXT("loadSingleplayerMenu should create only one instance of singleplayer menu."), testMenu == anotherTestMenu);
		return true;
	}
	return false;
}



#endif //WITH_DEV_AUTOMATION_TESTS
