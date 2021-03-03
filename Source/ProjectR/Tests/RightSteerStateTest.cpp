// Fill out your copyright notice in the Description page of Project Settings.


#if WITH_DEV_AUTOMATION_TESTS


#include "RightSteerStateTest.h"
#include "Jet/SteerStates/RightSteerState.h"

#include "Tests/AutomationEditorCommon.h"
#include "Commands/CommonPIECommands.h"
#include "Mocks/JetMOCK.h"
#include "Commands/JetTestCommands.h"
#include "Commands/RightSteerStateTestCommands.h"
#include "Utilities/ObjectContainerActor.h"

bool FURightSteerStateIsntNullWhenInstantiatedTest::RunTest(const FString& Parameters)
{
	URightSteerState* testState = NewObject<URightSteerState>();

	TestNotNull("Shouldn't be null when instantiated.", testState);

	return true;
}


bool FURightSteerStateActivateTurnsRightSteeringTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));

	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	UClass* jetClass = AJetMOCK::StaticClass();
	ADD_LATENT_AUTOMATION_COMMAND(FSpawnInPIEAnActorOfClass(jetClass, FTransform()));
	float desiredSpeed = 10000;
	ADD_LATENT_AUTOMATION_COMMAND(FRetrieveAJetMOCKSetVelocityToDesiredSpeed(desiredSpeed));

	UClass* containerClass = AObjectContainerActor::StaticClass();
	ADD_LATENT_AUTOMATION_COMMAND(FSpawnInPIEAnActorOfClass(containerClass, FTransform()));
	
	int tickCount = 0;
	int tickLimit = 3;
	FVector location = FVector(0);
	ADD_LATENT_AUTOMATION_COMMAND(FCheckAJetSteersRight(tickCount, tickLimit, location, this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}





#endif //WITH_DEV_AUTOMATION_TESTS