// Fill out your copyright notice in the Description page of Project Settings.


#if WITH_DEV_AUTOMATION_TESTS


#include "RightSteerStateTest.h"
#include "Jet/SteerStates/RightSteerState.h"

#include "Tests/AutomationEditorCommon.h"
#include "../../Commands/CommonPIECommands.h"
#include "../../Mocks/JetMOCK.h"
#include "../Jet/JetTestCommands.h"
#include "RightSteerStateTestCommands.h"
#include "../../Utilities/ObjectContainerActor.h"

bool FURightSteerStateIsntNullWhenInstantiatedTest::RunTest(const FString& Parameters)
{
	URightSteerState* testState = NewObject<URightSteerState>();

	TestNotNull("Shouldn't be null when instantiated.", testState);

	return true;
}


bool FURightSteerStateActivateTurnsRightSteeringTest::RunTest(const FString& Parameters)
{
	establishInitialMapDirectoryTo(FString("/Game/Development/Maps/VoidWorld"));
	establishTestMessageTo(FString("The right steer state should steer right the steering component passed as parameter."));
	establishTickLimitTo(3);

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(retrieveInitialMapDirectory()));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	
	

	UClass* jetClass = AJetMOCK::StaticClass();
	ADD_LATENT_AUTOMATION_COMMAND(FSpawnInPIEAnActorOfClass(jetClass, FTransform()));
	float desiredSpeed = 10000;
	ADD_LATENT_AUTOMATION_COMMAND(FRetrieveAJetMOCKSetVelocityToDesiredSpeed(desiredSpeed));

	UClass* containerClass = AObjectContainerActor::StaticClass();
	ADD_LATENT_AUTOMATION_COMMAND(FSpawnInPIEAnActorOfClass(containerClass, FTransform()));

	FVector location = FVector(0);
	ADD_LATENT_AUTOMATION_COMMAND(FCheckAJetSteersRight(location, this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}





#endif //WITH_DEV_AUTOMATION_TESTS