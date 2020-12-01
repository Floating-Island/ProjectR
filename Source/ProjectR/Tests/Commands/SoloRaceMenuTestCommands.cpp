// Fill out your copyright notice in the Description page of Project Settings.



#if WITH_DEV_AUTOMATION_TESTS

#include "SoloRaceMenuTestCommands.h"
#include "UI/SoloRaceMenu.h"
#include "../Utilities/PIESessionUtilities.h"
#include "GameInstance/ProjectRGameInstance.h"

//Test preparation commands:













//Test check commands:

bool FCheckSoloRaceMenuClickChangesMapCommand::Update()
{
	if (GEditor->IsPlayingSessionInEditor())
	{
		PIESessionUtilities sessionUtilities = PIESessionUtilities();
		bool isInAnotherWorld = GEditor->GetPIEWorldContext()->World()->GetMapName() != "VoidWorld";

		if(isMenuInstanciated && !isInAnotherWorld)
		{
			FVector2D playButtonCoordinates = aRaceMenuInstance->playButtonAbsoluteCenterPosition();
			sessionUtilities.processEditorClick(playButtonCoordinates);
		}
		
		if(aRaceMenuInstance == nullptr)
		{
			UProjectRGameInstance* gameInstance = Cast<UProjectRGameInstance,UGameInstance>(sessionUtilities.currentPIEWorld()->GetGameInstance());
			aRaceMenuInstance = gameInstance->loadSoloRaceMenu();
			isMenuInstanciated = true;
			return false;
		}
		
		if (isInAnotherWorld)
		{
			aTest->TestTrue(TEXT("The solo race menu should change the current map when clicking the play button."), isInAnotherWorld);
			sessionUtilities.currentPIEWorld()->bDebugFrameStepExecution = true;
			return true;
		}

		++aTickCount;
		if (aTickCount > aTickLimit)
		{
			aTest->TestTrue(TEXT("The solo race menu should change the current map when clicking the play button."), isInAnotherWorld);
			sessionUtilities.currentPIEWorld()->bDebugFrameStepExecution = true;
			return true;
		}
	}
	return false;
}


bool FCheckSoloRaceMenuClickGoBackRemovesFromViewportCommand::Update()
{
	if (GEditor->IsPlayingSessionInEditor())
	{
		PIESessionUtilities sessionUtilities = PIESessionUtilities();
	
		if(aRaceMenuInstance == nullptr)
		{
			UProjectRGameInstance* gameInstance = Cast<UProjectRGameInstance,UGameInstance>(sessionUtilities.currentPIEWorld()->GetGameInstance());
			aRaceMenuInstance = gameInstance->loadSoloRaceMenu();
			isMenuInstanciated = true;
			return false;
		}
		
		if(isMenuInstanciated && aRaceMenuInstance->IsInViewport())
		{
			FVector2D goBackButtonCoordinates = aRaceMenuInstance->goBackButtonAbsoluteCenterPosition();
			sessionUtilities.processEditorClick(goBackButtonCoordinates);
			return false;
		}
		
		aTest->TestTrue(TEXT("The solo race menu should be removed from viewport when clicking the go back button."), !aRaceMenuInstance->IsInViewport());
		sessionUtilities.currentPIEWorld()->bDebugFrameStepExecution = true;
		return true;
	}
	return false;
}






#endif //WITH_DEV_AUTOMATION_TESTS
