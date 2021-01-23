// Fill out your copyright notice in the Description page of Project Settings.


#if WITH_DEV_AUTOMATION_TESTS

#include "JetTest.h"
#include "Commands/JetTestCommands.h"
#include "Jet/Jet.h"
#include "Mocks/JetMOCK.h"

//to be able to simulate:
#include "Tests/AutomationEditorCommon.h"
#include "Commands/NetworkCommands.h"



bool FAJetIsntNullWhenInstantiatedTest::RunTest(const FString& Parameters)
{
	AJet* testJet = NewObject<AJet>();
	TestNotNull(TEXT("The Jet shouldn't be null after instantiating it."), testJet);

	return true;
}


bool FAJetSpeedIsZeroWhenInstantiatedTest::RunTest(const FString& Parameters)
{
	AJet* testJet = NewObject<AJet>();
	TestTrue(TEXT("Jet speed should be zero when instantiated."), testJet->currentSpeed() == 0);

	return true;
}


bool FAJetHasAStaticMeshTest::RunTest(const FString& Parameters)
{
	AJetMOCK* testJet = NewObject<AJetMOCK>();
	TestTrue(TEXT("The Jet physics mesh shouldn't be null if it has one."), testJet->hasAPhysicsMesh());

	return true;
}


bool FAJetMeshIsTheRootComponentTest::RunTest(const FString& Parameters)
{
	AJetMOCK* testJet = NewObject<AJetMOCK>();
	TestTrue(TEXT("The Jet physics mesh should be the root component."), testJet->isPhysicsMeshTheRootComponent());

	return true;
}


bool FAJetHasGravityEnabledTest::RunTest(const FString& Parameters)
{
	AJetMOCK* testJet = NewObject<AJetMOCK>();
	TestTrue(TEXT("The Jet should have gravity enabled."), testJet->hasGravityEnabled());

	return true;
}


bool FAJetDoesntAffectNavigationVolumeTest::RunTest(const FString& Parameters)
{
	AJetMOCK* testJet = NewObject<AJetMOCK>();
	TestFalse(TEXT("The Jet shouldn't affect the navigation volume."), testJet->isAffectingNavigation());

	return true;
}


bool FAJetIsMovableTest::RunTest(const FString& Parameters)
{
	AJetMOCK* testJet = NewObject<AJetMOCK>();
	TestTrue(TEXT("The Jet should be movable when spawned into the world."), testJet->IsRootComponentMovable());

	return true;
}


bool FAJetDefaultAccelerationIsGreaterThanZeroTest::RunTest(const FString& Parameters)
{
	AJet* testJet = NewObject<AJet>(AJet::StaticClass());
	TestTrue(TEXT("A Jet's default acceleration should be bigger than zero."), testJet->acceleration() > 0);

	return true;
}


