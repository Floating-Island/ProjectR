// Fill out your copyright notice in the Description page of Project Settings.



#if WITH_DEV_AUTOMATION_TESTS

#include "ReversingMotorStateTestCommands.h"
#include "Jet/MotorStates/ReversingMotorState.h"
#include "../Utilities/PIESessionUtilities.h"
#include "../Mocks/JetMOCK.h"


//Test preparation commands:


bool FSpawningAJetAndActivateReversingMotorState::Update()
{
	if (GEditor->IsPlayingSessionInEditor())
	{
		PIESessionUtilities sessionUtilities = PIESessionUtilities();


		UWorld* testWorld = sessionUtilities.defaultPIEWorld();

		AJetMOCK* testJet = sessionUtilities.spawnInPIEAnInstanceOf<AJetMOCK>();

		AReversingMotorState* testState = NewObject<AReversingMotorState>();

		testState->activate(testJet->motorDriveComponent());

		return true;
	}
	return false;
}





//Test check commands:








#endif //WITH_DEV_AUTOMATION_TESTS
