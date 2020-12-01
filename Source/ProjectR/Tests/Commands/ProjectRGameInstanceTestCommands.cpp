// Fill out your copyright notice in the Description page of Project Settings.



#if WITH_DEV_AUTOMATION_TESTS

#include "ProjectRGameInstanceTestCommands.h"
#include "GameInstance/ProjectRGameInstance.h"
#include "../Utilities/PIESessionUtilities.h"

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
		
		test->TestNotNull(TEXT("loadMainMenu should bring the main menu instance."), testMenu);
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




#endif //WITH_DEV_AUTOMATION_TESTS
