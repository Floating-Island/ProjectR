// Fill out your copyright notice in the Description page of Project Settings.



#if WITH_DEV_AUTOMATION_TESTS

#include "AcceleratingMotorStateTestCommands.h"
#include "Jet/MotorStates/AcceleratingMotorState.h"
#include "../../Utilities/PIESessionUtilities.h"
#include "../../Mocks/JetMOCK.h"


//Test preparation commands:


bool FSpawningAJetAndActivateAcceleratingMotorState::Update()
{
	if (GEditor->IsPlayingSessionInEditor())
	{
		PIESessionUtilities sessionUtilities = PIESessionUtilities();


		UWorld* testWorld = sessionUtilities.defaultPIEWorld();

		AJetMOCK* testJet = sessionUtilities.spawnInPIEAnInstanceOf<AJetMOCK>();

		UAcceleratingMotorState* testState = NewObject<UAcceleratingMotorState>();

		testState->activate(testJet->motorDriveComponent());

		return true;
	}
	return false;
}











//Test check commands:






#endif //WITH_DEV_AUTOMATION_TESTS
