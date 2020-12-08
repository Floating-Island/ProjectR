// Fill out your copyright notice in the Description page of Project Settings.


#if WITH_DEV_AUTOMATION_TESTS

#include "JetTest.h"
#include "Commands/JetTestCommands.h"
#include "Jet/Jet.h"
#include "Mocks/JetMOCK.h"

//to be able to simulate:
#include "Tests/AutomationEditorCommon.h"



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

	ADD_LATENT_AUTOMATION_COMMAND(FSpawningAJetMakeItAccelerateCommand);
	int tickCount = 0;
	int tickLimit = 3;
	ADD_LATENT_AUTOMATION_COMMAND(FCheckAJetLocationCommand(tickCount, tickLimit, this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FAJetSpeedIncreasesWhenAcceleratesTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	ADD_LATENT_AUTOMATION_COMMAND(FSpawningAJetMakeItAccelerateCommand);
	int tickCount = 0;
	int tickLimit = 3;
	ADD_LATENT_AUTOMATION_COMMAND(FCheckAJetSpeedIncreaseCommand(tickCount, tickLimit, this));

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

	ADD_LATENT_AUTOMATION_COMMAND(FSpawningAJetMakeItBrakeCommand);
	int tickCount = 0;
	int tickLimit = 3;
	ADD_LATENT_AUTOMATION_COMMAND(FCheckAJetVelocityDecreaseCommand(tickCount, tickLimit, this));

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

	ADD_LATENT_AUTOMATION_COMMAND(FSpawningAJetSetVelocityToTopSpeedCommand);
	int tickCount = 0;
	int tickLimit = 3;
	ADD_LATENT_AUTOMATION_COMMAND(FCheckAJetSpeedAgainstTopSpeedCommand(tickCount, tickLimit, this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FAJetRotatesYawRightWhenSteeringRightTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	ADD_LATENT_AUTOMATION_COMMAND(FSpawningAJetMakeItSteerRightCommand);
	int tickCount = 0;
	int tickLimit = 3;
	ADD_LATENT_AUTOMATION_COMMAND(FCheckAJetRotatedYawCommand(tickCount, tickLimit, this));

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

	ADD_LATENT_AUTOMATION_COMMAND(FSpawningAJetPressAccelerationKeyCommand);
	int tickCount = 0;
	int tickLimit = 3;
	ADD_LATENT_AUTOMATION_COMMAND(FCheckAJetSpeedIncreaseCommand(tickCount, tickLimit, this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FAJetMovesRightWhenPressingSteerRightKeyTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld-JetMOCKTest");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	ADD_LATENT_AUTOMATION_COMMAND(FSpawningAJetPressSteerRightKeyCommand);
	int tickCount = 0;
	int tickLimit = 3;
	ADD_LATENT_AUTOMATION_COMMAND(FCheckAJetRotatedYawCommand(tickCount, tickLimit, this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FAJetBrakesWhenPressingBrakeKeyTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld-JetMOCKTest");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	ADD_LATENT_AUTOMATION_COMMAND(FSpawningAJetPressBrakeKeyCommand);
	int tickCount = 0;
	int tickLimit = 3;
	ADD_LATENT_AUTOMATION_COMMAND(FCheckAJetVelocityDecreaseCommand(tickCount, tickLimit, this));

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

	ADD_LATENT_AUTOMATION_COMMAND(FSpawningAJetSnapedToFloorCommand);
	int tickCount = 0;
	int tickLimit = 3;
	ADD_LATENT_AUTOMATION_COMMAND(FCheckAJetZLocationCommand(tickCount, tickLimit, this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FAJetAcceleratesAlongItsForwardVectorWhenAcceleratedAfterRotationTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	ADD_LATENT_AUTOMATION_COMMAND(FSpawningAJetRotateAndAccelerateCommand);
	int tickCount = 0;
	int tickLimit = 3;
	ADD_LATENT_AUTOMATION_COMMAND(FCheckAJetLocationCoincidentToForwardVectorCommand(tickCount, tickLimit, this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FAJetBrakesAlongItsBackwardsVectorWhileRotatedTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	ADD_LATENT_AUTOMATION_COMMAND(FSpawningAJetRotateAndBrakeCommand);
	int tickCount = 0;
	int tickLimit = 3;
	ADD_LATENT_AUTOMATION_COMMAND(FCheckAJetLocationParallelToForwardVectorCommand(tickCount, tickLimit, this));

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
//	ADD_LATENT_AUTOMATION_COMMAND(FSpawningAJetAccelerateAndSteerRightCommand);
//	int tickCount = 0;
//	int tickLimit = 3;
//	ADD_LATENT_AUTOMATION_COMMAND(FCheckAJetUpdatedVelocityWhenAfterSteeringCommand(tickCount, tickLimit, FVector(0), this));
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

	ADD_LATENT_AUTOMATION_COMMAND(FSpawningAJetBrakeAndSteerRightCommand);
	int tickCount = 0;
	int tickLimit = 3;
	ADD_LATENT_AUTOMATION_COMMAND(FCheckAJetInvertSteeringWhenInReverseCommand(tickCount, tickLimit, this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FAJetIsntAbleToSteerWhenIdleTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	ADD_LATENT_AUTOMATION_COMMAND(FSpawningAJeSteerRightWhenIdleCommand);
	int tickCount = 0;
	int tickLimit = 3;
	ADD_LATENT_AUTOMATION_COMMAND(FCheckAJetUnableToSteerWhenIdleCommand(tickCount, tickLimit, FRotator(0), this));

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

	ADD_LATENT_AUTOMATION_COMMAND(FSpawningAJetCommand);

	ADD_LATENT_AUTOMATION_COMMAND(FCheckAJetCenterOfMassCommand(this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FAJetFallingSpeedWhenSteeringSameAsNoSteeringTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	ADD_LATENT_AUTOMATION_COMMAND(FSpawningTwoJetsMakeOneOfThemItAccelerateAndSteerRightCommand);
	int tickCount = 0;
	int tickLimit = 3;
	ADD_LATENT_AUTOMATION_COMMAND(FCheckAJetFallSpeedCommand(tickCount, tickLimit, this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FAJetRotatesPitchRightWhenTiltedAndSteersRightTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));
	float roll = 30;
	ADD_LATENT_AUTOMATION_COMMAND(FSpawningAJetTiltItAndMakeItSteerRightCommand(roll));
	int tickCount = 0;
	int tickLimit = 3;
	ADD_LATENT_AUTOMATION_COMMAND(FCheckAJetSteersAroundUpVectorCommand(tickCount, tickLimit, roll, this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FAJetAcceleratesOrthogonalToSurfaceNormalTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	ADD_LATENT_AUTOMATION_COMMAND(FSpawningAJetRotatedOverFloorAndAccelerateItCommand);
	int tickCount = 0;
	int tickLimit = 3;
	ADD_LATENT_AUTOMATION_COMMAND(FCheckAJetSpeedOrthogonalityToFloorCommand(tickCount, tickLimit, this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FAJetSidewaysRejectsAFloorSidewaysTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	ADD_LATENT_AUTOMATION_COMMAND(FSpawningAJetAndFloorSideWaysCommand);
	int tickCount = 0;
	int tickLimit = 3;
	ADD_LATENT_AUTOMATION_COMMAND(FCheckAJetSidewaysRejectsFloorCommand(tickCount, tickLimit, std::numeric_limits<float>::max(), this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FAJetBrakesOrthogonalToSurfaceNormalTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	ADD_LATENT_AUTOMATION_COMMAND(FSpawningAJetRotatedOverFloorAndBrakeItCommand);
	int tickCount = 0;
	int tickLimit = 3;
	ADD_LATENT_AUTOMATION_COMMAND(FCheckAJetSpeedOrthogonalityToFloorCommand(tickCount, tickLimit, this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FAJetSteersOrthogonalToSurfaceNormalTest::RunTest(const FString& Parameters)
{

	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));

	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	ADD_LATENT_AUTOMATION_COMMAND(FSpawningAJetRotatedOverFloorAccelerateAndSteerItRightCommand);
	int tickCount = 0;
	int tickLimit = 3;
	ADD_LATENT_AUTOMATION_COMMAND(FCheckAJetVelocityMagnitudeOrthogonalityToFloorCommand(tickCount, tickLimit, this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);

	return true;
}



#endif //WITH_DEV_AUTOMATION_TESTS