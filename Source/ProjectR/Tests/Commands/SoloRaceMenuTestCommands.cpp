// Fill out your copyright notice in the Description page of Project Settings.



#if WITH_DEV_AUTOMATION_TESTS

#include "SoloRaceMenuTestCommands.h"
#include "UI/SoloRaceMenu.h"
#include "../Utilities/PIESessionUtilities.h"

//Test preparation commands:

bool FCreateSoloRaceMenu::Update()
{
	if (GEditor->IsPlayingSessionInEditor())
	{
		PIESessionUtilities sessionUtilities = PIESessionUtilities();
		sessionUtilities->loadMenu<USoloRaceMenu>();
		return true;
	}
	return false;
}











//Test check commands:

bool FCheckSoloRaceMenuClickChangesMapCommand::Update()
{
	if (GEditor->IsPlayingSessionInEditor())
	{
		PIESessionUtilities sessionUtilities = PIESessionUtilities();
		bool isInAnotherWorld = GEditor->GetPIEWorldContext()->World()->GetMapName() != "VoidWorld";
		
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





#endif //WITH_DEV_AUTOMATION_TESTS
