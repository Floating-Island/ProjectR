// Fill out your copyright notice in the Description page of Project Settings.



#if WITH_DEV_AUTOMATION_TESTS

#include "ProjectRGameStateTestCommands.h"
#include "../Utilities/PIESessionUtilities.h"
#include "GameState/ProjectRGameState.h"
#include "UI/PauseMenu.h"

//Test preparation commands:













//Test check commands:


bool FCheckGameStateBringsPauseMenu::Update()
{
	if(GEditor->IsPlayingSessionInEditor())
	{
		PIESessionUtilities sessionUtilities = PIESessionUtilities();
		AProjectRGameState* testGameState = Cast<AProjectRGameState, AGameStateBase>(sessionUtilities.currentPIEWorld()->GetGameState());

		UPauseMenu* testMenu = testGameState->loadPauseMenu();
		
		aTest->TestTrue(TEXT("loadPauseMenu should bring the pause menu instance and add it to viewport."), testMenu && testMenu->IsInViewport());
		return true;
	}
	return false;
}




#endif //WITH_DEV_AUTOMATION_TESTS
