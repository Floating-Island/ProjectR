// Fill out your copyright notice in the Description page of Project Settings.


#if WITH_DEV_AUTOMATION_TESTS

#include "JetTest.h"
#include "JetTestCommands.h"
#include "../../Commands/CommonPIECommands.h"
#include "Jet/Jet.h"
#include "../../Mocks/JetMOCK.h"
#include "Jet/MotorStates/AcceleratingMotorState.h"
#include "Jet/MotorStates/MixedMotorState.h"
#include "Jet/MotorStates/NeutralMotorState.h"
#include "Jet/MotorStates/ReversingMotorState.h"
#include "Jet/SteerStates/LeftSteerState.h"
#include "Jet/SteerStates/CenterSteerState.h"
#include "Jet/SteerStates/RightSteerState.h"

//to be able to simulate:
#include "Tests/AutomationEditorCommon.h"
#include "../../Commands/NetworkCommands.h"



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
	establishInitialMapDirectoryTo(FString("/Game/Tests/TestMaps/VoidWorld"));
	establishTestMessageTo(FString("The Jet X location should increase after an acceleration is added (after ticking)."));
	establishTickLimitTo(3);

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(retrieveInitialMapDirectory()));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	
	

	UClass* jetClass = AJet::StaticClass();
	ADD_LATENT_AUTOMATION_COMMAND(FSpawnInPIEAnActorOfClass(jetClass, FTransform()));
	ADD_LATENT_AUTOMATION_COMMAND(FRetrieveAJetMakeItAccelerate);

	ADD_LATENT_AUTOMATION_COMMAND(FCheckAJetLocation(this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FAJetSpeedIncreasesWhenAcceleratesTest::RunTest(const FString& Parameters)
{
	establishInitialMapDirectoryTo(FString("/Game/Tests/TestMaps/VoidWorld"));
	establishTestMessageTo(FString("The Jet speed should increase after accelerating (after ticking)."));
	establishTickLimitTo(3);

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(retrieveInitialMapDirectory()));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	
	

	UClass* jetClass = AJet::StaticClass();
	ADD_LATENT_AUTOMATION_COMMAND(FSpawnInPIEAnActorOfClass(jetClass, FTransform()));
	ADD_LATENT_AUTOMATION_COMMAND(FRetrieveAJetMakeItAccelerate);

	ADD_LATENT_AUTOMATION_COMMAND(FCheckAJetSpeedIncrease(this));

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
	establishInitialMapDirectoryTo(FString("/Game/Tests/TestMaps/VoidWorld"));
	establishTestMessageTo(FString("The Jet velocity should be negative after a brake (after ticking) from idle."));
	establishTickLimitTo(3);

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(retrieveInitialMapDirectory()));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	
	

	UClass* jetClass = AJet::StaticClass();
	ADD_LATENT_AUTOMATION_COMMAND(FSpawnInPIEAnActorOfClass(jetClass, FTransform()));
	ADD_LATENT_AUTOMATION_COMMAND(FRetrieveAJetMakeItBrake);

	ADD_LATENT_AUTOMATION_COMMAND(FCheckAJetVelocityDecrease(this));

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
	establishInitialMapDirectoryTo(FString("/Game/Tests/TestMaps/VoidWorld"));
	establishTestMessageTo(FString("If a jet is at top speed, it should never increase it after an acceleration is added (after ticking)."));
	establishTickLimitTo(3);

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(retrieveInitialMapDirectory()));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	
	

	UClass* jetClass = AJetMOCK::StaticClass();
	ADD_LATENT_AUTOMATION_COMMAND(FSpawnInPIEAnActorOfClass(jetClass, FTransform()));

	ADD_LATENT_AUTOMATION_COMMAND(FRetrieveAJetMOCKSetVelocityToTopSpeed);
	ADD_LATENT_AUTOMATION_COMMAND(FRetrieveAJetMakeItAccelerate);

	ADD_LATENT_AUTOMATION_COMMAND(FCheckAJetSpeedAgainstTopSpeed(this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FAJetRotatesYawRightWhenSteeringRightTest::RunTest(const FString& Parameters)
{
	establishInitialMapDirectoryTo(FString("/Game/Tests/TestMaps/VoidWorld"));
	establishTestMessageTo(FString("The Jet yaw rotation (around Z axis) should be greater than zero after steering right (after ticking)."));
	establishTickLimitTo(3);

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(retrieveInitialMapDirectory()));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	
	

	UClass* jetClass = AJetMOCK::StaticClass();
	ADD_LATENT_AUTOMATION_COMMAND(FSpawnInPIEAnActorOfClass(jetClass, FTransform()));
	float desiredSpeed = 10000;
	ADD_LATENT_AUTOMATION_COMMAND(FRetrieveAJetMOCKSetVelocityToDesiredSpeed(desiredSpeed));//to be able to steer...
	ADD_LATENT_AUTOMATION_COMMAND(FRetrieveAJetMakeItSteerRight);
	
	ADD_LATENT_AUTOMATION_COMMAND(FCheckAJetRotatedYawRight(this));

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
	establishInitialMapDirectoryTo(FString("/Game/Tests/TestMaps/VoidWorld-JetMOCKTest"));
	establishTestMessageTo(FString("The Jet speed should increase after pressing the accelerate action key."));
	establishTickLimitTo(3);

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(retrieveInitialMapDirectory()));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	
	

	ADD_LATENT_AUTOMATION_COMMAND(FSpawnLocalPlayerInPIE);
	ADD_LATENT_AUTOMATION_COMMAND(FRetrieveAJetAndPressActionKey(FName(TEXT("AccelerateAction"))));

	ADD_LATENT_AUTOMATION_COMMAND(FCheckAJetSpeedIncrease(this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FAJetMovesRightWhenPressingSteerRightKeyTest::RunTest(const FString& Parameters)
{
	establishInitialMapDirectoryTo(FString("/Game/Tests/TestMaps/VoidWorld-JetMOCKTest"));
	establishTestMessageTo(FString("The Jet speed should increase after pressing the steer right action key."));
	establishTickLimitTo(3);

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(retrieveInitialMapDirectory()));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	
	

	ADD_LATENT_AUTOMATION_COMMAND(FSpawnLocalPlayerInPIE);
	float desiredSpeed = 10000;
	ADD_LATENT_AUTOMATION_COMMAND(FRetrieveAJetMOCKSetVelocityToDesiredSpeed(desiredSpeed));
	ADD_LATENT_AUTOMATION_COMMAND(FRetrieveAJetAndPressActionKey(FName(TEXT("SteerRightAction"))));

	ADD_LATENT_AUTOMATION_COMMAND(FCheckAJetRotatedYawRight(this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FAJetBrakesWhenPressingBrakeKeyTest::RunTest(const FString& Parameters)
{
	establishInitialMapDirectoryTo(FString("/Game/Tests/TestMaps/VoidWorld-JetMOCKTest"));
	establishTestMessageTo(FString("The Jet speed should increase after pressing the brake action key."));
	establishTickLimitTo(3);

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(retrieveInitialMapDirectory()));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	
	

	ADD_LATENT_AUTOMATION_COMMAND(FSpawnLocalPlayerInPIE);
	ADD_LATENT_AUTOMATION_COMMAND(FRetrieveAJetAndPressActionKey(FName(TEXT("BrakeAction"))));
	
	ADD_LATENT_AUTOMATION_COMMAND(FCheckAJetVelocityDecrease(this));

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
	establishInitialMapDirectoryTo(FString("/Game/Tests/TestMaps/VoidWorld"));
	establishTestMessageTo(FString("The Jet Z veocity should increase due to anti-gravity activation near floor."));
	establishTickLimitTo(3);

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(retrieveInitialMapDirectory()));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	
	

	ADD_LATENT_AUTOMATION_COMMAND(FSpawningAJetSnapedToFloor);

	ADD_LATENT_AUTOMATION_COMMAND(FCheckAJetZLocation(this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FAJetAcceleratesAlongItsForwardVectorWhenAcceleratedAfterRotationTest::RunTest(const FString& Parameters)
{
	establishInitialMapDirectoryTo(FString("/Game/Tests/TestMaps/VoidWorld"));
	establishTestMessageTo(FString("The Jet should accelerate in the direction of it's forward vector after being rotated."));
	establishTickLimitTo(3);

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(retrieveInitialMapDirectory()));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	
	

	UClass* jetClass = AJet::StaticClass();
	ADD_LATENT_AUTOMATION_COMMAND(FSpawnInPIEAnActorOfClass(jetClass, FTransform()));
	ADD_LATENT_AUTOMATION_COMMAND(FRetrieveAJetAndRotateIt);
	ADD_LATENT_AUTOMATION_COMMAND(FRetrieveAJetMakeItAccelerate);
	
	ADD_LATENT_AUTOMATION_COMMAND(FCheckAJetLocationCoincidentToForwardVector(this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FAJetBrakesAlongItsBackwardsVectorWhileRotatedTest::RunTest(const FString& Parameters)
{
	establishInitialMapDirectoryTo(FString("/Game/Tests/TestMaps/VoidWorld"));
	establishTestMessageTo(FString("The Jet should brake contrary to the direction of it's forward vector after being rotated."));
	establishTickLimitTo(3);

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(retrieveInitialMapDirectory()));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	
	

	UClass* jetClass = AJet::StaticClass();
	ADD_LATENT_AUTOMATION_COMMAND(FSpawnInPIEAnActorOfClass(jetClass, FTransform()));
	ADD_LATENT_AUTOMATION_COMMAND(FRetrieveAJetAndRotateIt);
	ADD_LATENT_AUTOMATION_COMMAND(FRetrieveAJetMakeItBrake);

	ADD_LATENT_AUTOMATION_COMMAND(FCheckAJetLocationParallelToForwardVector(this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


//bool FAJetUpdatesVelocityDirectionAfterSteeringTest::RunTest(const FString& Parameters)
//{
//
//	establishInitialMapDirectoryTo(FString("/Game/Tests/TestMaps/VoidWorld"));
//	establishTestMessageTo(FString("The Jet should update it's velocity to match the direction of the forward vector after steering."));
//	establishTickLimitTo(3);
//
//	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(retrieveInitialMapDirectory()));
//	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));
//
//	
//	
//
//	ADD_LATENT_AUTOMATION_COMMAND(FSpawningAJetAccelerateAndSteerRight);

//	ADD_LATENT_AUTOMATION_COMMAND(FCheckAJetUpdatedVelocityWhenAfterSteering(FVector(0), this));
//
//	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
//
//	return true;
//}


bool FAJetInvertsSteeringWhenInReverseTest::RunTest(const FString& Parameters)
{
	establishInitialMapDirectoryTo(FString("/Game/Tests/TestMaps/VoidWorld"));
	establishTestMessageTo(FString("The Jet should steer right counterclockwise if it's in reverse."));
	establishTickLimitTo(3);

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(retrieveInitialMapDirectory()));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	
	

	UClass* jetClass = AJetMOCK::StaticClass();
	ADD_LATENT_AUTOMATION_COMMAND(FSpawnInPIEAnActorOfClass(jetClass, FTransform()));
	float desiredSpeed = -10000;
	ADD_LATENT_AUTOMATION_COMMAND(FRetrieveAJetMOCKSetVelocityToDesiredSpeed(desiredSpeed));
	ADD_LATENT_AUTOMATION_COMMAND(FRetrieveAJetMakeItSteerRight);

	ADD_LATENT_AUTOMATION_COMMAND(FCheckAJetInvertSteeringWhenInReverse(this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FAJetIsntAbleToSteerWhenIdleTest::RunTest(const FString& Parameters)
{
	establishInitialMapDirectoryTo(FString("/Game/Tests/TestMaps/VoidWorld"));
	establishTestMessageTo(FString("The Jet should update it's velocity to match the direction of the forward vector after steering."));
	establishTickLimitTo(3);

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(retrieveInitialMapDirectory()));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	
	

	UClass* jetClass = AJetMOCK::StaticClass();
	ADD_LATENT_AUTOMATION_COMMAND(FSpawnInPIEAnActorOfClass(jetClass, FTransform()));
	ADD_LATENT_AUTOMATION_COMMAND(FRetrieveAJetMakeItSteerRight);

	ADD_LATENT_AUTOMATION_COMMAND(FCheckAJetUnableToSteerWhenIdle(FRotator(0), this));

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

	UClass* jetClass = AJetMOCK::StaticClass();
	ADD_LATENT_AUTOMATION_COMMAND(FSpawnInPIEAnActorOfClass(jetClass, FTransform()));

	ADD_LATENT_AUTOMATION_COMMAND(FCheckAJetCenterOfMass(this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FAJetFallingSpeedWhenSteeringSameAsNoSteeringTest::RunTest(const FString& Parameters)
{
	establishInitialMapDirectoryTo(FString("/Game/Tests/TestMaps/VoidWorld"));
	establishTestMessageTo(FString("The Jet should keep falling even if it's steering."));
	establishTickLimitTo(3);

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(retrieveInitialMapDirectory()));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	
	

	ADD_LATENT_AUTOMATION_COMMAND(FSpawningTwoJetsMakeOneOfThemItAccelerateAndSteerRight);

	ADD_LATENT_AUTOMATION_COMMAND(FCheckAJetFallSpeed(this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FAJetRotatesPitchRightWhenTiltedAndSteersRightTest::RunTest(const FString& Parameters)
{
	establishInitialMapDirectoryTo(FString("/Game/Tests/TestMaps/VoidWorld"));
	establishTestMessageTo(FString("The Jet pitch rotation should be greater than zero after being tilted and steered."));
	establishTickLimitTo(3);

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(retrieveInitialMapDirectory()));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	
	
	
	float roll = 30;
	ADD_LATENT_AUTOMATION_COMMAND(FSpawningAJetTiltItAndMakeItSteerRight(roll));

	ADD_LATENT_AUTOMATION_COMMAND(FCheckAJetSteersAroundUpVector(roll, this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FAJetAcceleratesOrthogonalToSurfaceNormalTest::RunTest(const FString& Parameters)
{
	establishInitialMapDirectoryTo(FString("/Game/Tests/TestMaps/VoidWorld"));
	establishTestMessageTo(FString("The Jet should move parallel to the floor. Then, the speed, floor speed and velocity magnitude (gravity is being canceled) should be the same."));
	establishTickLimitTo(3);

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(retrieveInitialMapDirectory()));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	
	

	ADD_LATENT_AUTOMATION_COMMAND(FSpawningAJetRotatedOverFloorAndAccelerateIt);

	ADD_LATENT_AUTOMATION_COMMAND(FCheckAJetSpeedOrthogonalityToFloor(this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FAJetSidewaysRejectsAFloorSidewaysTest::RunTest(const FString& Parameters)
{
	establishInitialMapDirectoryTo(FString("/Game/Tests/TestMaps/VoidWorld"));
	establishTestMessageTo(FString("The jet should reject the nearest floor along the floor up vector."));
	establishTickLimitTo(3);

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(retrieveInitialMapDirectory()));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	
	

	ADD_LATENT_AUTOMATION_COMMAND(FSpawningAJetAndFloorSideWays);

	ADD_LATENT_AUTOMATION_COMMAND(FCheckAJetSidewaysRejectsFloor(std::numeric_limits<float>::max(), this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FAJetBrakesOrthogonalToSurfaceNormalTest::RunTest(const FString& Parameters)
{
	establishInitialMapDirectoryTo(FString("/Game/Tests/TestMaps/VoidWorld"));
	establishTestMessageTo(FString("The Jet should move parallel to the floor. Then, the floor speed and velocity magnitude (gravity is being canceled) should be the same."));
	establishTickLimitTo(3);

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(retrieveInitialMapDirectory()));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	
	

	ADD_LATENT_AUTOMATION_COMMAND(FSpawningAJetRotatedOverFloorAndBrakeIt);

	ADD_LATENT_AUTOMATION_COMMAND(FCheckAJetSpeedOrthogonalityToFloor(this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FAJetSteersOrthogonalToSurfaceNormalTest::RunTest(const FString& Parameters)
{
	establishInitialMapDirectoryTo(FString("/Game/Tests/TestMaps/VoidWorld"));
	establishTestMessageTo(FString("The Jet should move parallel to the floor. Then, the speed, floor speed and velocity magnitude (gravity is being canceled) should be the same."));
	establishTickLimitTo(3);

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(retrieveInitialMapDirectory()));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	
	

	ADD_LATENT_AUTOMATION_COMMAND(FSpawningAJetRotatedOverFloorAccelerateAndSteerItRight);

	ADD_LATENT_AUTOMATION_COMMAND(FCheckAJetVelocityMagnitudeOrthogonalityToFloor(this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FAJetReplicatesTest::RunTest(const FString& Parameters)
{
	AJet* testJet = NewObject<AJet>();
	TestTrue(TEXT("Jet should replicate to other objects."), testJet->GetIsReplicated());

	return true;
}


bool FAJetDoesntReplicateMovementTest::RunTest(const FString& Parameters)
{
	AJet* testJet = NewObject<AJet>();
	TestTrue(TEXT("Jet shouldn't replicate movement to other objects."), testJet->IsReplicatingMovement());

	return true;
}


bool FAJetServerAccelerateReplicatesAccelerationTest::RunTest(const FString& Parameters)
{
	establishInitialMapDirectoryTo(FString("/Game/Tests/TestMaps/VoidWorld"));
	establishTestMessageTo(FString("The Jet should replicate its acceleration action to other clients when using accelerate."));
	establishTickLimitTo(10);

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(retrieveInitialMapDirectory()));
	int32 numberOfPlayers = 2;
	EPlayNetMode networkMode = EPlayNetMode::PIE_ListenServer;

	ADD_LATENT_AUTOMATION_COMMAND(FStartNetworkedPIESession(numberOfPlayers, networkMode));

	
	

	UClass* jetClass = AJet::StaticClass();
	FVector jetLocation = FVector(1000);
	FTransform jetTransform = FTransform();
	jetTransform.SetLocation(jetLocation);
	ADD_LATENT_AUTOMATION_COMMAND(FServerSpawnPawnOfClass(jetClass, jetTransform, numberOfPlayers));

	FVector previousLocation = FVector(1000);
	ADD_LATENT_AUTOMATION_COMMAND(FServerCheckJetAccelerated(numberOfPlayers, previousLocation, this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FAJetServerAcceleratesWhenPressingAccelerationKeyTest::RunTest(const FString& Parameters)
{
	establishInitialMapDirectoryTo(FString("/Game/Tests/TestMaps/VoidWorld"));
	establishTestMessageTo(FString("The Jet should replicate its acceleration action to other clients when using accelerate."));
	establishTickLimitTo(10);

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(retrieveInitialMapDirectory()));
	int32 numberOfPlayers = 2;
	EPlayNetMode networkMode = EPlayNetMode::PIE_ListenServer;

	ADD_LATENT_AUTOMATION_COMMAND(FStartNetworkedPIESession(numberOfPlayers, networkMode));

	
	

	UClass* jetClass = AJet::StaticClass();
	FVector jetLocation = FVector(1000);
	FTransform jetTransform = FTransform();
	jetTransform.SetLocation(jetLocation);
	ADD_LATENT_AUTOMATION_COMMAND(FServerSpawnPawnOfClass(jetClass, jetTransform, numberOfPlayers));

	ADD_LATENT_AUTOMATION_COMMAND(FClientPressActionKey(FName(TEXT("AccelerateAction")), numberOfPlayers));

	FVector previousLocation = FVector(1000);
	ADD_LATENT_AUTOMATION_COMMAND(FServerCheckJetAccelerated(numberOfPlayers, previousLocation, this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FAJetServerBrakeReplicatesBrakingTest::RunTest(const FString& Parameters)
{
	establishInitialMapDirectoryTo(FString("/Game/Tests/TestMaps/VoidWorld"));
	establishTestMessageTo(FString("The Jet should replicate its braking action to other clients when using brake."));
	establishTickLimitTo(10);

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(retrieveInitialMapDirectory()));
	int32 numberOfPlayers = 2;
	EPlayNetMode networkMode = EPlayNetMode::PIE_ListenServer;

	ADD_LATENT_AUTOMATION_COMMAND(FStartNetworkedPIESession(numberOfPlayers, networkMode));

	
	

	UClass* jetClass = AJet::StaticClass();
	FVector jetLocation = FVector(1000);
	FTransform jetTransform = FTransform();
	jetTransform.SetLocation(jetLocation);
	ADD_LATENT_AUTOMATION_COMMAND(FServerSpawnPawnOfClass(jetClass, jetTransform, numberOfPlayers));

	FVector previousLocation = FVector(1000);
	ADD_LATENT_AUTOMATION_COMMAND(FServerCheckJetBrake(numberOfPlayers, previousLocation, this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FAJetServerBrakesWhenPressingBrakeKeyTest::RunTest(const FString& Parameters)
{
	establishInitialMapDirectoryTo(FString("/Game/Tests/TestMaps/VoidWorld"));
	establishTestMessageTo(FString("The Jet should replicate its braking action to other clients when using brake."));
	establishTickLimitTo(10);

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(retrieveInitialMapDirectory()));
	int32 numberOfPlayers = 2;
	EPlayNetMode networkMode = EPlayNetMode::PIE_ListenServer;

	ADD_LATENT_AUTOMATION_COMMAND(FStartNetworkedPIESession(numberOfPlayers, networkMode));

	
	

	UClass* jetClass = AJet::StaticClass();
	FVector jetLocation = FVector(1000);
	FTransform jetTransform = FTransform();
	jetTransform.SetLocation(jetLocation);
	ADD_LATENT_AUTOMATION_COMMAND(FServerSpawnPawnOfClass(jetClass, jetTransform, numberOfPlayers));

	ADD_LATENT_AUTOMATION_COMMAND(FClientPressActionKey(FName(TEXT("BrakeAction")), numberOfPlayers));

	FVector previousLocation = FVector(1000);
	ADD_LATENT_AUTOMATION_COMMAND(FServerCheckJetBrake(numberOfPlayers, previousLocation, this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FAJetRightSteerReplicatesRightSteeringTest::RunTest(const FString& Parameters)
{
	establishInitialMapDirectoryTo(FString("/Game/Tests/TestMaps/VoidWorld"));
	establishTestMessageTo(FString("The Jet should replicate its steering action to other clients when using steerRight."));
	establishTickLimitTo(10);
	
	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(retrieveInitialMapDirectory()));
	int32 numberOfPlayers = 2;
	EPlayNetMode networkMode = EPlayNetMode::PIE_ListenServer;

	ADD_LATENT_AUTOMATION_COMMAND(FStartNetworkedPIESession(numberOfPlayers, networkMode));

	
	

	UClass* jetClass = AJetMOCK::StaticClass();
	FVector jetLocation = FVector(1000);
	FTransform jetTransform = FTransform();
	jetTransform.SetLocation(jetLocation);
	ADD_LATENT_AUTOMATION_COMMAND(FServerSpawnPawnOfClass(jetClass, jetTransform, numberOfPlayers));
	ADD_LATENT_AUTOMATION_COMMAND(FServerRetrieveJetMOCKAndSetTopSpeed(numberOfPlayers));

	ADD_LATENT_AUTOMATION_COMMAND(FClientSteerRightJet(numberOfPlayers));

	FVector previousLocation = FVector(1000);
	ADD_LATENT_AUTOMATION_COMMAND(FServerCheckJetSteer(numberOfPlayers, previousLocation, this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FAJetServerSteersToRightWhenPressingSteerKeyTest::RunTest(const FString& Parameters)
{
	establishInitialMapDirectoryTo(FString("/Game/Tests/TestMaps/VoidWorld"));
	establishTestMessageTo(FString("The Jet should replicate its steering action to other clients when using steerRight."));
	establishTickLimitTo(10);
	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(retrieveInitialMapDirectory()));
	int32 numberOfPlayers = 2;
	EPlayNetMode networkMode = EPlayNetMode::PIE_ListenServer;

	ADD_LATENT_AUTOMATION_COMMAND(FStartNetworkedPIESession(numberOfPlayers, networkMode));

	
	

	UClass* jetClass = AJetMOCK::StaticClass();
	FVector jetLocation = FVector(1000);
	FTransform jetTransform = FTransform();
	jetTransform.SetLocation(jetLocation);
	ADD_LATENT_AUTOMATION_COMMAND(FServerSpawnPawnOfClass(jetClass, jetTransform, numberOfPlayers));
	ADD_LATENT_AUTOMATION_COMMAND(FServerRetrieveJetMOCKAndSetTopSpeed(numberOfPlayers));

	ADD_LATENT_AUTOMATION_COMMAND(FClientPressActionKey(FName(TEXT("SteerRightAction")), numberOfPlayers));

	FVector previousLocation = FVector(1000);
	ADD_LATENT_AUTOMATION_COMMAND(FServerCheckJetSteer(numberOfPlayers, previousLocation, this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FAJetNeutralizesMotorManagerWhenReleasingAccelerateKeyTest::RunTest(const FString& Parameters)
{
	establishInitialMapDirectoryTo(FString("/Game/Tests/TestMaps/VoidWorld-JetMOCKTest"));
	UClass* expectedMotorStateClass = UNeutralMotorState::StaticClass();
	establishTestMessageTo((FString("The Jet motor state should be %s."), *expectedMotorStateClass->GetName()));
	establishTickLimitTo(3);

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(retrieveInitialMapDirectory()));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	
	

	ADD_LATENT_AUTOMATION_COMMAND(FSpawnLocalPlayerInPIE);
	ADD_LATENT_AUTOMATION_COMMAND(FRetrieveAJetMOCKSetMotorManagerMOCKAndSetAcceleratingMotorState);
	ADD_LATENT_AUTOMATION_COMMAND(FRetrieveAJetAndReleaseActionKey(FName(TEXT("AccelerateAction"))));

	ADD_LATENT_AUTOMATION_COMMAND(FCheckAJetToExpectedMotorState(expectedMotorStateClass, this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FAJetNeutralizesMotorManagerWhenReleasingBrakeKeyTest::RunTest(const FString& Parameters)
{
	establishInitialMapDirectoryTo(FString("/Game/Tests/TestMaps/VoidWorld-JetMOCKTest"));
	UClass* expectedMotorStateClass = UNeutralMotorState::StaticClass();
	establishTestMessageTo((FString("The Jet motor state should be %s."), *expectedMotorStateClass->GetName()));
	establishTickLimitTo(3);

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(retrieveInitialMapDirectory()));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	
	

	ADD_LATENT_AUTOMATION_COMMAND(FSpawnLocalPlayerInPIE);
	ADD_LATENT_AUTOMATION_COMMAND(FRetrieveAJetMOCKSetMotorManagerMOCKAndSetAcceleratingMotorState);
	ADD_LATENT_AUTOMATION_COMMAND(FRetrieveAJetAndReleaseActionKey(FName(TEXT("BrakeAction"))));

	ADD_LATENT_AUTOMATION_COMMAND(FCheckAJetToExpectedMotorState(expectedMotorStateClass, this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FAJetServerNeutralizesWhenReleasingAccelerationKeyTest::RunTest(const FString& Parameters)
{
	establishInitialMapDirectoryTo(FString("/Game/Tests/TestMaps/VoidWorld"));
	UClass* expectedMotorStateClass = UNeutralMotorState::StaticClass();
	establishTestMessageTo((FString("The server should replicate its state to %s."), *expectedMotorStateClass->GetName()));
	establishTickLimitTo(10);

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(retrieveInitialMapDirectory()));
	int32 numberOfPlayers = 2;
	EPlayNetMode networkMode = EPlayNetMode::PIE_ListenServer;

	ADD_LATENT_AUTOMATION_COMMAND(FStartNetworkedPIESession(numberOfPlayers, networkMode));

	
	

	UClass* jetClass = AJetMOCK::StaticClass();
	ADD_LATENT_AUTOMATION_COMMAND(FServerSpawnPawnOfClass(jetClass, FTransform(), numberOfPlayers));
	ADD_LATENT_AUTOMATION_COMMAND(FServerRetrieveJetMOCKAndSetStateManagerMocks(numberOfPlayers));

	ADD_LATENT_AUTOMATION_COMMAND(FClientReleaseActionKey(FName(TEXT("AccelerateAction")), numberOfPlayers));

	ADD_LATENT_AUTOMATION_COMMAND(FServerCheckJetExpectedMotorState(expectedMotorStateClass, numberOfPlayers, this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FAJetServerNeutralizesWhenReleasingBrakeKeyTest::RunTest(const FString& Parameters)
{
	establishInitialMapDirectoryTo(FString("/Game/Tests/TestMaps/VoidWorld"));
	UClass* expectedMotorStateClass = UNeutralMotorState::StaticClass();
	establishTestMessageTo((FString("The server should replicate its state to %s."), *expectedMotorStateClass->GetName()));
	establishTickLimitTo(10);

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(retrieveInitialMapDirectory()));
	int32 numberOfPlayers = 2;
	EPlayNetMode networkMode = EPlayNetMode::PIE_ListenServer;

	ADD_LATENT_AUTOMATION_COMMAND(FStartNetworkedPIESession(numberOfPlayers, networkMode));

	
	

	UClass* jetClass = AJetMOCK::StaticClass();
	ADD_LATENT_AUTOMATION_COMMAND(FServerSpawnPawnOfClass(jetClass, FTransform(), numberOfPlayers));
	ADD_LATENT_AUTOMATION_COMMAND(FServerRetrieveJetMOCKAndSetStateManagerMocks(numberOfPlayers));

	ADD_LATENT_AUTOMATION_COMMAND(FClientReleaseActionKey(FName(TEXT("BrakeAction")), numberOfPlayers));

	ADD_LATENT_AUTOMATION_COMMAND(FServerCheckJetExpectedMotorState(expectedMotorStateClass, numberOfPlayers, this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FAJetMixesItsMotorStateWhenPressingAccelerationAndBrakeKeyTest::RunTest(const FString& Parameters)
{
	establishInitialMapDirectoryTo(FString("/Game/Tests/TestMaps/VoidWorld-JetMOCKTest"));
	UClass* expectedMotorStateClass = UMixedMotorState::StaticClass();
	establishTestMessageTo((FString("The Jet motor state should be %s."), *expectedMotorStateClass->GetName()));
	establishTickLimitTo(3);

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(retrieveInitialMapDirectory()));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	
	

	ADD_LATENT_AUTOMATION_COMMAND(FSpawnLocalPlayerInPIE);
	ADD_LATENT_AUTOMATION_COMMAND(FRetrieveAJetMOCKSetMotorManagerMOCKAndSetAcceleratingMotorState);
	ADD_LATENT_AUTOMATION_COMMAND(FRetrieveAJetAndPressActionKey(FName(TEXT("AccelerateAction"))));
	ADD_LATENT_AUTOMATION_COMMAND(FRetrieveAJetAndPressActionKey(FName(TEXT("BrakeAction"))));
	
	ADD_LATENT_AUTOMATION_COMMAND(FCheckAJetToExpectedMotorState(expectedMotorStateClass, this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FAJetMixesItsMotorStateWhenPressingBrakeAndAccelerationKeyTest::RunTest(const FString& Parameters)
{
	establishInitialMapDirectoryTo(FString("/Game/Tests/TestMaps/VoidWorld-JetMOCKTest"));
	UClass* expectedMotorStateClass = UMixedMotorState::StaticClass();
	establishTestMessageTo((FString("The Jet motor state should be %s."), *expectedMotorStateClass->GetName()));
	establishTickLimitTo(3);

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(retrieveInitialMapDirectory()));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	
	

	ADD_LATENT_AUTOMATION_COMMAND(FSpawnLocalPlayerInPIE);
	ADD_LATENT_AUTOMATION_COMMAND(FRetrieveAJetMOCKSetMotorManagerMOCKAndSetAcceleratingMotorState);
	ADD_LATENT_AUTOMATION_COMMAND(FRetrieveAJetAndPressActionKey(FName(TEXT("BrakeAction"))));
	ADD_LATENT_AUTOMATION_COMMAND(FRetrieveAJetAndPressActionKey(FName(TEXT("AccelerateAction"))));
	
	ADD_LATENT_AUTOMATION_COMMAND(FCheckAJetToExpectedMotorState(expectedMotorStateClass, this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FAJetServerMixesWhenPressingAccelerationAndBrakeKeyTest::RunTest(const FString& Parameters)
{
	establishInitialMapDirectoryTo(FString("/Game/Tests/TestMaps/VoidWorld"));
	UClass* expectedMotorStateClass = UMixedMotorState::StaticClass();
	establishTestMessageTo((FString("The server should replicate its state to %s."), *expectedMotorStateClass->GetName()));
	establishTickLimitTo(10);

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(retrieveInitialMapDirectory()));
	int32 numberOfPlayers = 2;
	EPlayNetMode networkMode = EPlayNetMode::PIE_ListenServer;

	ADD_LATENT_AUTOMATION_COMMAND(FStartNetworkedPIESession(numberOfPlayers, networkMode));

	
	

	UClass* jetClass = AJetMOCK::StaticClass();
	ADD_LATENT_AUTOMATION_COMMAND(FServerSpawnPawnOfClass(jetClass, FTransform(), numberOfPlayers));
	ADD_LATENT_AUTOMATION_COMMAND(FServerRetrieveJetMOCKAndSetStateManagerMocks(numberOfPlayers));

	ADD_LATENT_AUTOMATION_COMMAND(FClientPressActionKey(FName(TEXT("AccelerateAction")), numberOfPlayers));
	ADD_LATENT_AUTOMATION_COMMAND(FClientPressActionKey(FName(TEXT("BrakeAction")), numberOfPlayers));

	ADD_LATENT_AUTOMATION_COMMAND(FServerCheckJetExpectedMotorState(expectedMotorStateClass, numberOfPlayers, this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FAJetReversesItsMotorStateWhenBrakeKeyIsPressedAndAccelerateReleasedTest::RunTest(const FString& Parameters)
{
	establishInitialMapDirectoryTo(FString("/Game/Tests/TestMaps/VoidWorld-JetMOCKTest"));
	UClass* expectedMotorStateClass = UReversingMotorState::StaticClass();
	establishTestMessageTo((FString("The Jet motor state should be %s."), *expectedMotorStateClass->GetName()));
	establishTickLimitTo(3);

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(retrieveInitialMapDirectory()));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	
	

	ADD_LATENT_AUTOMATION_COMMAND(FSpawnLocalPlayerInPIE);
	ADD_LATENT_AUTOMATION_COMMAND(FRetrieveAJetMOCKSetMotorManagerMOCKAndSetAcceleratingMotorState);
	ADD_LATENT_AUTOMATION_COMMAND(FRetrieveAJetAndPressActionKey(FName(TEXT("BrakeAction"))));
	ADD_LATENT_AUTOMATION_COMMAND(FRetrieveAJetAndReleaseActionKey(FName(TEXT("AccelerateAction"))));
	
	ADD_LATENT_AUTOMATION_COMMAND(FCheckAJetToExpectedMotorState(expectedMotorStateClass, this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FAJetAcceleratesItsMotorStateWhenAccelerateKeyIsPressedAndBrakeReleasedTest::RunTest(const FString& Parameters)
{
	establishInitialMapDirectoryTo(FString("/Game/Tests/TestMaps/VoidWorld-JetMOCKTest"));
	UClass* expectedMotorStateClass = UAcceleratingMotorState::StaticClass();
	establishTestMessageTo((FString("The Jet motor state should be %s."), *expectedMotorStateClass->GetName()));
	establishTickLimitTo(3);

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(retrieveInitialMapDirectory()));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	
	

	ADD_LATENT_AUTOMATION_COMMAND(FSpawnLocalPlayerInPIE);
	ADD_LATENT_AUTOMATION_COMMAND(FRetrieveAJetMOCKSetMotorManagerMOCKAndSetAcceleratingMotorState);
	ADD_LATENT_AUTOMATION_COMMAND(FRetrieveAJetAndPressActionKey(FName(TEXT("AccelerateAction"))));
	ADD_LATENT_AUTOMATION_COMMAND(FRetrieveAJetAndReleaseActionKey(FName(TEXT("BrakeAction"))));
	
	ADD_LATENT_AUTOMATION_COMMAND(FCheckAJetToExpectedMotorState(expectedMotorStateClass, this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FAJetServerReversesWhenBrakeKeyIsPressedAndAccelerateReleasedTest::RunTest(const FString& Parameters)
{
	establishInitialMapDirectoryTo(FString("/Game/Tests/TestMaps/VoidWorld"));
	UClass* expectedMotorStateClass = UReversingMotorState::StaticClass();
	establishTestMessageTo((FString("The server should replicate its state to %s."), *expectedMotorStateClass->GetName()));
	establishTickLimitTo(10);

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(retrieveInitialMapDirectory()));
	int32 numberOfPlayers = 2;
	EPlayNetMode networkMode = EPlayNetMode::PIE_ListenServer;

	ADD_LATENT_AUTOMATION_COMMAND(FStartNetworkedPIESession(numberOfPlayers, networkMode));

	
	

	UClass* jetClass = AJetMOCK::StaticClass();
	ADD_LATENT_AUTOMATION_COMMAND(FServerSpawnPawnOfClass(jetClass, FTransform(), numberOfPlayers));
	ADD_LATENT_AUTOMATION_COMMAND(FServerRetrieveJetMOCKAndSetStateManagerMocks(numberOfPlayers));

	ADD_LATENT_AUTOMATION_COMMAND(FClientPressActionKey(FName(TEXT("BrakeAction")), numberOfPlayers));
	ADD_LATENT_AUTOMATION_COMMAND(FClientReleaseActionKey(FName(TEXT("AccelerateAction")), numberOfPlayers));
	
	ADD_LATENT_AUTOMATION_COMMAND(FServerCheckJetExpectedMotorState(expectedMotorStateClass, numberOfPlayers, this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FAJetServerAcceleratesWhenAccelerateKeyIsPressedAndBrakeReleasedTest::RunTest(const FString& Parameters)
{
	establishInitialMapDirectoryTo(FString("/Game/Tests/TestMaps/VoidWorld"));
	UClass* expectedMotorStateClass = UAcceleratingMotorState::StaticClass();
	establishTestMessageTo((FString("The server should replicate its state to %s."), *expectedMotorStateClass->GetName()));
	establishTickLimitTo(10);

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(retrieveInitialMapDirectory()));
	int32 numberOfPlayers = 2;
	EPlayNetMode networkMode = EPlayNetMode::PIE_ListenServer;

	ADD_LATENT_AUTOMATION_COMMAND(FStartNetworkedPIESession(numberOfPlayers, networkMode));

	
	

	UClass* jetClass = AJetMOCK::StaticClass();
	ADD_LATENT_AUTOMATION_COMMAND(FServerSpawnPawnOfClass(jetClass, FTransform(), numberOfPlayers));
	ADD_LATENT_AUTOMATION_COMMAND(FServerRetrieveJetMOCKAndSetStateManagerMocks(numberOfPlayers));

	ADD_LATENT_AUTOMATION_COMMAND(FClientPressActionKey(FName(TEXT("AccelerateAction")), numberOfPlayers));
	ADD_LATENT_AUTOMATION_COMMAND(FClientReleaseActionKey(FName(TEXT("BrakeAction")), numberOfPlayers));

	ADD_LATENT_AUTOMATION_COMMAND(FServerCheckJetExpectedMotorState(expectedMotorStateClass, numberOfPlayers, this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FAJetRotatesYawLeftWhenSteeringLeftTest::RunTest(const FString& Parameters)
{
	establishInitialMapDirectoryTo(FString("/Game/Tests/TestMaps/VoidWorld"));
	establishTestMessageTo(FString("The Jet yaw rotation (around Z axis) should be greater than zero after steering right (after ticking)."));
	establishTickLimitTo(3);

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(retrieveInitialMapDirectory()));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	
	
	
	UClass* jetClass = AJetMOCK::StaticClass();
	ADD_LATENT_AUTOMATION_COMMAND(FSpawnInPIEAnActorOfClass(jetClass, FTransform()));
	float desiredSpeed = 10000;
	ADD_LATENT_AUTOMATION_COMMAND(FRetrieveAJetMOCKSetVelocityToDesiredSpeed(desiredSpeed));
	ADD_LATENT_AUTOMATION_COMMAND(FRetrieveAJetMakeItSteerLeft);

	ADD_LATENT_AUTOMATION_COMMAND(FCheckAJetRotatedYawLeft(this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FAJetChangesToLeftSteerStateWhenPressingSteerLeftKeyTest::RunTest(const FString& Parameters)
{
	establishInitialMapDirectoryTo(FString("/Game/Tests/TestMaps/VoidWorld-JetMOCKTest"));
	UClass* expectedSteerStateClass = ULeftSteerState::StaticClass();
	establishTestMessageTo((FString("The Jet steer state should be %s."), *expectedSteerStateClass->GetName()));
	establishTickLimitTo(3);

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(retrieveInitialMapDirectory()));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	
	

	ADD_LATENT_AUTOMATION_COMMAND(FSpawnLocalPlayerInPIE);
	ADD_LATENT_AUTOMATION_COMMAND(FRetrieveAJetMOCKSetSteerManagerMOCK);
	ADD_LATENT_AUTOMATION_COMMAND(FRetrieveAJetAndPressActionKey(FName(TEXT("SteerLeftAction"))));
	
	ADD_LATENT_AUTOMATION_COMMAND(FCheckAJetToExpectedSteerState(expectedSteerStateClass, this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FAJetChangesToCenterSteerStateWhenReleasingSteerLeftKeyTest::RunTest(const FString& Parameters)
{
	establishInitialMapDirectoryTo(FString("/Game/Tests/TestMaps/VoidWorld-JetMOCKTest"));
	UClass* expectedSteerStateClass = UCenterSteerState::StaticClass();
	establishTestMessageTo((FString("The Jet steer state should be %s."), *expectedSteerStateClass->GetName()));
	establishTickLimitTo(3);

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(retrieveInitialMapDirectory()));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	
	

	ADD_LATENT_AUTOMATION_COMMAND(FSpawnLocalPlayerInPIE);
	ADD_LATENT_AUTOMATION_COMMAND(FRetrieveAJetMOCKSetSteerManagerMOCK);
	ADD_LATENT_AUTOMATION_COMMAND(FRetrieveAJetAndReleaseActionKey(FName(TEXT("SteerLeftAction"))));
	
	ADD_LATENT_AUTOMATION_COMMAND(FCheckAJetToExpectedSteerState(expectedSteerStateClass, this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FAJetChangesToCenterSteerStateWhenReleasingSteerRightKeyTest::RunTest(const FString& Parameters)
{
	establishInitialMapDirectoryTo(FString("/Game/Tests/TestMaps/VoidWorld-JetMOCKTest"));
	UClass* expectedSteerStateClass = UCenterSteerState::StaticClass();
	establishTestMessageTo((FString("The Jet steer state should be %s."), *expectedSteerStateClass->GetName()));
	establishTickLimitTo(3);

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(retrieveInitialMapDirectory()));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	
	

	ADD_LATENT_AUTOMATION_COMMAND(FSpawnLocalPlayerInPIE);
	ADD_LATENT_AUTOMATION_COMMAND(FRetrieveAJetMOCKSetSteerManagerMOCK);
	ADD_LATENT_AUTOMATION_COMMAND(FRetrieveAJetAndReleaseActionKey(FName(TEXT("SteerRightAction"))));
	
	ADD_LATENT_AUTOMATION_COMMAND(FCheckAJetToExpectedSteerState(expectedSteerStateClass, this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FAJetChangesToLeftSteerStateWhenReleasingSteerRightKeyAndSteerLeftIsPressedTest::RunTest(const FString& Parameters)
{
	establishInitialMapDirectoryTo(FString("/Game/Tests/TestMaps/VoidWorld-JetMOCKTest"));
	UClass* expectedSteerStateClass = ULeftSteerState::StaticClass();
	establishTestMessageTo((FString("The Jet steer state should be %s."), *expectedSteerStateClass->GetName()));
	establishTickLimitTo(3);

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(retrieveInitialMapDirectory()));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	
	

	ADD_LATENT_AUTOMATION_COMMAND(FSpawnLocalPlayerInPIE);
	ADD_LATENT_AUTOMATION_COMMAND(FRetrieveAJetMOCKSetSteerManagerMOCK);
	ADD_LATENT_AUTOMATION_COMMAND(FRetrieveAJetAndPressActionKey(FName(TEXT("SteerLeftAction"))));
	ADD_LATENT_AUTOMATION_COMMAND(FRetrieveAJetAndReleaseActionKey(FName(TEXT("SteerRightAction"))));

	ADD_LATENT_AUTOMATION_COMMAND(FCheckAJetToExpectedSteerState(expectedSteerStateClass, this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FAJetChangesToRightSteerStateWhenReleasingSteerLeftKeyAndSteerRightIsPressedTest::RunTest(const FString& Parameters)
{
	establishInitialMapDirectoryTo(FString("/Game/Tests/TestMaps/VoidWorld-JetMOCKTest"));
	UClass* expectedSteerStateClass = URightSteerState::StaticClass();
	establishTestMessageTo((FString("The Jet steer state should be %s."), *expectedSteerStateClass->GetName()));
	establishTickLimitTo(3);

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(retrieveInitialMapDirectory()));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	
	

	ADD_LATENT_AUTOMATION_COMMAND(FSpawnLocalPlayerInPIE);
	ADD_LATENT_AUTOMATION_COMMAND(FRetrieveAJetMOCKSetSteerManagerMOCK);
	ADD_LATENT_AUTOMATION_COMMAND(FRetrieveAJetAndPressActionKey(FName(TEXT("SteerRightAction"))));
	ADD_LATENT_AUTOMATION_COMMAND(FRetrieveAJetAndReleaseActionKey(FName(TEXT("SteerLeftAction"))));
	
	ADD_LATENT_AUTOMATION_COMMAND(FCheckAJetToExpectedSteerState(expectedSteerStateClass, this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FAJetChangesToCenterSteerStateWhenPressingSteerRightKeyAndSteerLeftIsPressedTest::RunTest(const FString& Parameters)
{
	establishInitialMapDirectoryTo(FString("/Game/Tests/TestMaps/VoidWorld-JetMOCKTest"));
	UClass* expectedSteerStateClass = UCenterSteerState::StaticClass();
	establishTestMessageTo((FString("The Jet steer state should be %s."), *expectedSteerStateClass->GetName()));
	establishTickLimitTo(3);

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(retrieveInitialMapDirectory()));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	
	

	ADD_LATENT_AUTOMATION_COMMAND(FSpawnLocalPlayerInPIE);
	ADD_LATENT_AUTOMATION_COMMAND(FRetrieveAJetMOCKSetSteerManagerMOCK);
	ADD_LATENT_AUTOMATION_COMMAND(FRetrieveAJetAndPressActionKey(FName(TEXT("SteerLeftAction"))));
	ADD_LATENT_AUTOMATION_COMMAND(FRetrieveAJetAndPressActionKey(FName(TEXT("SteerRightAction"))));

	ADD_LATENT_AUTOMATION_COMMAND(FCheckAJetToExpectedSteerState(expectedSteerStateClass, this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FAJetChangesToCenterSteerStateWhenPressingSteerLeftKeyAndSteerRightIsPressedTest::RunTest(const FString& Parameters)
{
	establishInitialMapDirectoryTo(FString("/Game/Tests/TestMaps/VoidWorld-JetMOCKTest"));
	UClass* expectedSteerStateClass = UCenterSteerState::StaticClass();
	establishTestMessageTo((FString("The Jet steer state should be %s."), *expectedSteerStateClass->GetName()));
	establishTickLimitTo(3);

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(retrieveInitialMapDirectory()));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	
	

	ADD_LATENT_AUTOMATION_COMMAND(FSpawnLocalPlayerInPIE);
	ADD_LATENT_AUTOMATION_COMMAND(FRetrieveAJetMOCKSetSteerManagerMOCK);
	ADD_LATENT_AUTOMATION_COMMAND(FRetrieveAJetAndPressActionKey(FName(TEXT("SteerRightAction"))));
	ADD_LATENT_AUTOMATION_COMMAND(FRetrieveAJetAndPressActionKey(FName(TEXT("SteerLeftAction"))));
	
	ADD_LATENT_AUTOMATION_COMMAND(FCheckAJetToExpectedSteerState(expectedSteerStateClass, this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FAJetServerChangesSteerToLeftSteerWhenPressingSteerLeftKeyTest::RunTest(const FString& Parameters)
{
	establishInitialMapDirectoryTo(FString("/Game/Tests/TestMaps/VoidWorld"));
	UClass* expectedSteerStateClass = ULeftSteerState::StaticClass();
	establishTestMessageTo((FString("The server should replicate its state to %s."), *expectedSteerStateClass->GetName()));
	establishTickLimitTo(10);

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(retrieveInitialMapDirectory()));
	int32 numberOfPlayers = 2;
	EPlayNetMode networkMode = EPlayNetMode::PIE_ListenServer;

	ADD_LATENT_AUTOMATION_COMMAND(FStartNetworkedPIESession(numberOfPlayers, networkMode));

	
	

	UClass* jetClass = AJetMOCK::StaticClass();
	ADD_LATENT_AUTOMATION_COMMAND(FServerSpawnPawnOfClass(jetClass, FTransform(), numberOfPlayers));
	ADD_LATENT_AUTOMATION_COMMAND(FServerRetrieveJetMOCKAndSetStateManagerMocks(numberOfPlayers));

	ADD_LATENT_AUTOMATION_COMMAND(FClientPressActionKey(FName(TEXT("SteerLeftAction")), numberOfPlayers));

	ADD_LATENT_AUTOMATION_COMMAND(FServerCheckJetExpectedSteerState(expectedSteerStateClass, numberOfPlayers, this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FAJetServerChangesSteerToCenterSteerWhenReleasingSteerLeftKeyTest::RunTest(const FString& Parameters)
{
	establishInitialMapDirectoryTo(FString("/Game/Tests/TestMaps/VoidWorld"));
	UClass* expectedSteerStateClass = UCenterSteerState::StaticClass();
	establishTestMessageTo((FString("The server should replicate its state to %s."), *expectedSteerStateClass->GetName()));
	establishTickLimitTo(10);

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(retrieveInitialMapDirectory()));
	int32 numberOfPlayers = 2;
	EPlayNetMode networkMode = EPlayNetMode::PIE_ListenServer;

	ADD_LATENT_AUTOMATION_COMMAND(FStartNetworkedPIESession(numberOfPlayers, networkMode));

	
	

	UClass* jetClass = AJetMOCK::StaticClass();
	ADD_LATENT_AUTOMATION_COMMAND(FServerSpawnPawnOfClass(jetClass, FTransform(), numberOfPlayers));
	ADD_LATENT_AUTOMATION_COMMAND(FServerRetrieveJetMOCKAndSetStateManagerMocks(numberOfPlayers));

	ADD_LATENT_AUTOMATION_COMMAND(FClientReleaseActionKey(FName(TEXT("SteerLeftAction")), numberOfPlayers));
	
	ADD_LATENT_AUTOMATION_COMMAND(FServerCheckJetExpectedSteerState(expectedSteerStateClass, numberOfPlayers, this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FAJetServerChangesSteerToCenterSteerWhenReleasingSteerRightKeyTest::RunTest(const FString& Parameters)
{
	establishInitialMapDirectoryTo(FString("/Game/Tests/TestMaps/VoidWorld"));
	UClass* expectedSteerStateClass = UCenterSteerState::StaticClass();
	establishTestMessageTo((FString("The server should replicate its state to %s."), *expectedSteerStateClass->GetName()));
	establishTickLimitTo(10);

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(retrieveInitialMapDirectory()));
	int32 numberOfPlayers = 2;
	EPlayNetMode networkMode = EPlayNetMode::PIE_ListenServer;

	ADD_LATENT_AUTOMATION_COMMAND(FStartNetworkedPIESession(numberOfPlayers, networkMode));

	
	

	UClass* jetClass = AJetMOCK::StaticClass();
	ADD_LATENT_AUTOMATION_COMMAND(FServerSpawnPawnOfClass(jetClass, FTransform(), numberOfPlayers));
	ADD_LATENT_AUTOMATION_COMMAND(FServerRetrieveJetMOCKAndSetStateManagerMocks(numberOfPlayers));

	ADD_LATENT_AUTOMATION_COMMAND(FClientReleaseActionKey(FName(TEXT("SteerRightAction")), numberOfPlayers));

	ADD_LATENT_AUTOMATION_COMMAND(FServerCheckJetExpectedSteerState(expectedSteerStateClass, numberOfPlayers, this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FAJetServerChangesSteerToLeftSteerStateWhenReleasingSteerRightKeyAndSteerLeftIsPressedTest::RunTest(const FString& Parameters)
{
	establishInitialMapDirectoryTo(FString("/Game/Tests/TestMaps/VoidWorld"));
	UClass* expectedSteerStateClass = ULeftSteerState::StaticClass();
	establishTestMessageTo((FString("The server should replicate its state to %s."), *expectedSteerStateClass->GetName()));
	establishTickLimitTo(10);

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(retrieveInitialMapDirectory()));
	int32 numberOfPlayers = 2;
	EPlayNetMode networkMode = EPlayNetMode::PIE_ListenServer;

	ADD_LATENT_AUTOMATION_COMMAND(FStartNetworkedPIESession(numberOfPlayers, networkMode));

	
	

	UClass* jetClass = AJetMOCK::StaticClass();
	ADD_LATENT_AUTOMATION_COMMAND(FServerSpawnPawnOfClass(jetClass, FTransform(), numberOfPlayers));
	ADD_LATENT_AUTOMATION_COMMAND(FServerRetrieveJetMOCKAndSetStateManagerMocks(numberOfPlayers));

	ADD_LATENT_AUTOMATION_COMMAND(FClientPressActionKey(FName(TEXT("SteerLeftAction")), numberOfPlayers));
	ADD_LATENT_AUTOMATION_COMMAND(FClientReleaseActionKey(FName(TEXT("SteerRightAction")), numberOfPlayers));

	ADD_LATENT_AUTOMATION_COMMAND(FServerCheckJetExpectedSteerState(expectedSteerStateClass, numberOfPlayers, this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FAJetServerChangesSteerToRightSteerStateWhenReleasingSteerLeftKeyAndSteerRightIsPressedTest::RunTest(const FString& Parameters)
{
	establishInitialMapDirectoryTo(FString("/Game/Tests/TestMaps/VoidWorld"));
	UClass* expectedSteerStateClass = URightSteerState::StaticClass();
	establishTestMessageTo((FString("The server should replicate its state to %s."), *expectedSteerStateClass->GetName()));
	establishTickLimitTo(10);

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(retrieveInitialMapDirectory()));
	int32 numberOfPlayers = 2;
	EPlayNetMode networkMode = EPlayNetMode::PIE_ListenServer;

	ADD_LATENT_AUTOMATION_COMMAND(FStartNetworkedPIESession(numberOfPlayers, networkMode));

	
	

	UClass* jetClass = AJetMOCK::StaticClass();
	ADD_LATENT_AUTOMATION_COMMAND(FServerSpawnPawnOfClass(jetClass, FTransform(), numberOfPlayers));
	ADD_LATENT_AUTOMATION_COMMAND(FServerRetrieveJetMOCKAndSetStateManagerMocks(numberOfPlayers));

	ADD_LATENT_AUTOMATION_COMMAND(FClientPressActionKey(FName(TEXT("SteerRightAction")), numberOfPlayers));
	ADD_LATENT_AUTOMATION_COMMAND(FClientReleaseActionKey(FName(TEXT("SteerLeftAction")), numberOfPlayers));
	
	ADD_LATENT_AUTOMATION_COMMAND(FServerCheckJetExpectedSteerState(expectedSteerStateClass, numberOfPlayers, this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FAJetServerChangesSteerToCenterSteerStateWhenPressingSteerLeftKeyAndSteerRightIsPressedTest::RunTest(const FString& Parameters)
{
	establishInitialMapDirectoryTo(FString("/Game/Tests/TestMaps/VoidWorld"));
	UClass* expectedSteerStateClass = UCenterSteerState::StaticClass();
	establishTestMessageTo((FString("The server should replicate its state to %s."), *expectedSteerStateClass->GetName()));
	establishTickLimitTo(10);

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(retrieveInitialMapDirectory()));
	int32 numberOfPlayers = 2;
	EPlayNetMode networkMode = EPlayNetMode::PIE_ListenServer;

	ADD_LATENT_AUTOMATION_COMMAND(FStartNetworkedPIESession(numberOfPlayers, networkMode));

	
	

	UClass* jetClass = AJetMOCK::StaticClass();
	ADD_LATENT_AUTOMATION_COMMAND(FServerSpawnPawnOfClass(jetClass, FTransform(), numberOfPlayers));
	ADD_LATENT_AUTOMATION_COMMAND(FServerRetrieveJetMOCKAndSetStateManagerMocks(numberOfPlayers));

	ADD_LATENT_AUTOMATION_COMMAND(FClientPressActionKey(FName(TEXT("SteerRightAction")), numberOfPlayers));
	ADD_LATENT_AUTOMATION_COMMAND(FClientPressActionKey(FName(TEXT("SteerLeftAction")), numberOfPlayers));
	
	ADD_LATENT_AUTOMATION_COMMAND(FServerCheckJetExpectedSteerState(expectedSteerStateClass, numberOfPlayers, this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FAJetServerChangesSteerToCenterSteerStateWhenPressingSteerRightKeyAndSteerLeftIsPressedTest::RunTest(const FString& Parameters)
{
	establishInitialMapDirectoryTo(FString("/Game/Tests/TestMaps/VoidWorld"));
	UClass* expectedSteerStateClass = UCenterSteerState::StaticClass();
	establishTestMessageTo((FString("The server should replicate its state to %s."), *expectedSteerStateClass->GetName()));
	establishTickLimitTo(10);

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(retrieveInitialMapDirectory()));
	int32 numberOfPlayers = 2;
	EPlayNetMode networkMode = EPlayNetMode::PIE_ListenServer;

	ADD_LATENT_AUTOMATION_COMMAND(FStartNetworkedPIESession(numberOfPlayers, networkMode));

	
	

	UClass* jetClass = AJetMOCK::StaticClass();
	ADD_LATENT_AUTOMATION_COMMAND(FServerSpawnPawnOfClass(jetClass, FTransform(), numberOfPlayers));
	ADD_LATENT_AUTOMATION_COMMAND(FServerRetrieveJetMOCKAndSetStateManagerMocks(numberOfPlayers));

	ADD_LATENT_AUTOMATION_COMMAND(FClientPressActionKey(FName(TEXT("SteerLeftAction")), numberOfPlayers));
	ADD_LATENT_AUTOMATION_COMMAND(FClientPressActionKey(FName(TEXT("SteerRightAction")), numberOfPlayers));
	
	ADD_LATENT_AUTOMATION_COMMAND(FServerCheckJetExpectedSteerState(expectedSteerStateClass, numberOfPlayers, this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FAJetHidesItsPhysicsMeshTest::RunTest(const FString& Parameters)
{
	establishInitialMapDirectoryTo(FString("/Game/Tests/TestMaps/VoidWorld-JetMOCKTest"));
	establishTestMessageTo(FString("The Jet should hide its physics mesh."));
	establishTickLimitTo(3);

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(retrieveInitialMapDirectory()));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	
	

	ADD_LATENT_AUTOMATION_COMMAND(FSpawnLocalPlayerInPIE);

	ADD_LATENT_AUTOMATION_COMMAND(FCheckAJetHidesPhysicsMesh(this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FAJetHasAModelMeshTest::RunTest(const FString& Parameters)
{
	establishInitialMapDirectoryTo(FString("/Game/Tests/TestMaps/VoidWorld-JetMOCKTest"));
	establishTestMessageTo(FString("The Jet should have a jet model mesh."));
	establishTickLimitTo(3);

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(retrieveInitialMapDirectory()));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	
	

	ADD_LATENT_AUTOMATION_COMMAND(FSpawnLocalPlayerInPIE);

	ADD_LATENT_AUTOMATION_COMMAND(FCheckAJetHasAModelMesh(this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FAJetModelMeshIsAttachedToPhysicsComponentTest::RunTest(const FString& Parameters)
{
	establishInitialMapDirectoryTo(FString("/Game/Tests/TestMaps/VoidWorld-JetMOCKTest"));
	UClass* expectedSteerStateClass = UCenterSteerState::StaticClass();
	establishTestMessageTo(FString("The Jet model mesh should be attached to the physics component."));
	establishTickLimitTo(3);

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(retrieveInitialMapDirectory()));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	
	

	ADD_LATENT_AUTOMATION_COMMAND(FSpawnLocalPlayerInPIE);

	ADD_LATENT_AUTOMATION_COMMAND(FCheckAJetModelMeshAttachment(this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FAJetStoresItsMovementEachTickTest::RunTest(const FString& Parameters)
{
	establishInitialMapDirectoryTo(FString("/Game/Tests/TestMaps/JetMOCKTestWorld"));
	UClass* expectedSteerStateClass = UCenterSteerState::StaticClass();
	establishTestMessageTo(FString("The Jet should store its current movement each tick."));
	establishTickLimitTo(3);

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(retrieveInitialMapDirectory()));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	ADD_LATENT_AUTOMATION_COMMAND(FCheckAJetHasMovementsStored(this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FAJetMovementHistorySizeIsLimitedTest::RunTest(const FString& Parameters)
{
	establishInitialMapDirectoryTo(FString("/Game/Tests/TestMaps/JetMOCKTestWorld"));
	UClass* expectedSteerStateClass = UCenterSteerState::StaticClass();
	establishTestMessageTo(FString("The Jet should limit the movementHistory size to the one set."));
	establishTickLimitTo(3);

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(retrieveInitialMapDirectory()));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	ADD_LATENT_AUTOMATION_COMMAND(FCheckAJetHasMovementHistorySizeLimited(this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FAJetServerAndClientHaveSameMovesAfterAcceleratingTest::RunTest(const FString& Parameters)
{
	establishInitialMapDirectoryTo(FString("/Game/Tests/TestMaps/VoidWorld-JetMOCKTest"));
	establishTestMessageTo((FString("The server and client should have the same movements states after accelerating.")));
	establishTickLimitTo(10);

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(retrieveInitialMapDirectory()));
	int32 numberOfPlayers = 2;
	EPlayNetMode networkMode = EPlayNetMode::PIE_ListenServer;

	ADD_LATENT_AUTOMATION_COMMAND(FStartNetworkedPIESession(numberOfPlayers, networkMode));
	
	ADD_LATENT_AUTOMATION_COMMAND(FServerAndClientCheckSameMovementsStoredAcceleration(numberOfPlayers, this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FAJetServerAndClientHaveSameMovesAfterBrakingTest::RunTest(const FString& Parameters)
{
	establishInitialMapDirectoryTo(FString("/Game/Tests/TestMaps/VoidWorld-JetMOCKTest"));
	establishTestMessageTo((FString("The server and client should have the same movements states after braking.")));
	establishTickLimitTo(10);

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(retrieveInitialMapDirectory()));
	int32 numberOfPlayers = 2;
	EPlayNetMode networkMode = EPlayNetMode::PIE_ListenServer;

	ADD_LATENT_AUTOMATION_COMMAND(FStartNetworkedPIESession(numberOfPlayers, networkMode));
	
	ADD_LATENT_AUTOMATION_COMMAND(FServerAndClientCheckSameMovementsStoredBraking(numberOfPlayers, this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FAJetServerAndClientHaveSameMovesAfterNeutralizeTest::RunTest(const FString& Parameters)
{
	establishInitialMapDirectoryTo(FString("/Game/Tests/TestMaps/VoidWorld-JetMOCKTest"));
	establishTestMessageTo((FString("The server and client should have the same movements states after neutralize.")));
	establishTickLimitTo(10);

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(retrieveInitialMapDirectory()));
	int32 numberOfPlayers = 2;
	EPlayNetMode networkMode = EPlayNetMode::PIE_ListenServer;

	ADD_LATENT_AUTOMATION_COMMAND(FStartNetworkedPIESession(numberOfPlayers, networkMode));
	
	ADD_LATENT_AUTOMATION_COMMAND(FServerAndClientCheckSameMovementsStoredNeutralize(numberOfPlayers, this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FAJetServerAndClientHaveSameMovesAfterSteerLeftTest::RunTest(const FString& Parameters)
{
	establishInitialMapDirectoryTo(FString("/Game/Tests/TestMaps/VoidWorld-JetMOCKTest"));
	establishTestMessageTo((FString("The server and client should have the same movements states after steering left.")));
	establishTickLimitTo(10);

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(retrieveInitialMapDirectory()));
	int32 numberOfPlayers = 2;
	EPlayNetMode networkMode = EPlayNetMode::PIE_ListenServer;

	ADD_LATENT_AUTOMATION_COMMAND(FStartNetworkedPIESession(numberOfPlayers, networkMode));
	
	ADD_LATENT_AUTOMATION_COMMAND(FServerAndClientCheckSameMovementsStoredSteerLeft(numberOfPlayers, this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FAJetServerAndClientHaveSameMovesAfterSteerRightTest::RunTest(const FString& Parameters)
{
	establishInitialMapDirectoryTo(FString("/Game/Tests/TestMaps/VoidWorld-JetMOCKTest"));
	establishTestMessageTo((FString("The server and client should have the same movements states after steering right.")));
	establishTickLimitTo(10);

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(retrieveInitialMapDirectory()));
	int32 numberOfPlayers = 2;
	EPlayNetMode networkMode = EPlayNetMode::PIE_ListenServer;

	ADD_LATENT_AUTOMATION_COMMAND(FStartNetworkedPIESession(numberOfPlayers, networkMode));
	
	ADD_LATENT_AUTOMATION_COMMAND(FServerAndClientCheckSameMovementsStoredSteerRight(numberOfPlayers, this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FAJetServerAndClientHaveSameMovesAfterCenterSteerTest::RunTest(const FString& Parameters)
{
	establishInitialMapDirectoryTo(FString("/Game/Tests/TestMaps/VoidWorld-JetMOCKTest"));
	establishTestMessageTo((FString("The server and client should have the same movements states after center steering.")));
	establishTickLimitTo(10);

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(retrieveInitialMapDirectory()));
	int32 numberOfPlayers = 2;
	EPlayNetMode networkMode = EPlayNetMode::PIE_ListenServer;

	ADD_LATENT_AUTOMATION_COMMAND(FStartNetworkedPIESession(numberOfPlayers, networkMode));
	
	ADD_LATENT_AUTOMATION_COMMAND(FServerAndClientCheckSameMovementsStoredCenterSteer(numberOfPlayers, this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FAJetSpawnsAdjustingIfPossibleButAlwaysSpawnTest::RunTest(const FString& Parameters)
{
	AJet* testJet = NewObject<AJet>();

	TestTrue(FString("Spawn collision method should be set as adjust if possible but always spawn"), 
		testJet->SpawnCollisionHandlingMethod == ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn);
	
	return true;
}












#endif //WITH_DEV_AUTOMATION_TESTS