bool FAJetMovesForwardWhenAcceleratedTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	ADD_LATENT_AUTOMATION_COMMAND(FSpawningAJetMakeItAccelerate);
	int tickCount = 0;
	int tickLimit = 3;
	ADD_LATENT_AUTOMATION_COMMAND(FCheckAJetLocation(tickCount, tickLimit, this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FAJetSpeedIncreasesWhenAcceleratesTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	ADD_LATENT_AUTOMATION_COMMAND(FSpawningAJetMakeItAccelerate);
	int tickCount = 0;
	int tickLimit = 3;
	ADD_LATENT_AUTOMATION_COMMAND(FCheckAJetSpeedIncrease(tickCount, tickLimit, this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FAJetDefaultBrakeValueIsGreaterThanZeroTest::RunTest(const FString& Parameters)
{
	AJet* testJet = NewObject<AJet>(AJet::StaticClass());
	TestTrue(TEXT("A Jet's default brake value should be bigger than zero."), testJet->brakeValue() > 0);

	return true;
}


bool FAJetVelocityNegativeWhenBrakesTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	ADD_LATENT_AUTOMATION_COMMAND(FSpawningAJetMakeItBrake);
	int tickCount = 0;
	int tickLimit = 3;
	ADD_LATENT_AUTOMATION_COMMAND(FCheckAJetVelocityDecrease(tickCount, tickLimit, this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FAJetDefaultTopSpeedIsGreaterThanZeroTest::RunTest(const FString& Parameters)
{
	AJet* testJet = NewObject<AJet>(AJet::StaticClass());
	TestTrue(TEXT("A Jet's default top speed should be bigger than zero."), testJet->settedTopSpeed() > 0);

	return true;
}


bool FAJetDoesntAccelerateWhenAtTopSpeedTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	ADD_LATENT_AUTOMATION_COMMAND(FSpawningAJetSetVelocityToTopSpeed);
	int tickCount = 0;
	int tickLimit = 3;
	ADD_LATENT_AUTOMATION_COMMAND(FCheckAJetSpeedAgainstTopSpeed(tickCount, tickLimit, this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FAJetRotatesYawRightWhenSteeringRightTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	ADD_LATENT_AUTOMATION_COMMAND(FSpawningAJetMakeItSteerRight);
	int tickCount = 0;
	int tickLimit = 3;
	ADD_LATENT_AUTOMATION_COMMAND(FCheckAJetRotatedYaw(tickCount, tickLimit, this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FAJetDefaultSteerRadiusIsGreaterThanZeroTest::RunTest(const FString& Parameters)
{
	AJet* testJet = NewObject<AJet>(AJet::StaticClass());
	TestTrue(TEXT("A Jet's default steer radius should be bigger than zero."), testJet->steerRadius() > 0);

	return true;
}


bool FAJetAcceleratesWhenPressingAccelerationKeyTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld-JetMOCKTest");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	ADD_LATENT_AUTOMATION_COMMAND(FSpawningAJetPressAccelerationKey);
	int tickCount = 0;
	int tickLimit = 3;
	ADD_LATENT_AUTOMATION_COMMAND(FCheckAJetSpeedIncrease(tickCount, tickLimit, this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FAJetMovesRightWhenPressingSteerRightKeyTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld-JetMOCKTest");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	ADD_LATENT_AUTOMATION_COMMAND(FSpawningAJetPressSteerRightKey);
	int tickCount = 0;
	int tickLimit = 3;
	ADD_LATENT_AUTOMATION_COMMAND(FCheckAJetRotatedYaw(tickCount, tickLimit, this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FAJetBrakesWhenPressingBrakeKeyTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld-JetMOCKTest");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	ADD_LATENT_AUTOMATION_COMMAND(FSpawningAJetPressBrakeKey);
	int tickCount = 0;
	int tickLimit = 3;
	ADD_LATENT_AUTOMATION_COMMAND(FCheckAJetVelocityDecrease(tickCount, tickLimit, this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FAJetHasASpringArmTest::RunTest(const FString& Parameters)
{
	AJetMOCK* testJet = NewObject<AJetMOCK>();
	TestTrue(TEXT("The Jet should have a spring arm."), testJet->hasASprinArm());

	return true;
}


bool FAJetSpringArmIsAttachedToRootComponentTest::RunTest(const FString& Parameters)
{
	AJetMOCK* testJet = NewObject<AJetMOCK>();
	TestTrue(TEXT("The Jet should have a spring arm attached to the root component."), testJet->isSpringArmAttachedToRoot());

	return true;
}


bool FAJetHasACameraTest::RunTest(const FString& Parameters)
{
	AJetMOCK* testJet = NewObject<AJetMOCK>();
	TestTrue(TEXT("The Jet should have a camera."), testJet->HasCameraComponent());

	return true;
}


bool FAJetCameraIsAttachedToSpringArmTest::RunTest(const FString& Parameters)
{
	AJetMOCK* testJet = NewObject<AJetMOCK>();
	TestTrue(TEXT("The Jet should have a camera attached to a springArm."), testJet->isCameraAttachedToSpringArm());

	return true;
}


bool FAJetGetsUpwardsImpulseFromAntiGravityOnFloorTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	ADD_LATENT_AUTOMATION_COMMAND(FSpawningAJetSnapedToFloor);
	int tickCount = 0;
	int tickLimit = 3;
	ADD_LATENT_AUTOMATION_COMMAND(FCheckAJetZLocation(tickCount, tickLimit, this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FAJetAcceleratesAlongItsForwardVectorWhenAcceleratedAfterRotationTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	ADD_LATENT_AUTOMATION_COMMAND(FSpawningAJetRotateAndAccelerate);
	int tickCount = 0;
	int tickLimit = 3;
	ADD_LATENT_AUTOMATION_COMMAND(FCheckAJetLocationCoincidentToForwardVector(tickCount, tickLimit, this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FAJetBrakesAlongItsBackwardsVectorWhileRotatedTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	ADD_LATENT_AUTOMATION_COMMAND(FSpawningAJetRotateAndBrake);
	int tickCount = 0;
	int tickLimit = 3;
	ADD_LATENT_AUTOMATION_COMMAND(FCheckAJetLocationParallelToForwardVector(tickCount, tickLimit, this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


//bool FAJetUpdatesVelocityDirectionAfterSteeringTest::RunTest(const FString& Parameters)
//{
//
//	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");
//
//	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));
//
//	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));
//
//	ADD_LATENT_AUTOMATION_COMMAND(FSpawningAJetAccelerateAndSteerRight);
//	int tickCount = 0;
//	int tickLimit = 3;
//	ADD_LATENT_AUTOMATION_COMMAND(FCheckAJetUpdatedVelocityWhenAfterSteering(tickCount, tickLimit, FVector(0), this));
//
//	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
//
//	return true;
//}


bool FAJetInvertsSteeringWhenInReverseTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	ADD_LATENT_AUTOMATION_COMMAND(FSpawningAJetBrakeAndSteerRight);
	int tickCount = 0;
	int tickLimit = 3;
	ADD_LATENT_AUTOMATION_COMMAND(FCheckAJetInvertSteeringWhenInReverse(tickCount, tickLimit, this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FAJetIsntAbleToSteerWhenIdleTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	ADD_LATENT_AUTOMATION_COMMAND(FSpawningAJeSteerRightWhenIdle);
	int tickCount = 0;
	int tickLimit = 3;
	ADD_LATENT_AUTOMATION_COMMAND(FCheckAJetUnableToSteerWhenIdle(tickCount, tickLimit, FRotator(0), this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FAJetGeneratesOverlapEventsWhenSpawnedTest::RunTest(const FString& Parameters)
{
	AJet* testJet = NewObject<AJet>();
	TestTrue(TEXT("Jet should generate overlap events when spawned into a level."), testJet->bGenerateOverlapEventsDuringLevelStreaming);

	return true;
}


bool FAJetMeshCollisionIsOfTypePawnTest::RunTest(const FString& Parameters)
{
	AJetMOCK* testJet = NewObject<AJetMOCK>();
	TestTrue(TEXT("The jet collision object type should be pawn."), testJet->meshCollisionIsPawn());

	return true;
}


bool FAJetHasCenterOfMassLoweredTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	ADD_LATENT_AUTOMATION_COMMAND(FSpawningAJet);

	ADD_LATENT_AUTOMATION_COMMAND(FCheckAJetCenterOfMass(this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FAJetFallingSpeedWhenSteeringSameAsNoSteeringTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	ADD_LATENT_AUTOMATION_COMMAND(FSpawningTwoJetsMakeOneOfThemItAccelerateAndSteerRight);
	int tickCount = 0;
	int tickLimit = 3;
	ADD_LATENT_AUTOMATION_COMMAND(FCheckAJetFallSpeed(tickCount, tickLimit, this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FAJetRotatesPitchRightWhenTiltedAndSteersRightTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));
	float roll = 30;
	ADD_LATENT_AUTOMATION_COMMAND(FSpawningAJetTiltItAndMakeItSteerRight(roll));
	int tickCount = 0;
	int tickLimit = 3;
	ADD_LATENT_AUTOMATION_COMMAND(FCheckAJetSteersAroundUpVector(tickCount, tickLimit, roll, this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FAJetAcceleratesOrthogonalToSurfaceNormalTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	ADD_LATENT_AUTOMATION_COMMAND(FSpawningAJetRotatedOverFloorAndAccelerateIt);
	int tickCount = 0;
	int tickLimit = 3;
	ADD_LATENT_AUTOMATION_COMMAND(FCheckAJetSpeedOrthogonalityToFloor(tickCount, tickLimit, this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FAJetSidewaysRejectsAFloorSidewaysTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	ADD_LATENT_AUTOMATION_COMMAND(FSpawningAJetAndFloorSideWays);
	int tickCount = 0;
	int tickLimit = 3;
	ADD_LATENT_AUTOMATION_COMMAND(FCheckAJetSidewaysRejectsFloor(tickCount, tickLimit, std::numeric_limits<float>::max(), this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FAJetBrakesOrthogonalToSurfaceNormalTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	ADD_LATENT_AUTOMATION_COMMAND(FSpawningAJetRotatedOverFloorAndBrakeIt);
	int tickCount = 0;
	int tickLimit = 3;
	ADD_LATENT_AUTOMATION_COMMAND(FCheckAJetSpeedOrthogonalityToFloor(tickCount, tickLimit, this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FAJetSteersOrthogonalToSurfaceNormalTest::RunTest(const FString& Parameters)
{

	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));

	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	ADD_LATENT_AUTOMATION_COMMAND(FSpawningAJetRotatedOverFloorAccelerateAndSteerItRight);
	int tickCount = 0;
	int tickLimit = 3;
	ADD_LATENT_AUTOMATION_COMMAND(FCheckAJetVelocityMagnitudeOrthogonalityToFloor(tickCount, tickLimit, this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FAJetReplicatesTest::RunTest(const FString& Parameters)
{
	AJet* testJet = NewObject<AJet>();
	TestTrue(TEXT("Jet should replicate to other objects."), testJet->GetIsReplicated());

	return true;
}


bool FAJetReplicatesMovementTest::RunTest(const FString& Parameters)
{
	AJet* testJet = NewObject<AJet>();
	TestTrue(TEXT("Jet should replicate to other objects."), testJet->IsReplicatingMovement());

	return true;
}


bool FAJetServerAccelerateReplicatesAccelerationTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));
	int32 numberOfPlayers = 2;
	EPlayNetMode networkMode = EPlayNetMode::PIE_ListenServer;

	ADD_LATENT_AUTOMATION_COMMAND(FStartNetworkedPIESession(numberOfPlayers, networkMode));

	ADD_LATENT_AUTOMATION_COMMAND(FServerSpawnJet(numberOfPlayers));

	int tickCount = 0;
	int tickLimit = 10;
	FVector previousLocation = FVector(1000);
	ADD_LATENT_AUTOMATION_COMMAND(FServerCheckJetAccelerated(tickCount, tickLimit, numberOfPlayers, previousLocation, this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FAJetServerAcceleratesWhenPressingAccelerationKeyTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));
	int32 numberOfPlayers = 2;
	EPlayNetMode networkMode = EPlayNetMode::PIE_ListenServer;

	ADD_LATENT_AUTOMATION_COMMAND(FStartNetworkedPIESession(numberOfPlayers, networkMode));

	ADD_LATENT_AUTOMATION_COMMAND(FServerSpawnJet(numberOfPlayers));

	ADD_LATENT_AUTOMATION_COMMAND(FClientPressKey(FName(TEXT("AccelerateAction")), numberOfPlayers));

	int tickCount = 0;
	int tickLimit = 10;
	FVector previousLocation = FVector(1000);
	ADD_LATENT_AUTOMATION_COMMAND(FServerCheckJetAccelerated(tickCount, tickLimit, numberOfPlayers, previousLocation, this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FAJetServerBrakeReplicatesBrakingTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));
	int32 numberOfPlayers = 2;
	EPlayNetMode networkMode = EPlayNetMode::PIE_ListenServer;

	ADD_LATENT_AUTOMATION_COMMAND(FStartNetworkedPIESession(numberOfPlayers, networkMode));

	ADD_LATENT_AUTOMATION_COMMAND(FServerSpawnJet(numberOfPlayers));

	int tickCount = 0;
	int tickLimit = 10;
	FVector previousLocation = FVector(1000);
	ADD_LATENT_AUTOMATION_COMMAND(FServerCheckJetBrake(tickCount, tickLimit, numberOfPlayers, previousLocation, this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FAJetServerBrakseWhenPressingBrakeKeyTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));
	int32 numberOfPlayers = 2;
	EPlayNetMode networkMode = EPlayNetMode::PIE_ListenServer;

	ADD_LATENT_AUTOMATION_COMMAND(FStartNetworkedPIESession(numberOfPlayers, networkMode));

	ADD_LATENT_AUTOMATION_COMMAND(FServerSpawnJet(numberOfPlayers));

	ADD_LATENT_AUTOMATION_COMMAND(FClientPressKey(FName(TEXT("BrakeAction")), numberOfPlayers));

	int tickCount = 0;
	int tickLimit = 10;
	FVector previousLocation = FVector(1000);
	ADD_LATENT_AUTOMATION_COMMAND(FServerCheckJetBrake(tickCount, tickLimit, numberOfPlayers, previousLocation, this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FAJetServerSteerReplicatesSteeringTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));
	int32 numberOfPlayers = 2;
	EPlayNetMode networkMode = EPlayNetMode::PIE_ListenServer;

	ADD_LATENT_AUTOMATION_COMMAND(FStartNetworkedPIESession(numberOfPlayers, networkMode));

	ADD_LATENT_AUTOMATION_COMMAND(FServerSpawnJetToSteer(numberOfPlayers));

	ADD_LATENT_AUTOMATION_COMMAND(FClientSteerJet(numberOfPlayers));

	int tickCount = 0;
	int tickLimit = 10;
	FVector previousLocation = FVector(1000);
	ADD_LATENT_AUTOMATION_COMMAND(FServerCheckJetSteer(tickCount, tickLimit, numberOfPlayers, previousLocation, this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FAJetServerSteersWhenPressingSteerKeyTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));
	int32 numberOfPlayers = 2;
	EPlayNetMode networkMode = EPlayNetMode::PIE_ListenServer;

	ADD_LATENT_AUTOMATION_COMMAND(FStartNetworkedPIESession(numberOfPlayers, networkMode));

	ADD_LATENT_AUTOMATION_COMMAND(FServerSpawnJetToSteer(numberOfPlayers));

	ADD_LATENT_AUTOMATION_COMMAND(FClientPressKey(FName(TEXT("SteerAction")), numberOfPlayers));

	int tickCount = 0;
	int tickLimit = 10;
	FVector previousLocation = FVector(1000);
	ADD_LATENT_AUTOMATION_COMMAND(FServerCheckJetSteer(tickCount, tickLimit, numberOfPlayers, previousLocation, this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}




#endif //WITH_DEV_AUTOMATION_TESTS