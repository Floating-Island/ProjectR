// Fill out your copyright notice in the Description page of Project Settings.


#if WITH_DEV_AUTOMATION_TESTS


#include "LeftSteerStateTest.h"
#include "Jet/SteerStates/LeftSteerState.h"

#include "Tests/AutomationEditorCommon.h"
#include "Commands/CommonPIECommands.h"
#include "Commands/JetTestCommands.h"
#include "Commands/LeftSteerStateTestCommands.h"
#include "Mocks/JetMOCK.h"
#include "Utilities/ObjectContainerActor.h"

bool FULeftSteerStateIsntNullWhenInstantiatedTest::RunTest(const FString& Parameters)
{
	ULeftSteerState* testState = NewObject<ULeftSteerState>();

	TestNotNull("Shouldn't be null when instantiated.", testState);

	return true;
}


bool FULeftSteerStateActivateTurnsLeftSteeringTest::RunTest(const FString& Parameters)
{
	establishInitialMapDirectoryTo(FString("/Game/Tests/TestMaps/VoidWorld"));
	establishTestMessageTo(FString("The left steer state should steer left the steering component passed as parameter."));
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
	ADD_LATENT_AUTOMATION_COMMAND(FCheckAJetSteersLeft(location, this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}



#endif //WITH_DEV_AUTOMATION_TESTS