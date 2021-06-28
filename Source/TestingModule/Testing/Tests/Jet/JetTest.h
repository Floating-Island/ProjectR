// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


/**
 * Each one of this tests should test something of the project class that this test class references to.
 * Each project class should have a test class for it. It's something kind of necessary for TDD.
 * 
 * It's nice if the prettyname follows a pattern like: Game.ClassToTest.Unit.TestName
 * TestName should express what you expect from a test given a scenario.
 * Pay attention to the automation flags because they're needed to run the tests without UI errors.
 */

#include "Misc/AutomationTest.h"
#include "../../TestBaseClasses/SimplePIETestBase.h"

#if WITH_DEV_AUTOMATION_TESTS

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAJetIsntNullWhenInstantiatedTest, 
	"ProjectR.Jet Tests.Unit.000: Isn't null when instantiated", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAJetSpeedIsZeroWhenInstantiatedTest, 
	"ProjectR.Jet Tests.Unit.001: Speed is zero when instantiated", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAJetHasAStaticMeshTest, 
	"ProjectR.Jet Tests.Unit.002: Has a static mesh as physics mesh", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAJetMeshIsTheRootComponentTest, 
	"ProjectR.Jet Tests.Unit.003: Mesh is the root component", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAJetHasGravityEnabledTest, 
	"ProjectR.Jet Tests.Unit.004: Has gravity enabled", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAJetDoesntAffectNavigationVolumeTest, 
	"ProjectR.Jet Tests.Unit.005: Doesn't affect navigation volume", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAJetIsMovableTest, 
	"ProjectR.Jet Tests.Unit.006: Is movable", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAJetDefaultAccelerationIsGreaterThanZeroTest, 
	"ProjectR.Jet Tests.Unit.007: Default acceleration is greater than zero", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST(FAJetMovesForwardWhenAcceleratedTest, FSimplePIETestBase,
	"ProjectR.Jet Tests.Unit.008: Moves forward when accelerated", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST(FAJetSpeedIncreasesWhenAcceleratesTest, FSimplePIETestBase,
	"ProjectR.Jet Tests.Unit.009: Speed increases when accelerates", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAJetDefaultBrakeValueIsGreaterThanZeroTest, 
	"ProjectR.Jet Tests.Unit.010: Default brake value is greater than zero", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST(FAJetVelocityNegativeWhenBrakesTest, FSimplePIETestBase, 
	"ProjectR.Jet Tests.Unit.011: Velocity is negative when brakes", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAJetDefaultTopSpeedIsGreaterThanZeroTest, 
	"ProjectR.Jet Tests.Unit.012: Default top speed is greater than zero", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST(FAJetDoesntAccelerateWhenAtTopSpeedTest, FSimplePIETestBase, 
	"ProjectR.Jet Tests.Unit.013: Doesn't accelerate when at top speed", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST(FAJetRotatesYawRightWhenSteeringRightTest, FSimplePIETestBase,
	"ProjectR.Jet Tests.Unit.014: Rotates yaw right when steering right", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAJetDefaultSteerRadiusIsGreaterThanZeroTest, 
	"ProjectR.Jet Tests.Unit.015: Default steer radius is greater than zero", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST(FAJetAcceleratesWhenPressingAccelerationKeyTest, FSimplePIETestBase, 
	"ProjectR.Jet Tests.Unit.016: Accelerates when pressing acceleration key", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST(FAJetMovesRightWhenPressingSteerRightKeyTest, FSimplePIETestBase, 
	"ProjectR.Jet Tests.Unit.017: Moves right when pressing steer right key", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST(FAJetBrakesWhenPressingBrakeKeyTest, FSimplePIETestBase,
	"ProjectR.Jet Tests.Unit.018: Brakes when pressing brake key", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAJetHasASpringArmTest, 
	"ProjectR.Jet Tests.Unit.019: Has a spring arm", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAJetSpringArmIsAttachedToRootComponentTest, 
	"ProjectR.Jet Tests.Unit.020: Spring arm is attached to root component", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAJetHasACameraTest, 
	"ProjectR.Jet Tests.Unit.021: Has a camera", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAJetCameraIsAttachedToSpringArmTest, 
	"ProjectR.Jet Tests.Unit.022: Camera is attached to spring arm", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST(FAJetGetsUpwardsImpulseFromAntiGravityOnFloorTest, FSimplePIETestBase, 
	"ProjectR.Jet Tests.Integration.023: Gets upwards impulse from anti-gravity on floor", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST(FAJetAcceleratesAlongItsForwardVectorWhenAcceleratedAfterRotationTest, FSimplePIETestBase,
	"ProjectR.Jet Tests.Unit.024: Accelerates along its forward vector when accelerated after being rotated", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST(FAJetBrakesAlongItsBackwardsVectorWhileRotatedTest, FSimplePIETestBase,
	"ProjectR.Jet Tests.Unit.025: Brakes along its backwards vector after being rotated", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


//IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST(FAJetUpdatesVelocityDirectionAfterSteeringTest, FSimplePIETestBase,
//	"ProjectR.Jet Tests.Unit.026: Updates velocity direction after steering",
//  EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST(FAJetInvertsSteeringWhenInReverseTest, FSimplePIETestBase, 
	"ProjectR.Jet Tests.Unit.027: Inverts steering when in reverse", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST(FAJetIsntAbleToSteerWhenIdleTest, FSimplePIETestBase, 
	"ProjectR.Jet Tests.Unit.028: Isn't able to steer when idle", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAJetGeneratesOverlapEventsWhenSpawnedTest, 
	"ProjectR.Jet Tests.Unit.029: Generates overlap events when spawned", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


//Necessary so the track generator overlaps with it.
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAJetMeshCollisionIsOfTypePawnTest, 
	"ProjectR.Jet Tests.Unit.030: Jet mesh collision is of type pawn", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAJetHasCenterOfMassLoweredTest, 
	"ProjectR.Jet Tests.Unit.031: Has its center of mass lowered", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST(FAJetFallingSpeedWhenSteeringSameAsNoSteeringTest, FSimplePIETestBase,
	"ProjectR.Jet Tests.Unit.032: Two jets fall at the same speed even if one moves and steers", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


//IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST(FAJetRotatesPitchRightWhenTiltedAndSteersRightTest, FSimplePIETestBase,
//	"ProjectR.Jet Tests.Unit.033: Rotates pitch right when tilted and steers right", 
//	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST(FAJetAcceleratesOrthogonalToSurfaceNormalTest, FSimplePIETestBase,
	"ProjectR.Jet Tests.Integration.034: Accelerates orthogonal to the floor surface up vector", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST(FAJetSidewaysRejectsAFloorSidewaysTest, FSimplePIETestBase,
	"ProjectR.Jet Tests.Integration.035: Activates anti-gravity even if sideways near a sideways floor", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST(FAJetBrakesOrthogonalToSurfaceNormalTest, FSimplePIETestBase,
	"ProjectR.Jet Tests.Integration.036: Brakes orthogonal to the floor surface up vector", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST(FAJetSteersOrthogonalToSurfaceNormalTest, FSimplePIETestBase,
	"ProjectR.Jet Tests.Integration.037: steers orthogonal to the floor surface up vector", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAJetReplicatesTest, 
	"ProjectR.Jet Tests.Replication.038: Replicates to other clients", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAJetDoesntReplicateMovementTest, 
	"ProjectR.Jet Tests.Replication.039: Doesn't replicate movement to other clients", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST(FAJetServerAccelerateReplicatesAccelerationTest, FSimplePIETestBase,
	"ProjectR.Jet Tests.Replication.040: accelerate replicates acceleration to other clients", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST(FAJetServerAcceleratesWhenPressingAccelerationKeyTest, FSimplePIETestBase,
	"ProjectR.Jet Tests.Replication.041: server accelerates when client pressess acceleration key", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST(FAJetServerBrakeReplicatesBrakingTest, FSimplePIETestBase,
	"ProjectR.Jet Tests.Replication.042: brake replicates braking to other clients", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST(FAJetServerBrakesWhenPressingBrakeKeyTest, FSimplePIETestBase,
	"ProjectR.Jet Tests.Replication.043: server brakes when client pressess brake key", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST(FAJetRightSteerReplicatesRightSteeringTest, FSimplePIETestBase,
	"ProjectR.Jet Tests.Replication.044: steerRight replicates right steering to other clients", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST(FAJetServerSteersToRightWhenPressingSteerKeyTest, FSimplePIETestBase,
	"ProjectR.Jet Tests.Replication.045: server steers right when client pressess steerRight key", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST(FAJetNeutralizesMotorManagerWhenReleasingAccelerateKeyTest, FSimplePIETestBase,
	"ProjectR.Jet Tests.Unit.046: Neutralizes when releasing acceleration key", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST(FAJetNeutralizesMotorManagerWhenReleasingBrakeKeyTest, FSimplePIETestBase,
	"ProjectR.Jet Tests.Unit.047: Neutralizes when releasing brake key", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST(FAJetServerNeutralizesWhenReleasingAccelerationKeyTest, FSimplePIETestBase,
	"ProjectR.Jet Tests.Replication.048: server neutralizes motor state when client releases acceleration key", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST(FAJetServerNeutralizesWhenReleasingBrakeKeyTest, FSimplePIETestBase,
	"ProjectR.Jet Tests.Replication.049: server neutralizes motor state when client releases brake key", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST(FAJetMixesItsMotorStateWhenPressingAccelerationAndBrakeKeyTest, FSimplePIETestBase,
	"ProjectR.Jet Tests.Unit.050: Mixes its motor state when pressing acceleration and brake key (in that order)", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST(FAJetMixesItsMotorStateWhenPressingBrakeAndAccelerationKeyTest, FSimplePIETestBase,
	"ProjectR.Jet Tests.Unit.051: Mixes its motor state when pressing brake and acceleration key (in that order)", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST(FAJetServerMixesWhenPressingAccelerationAndBrakeKeyTest, FSimplePIETestBase,
	"ProjectR.Jet Tests.Replication.052: server mixes motor state when client presses accelerate and brake key", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST(FAJetReversesItsMotorStateWhenBrakeKeyIsPressedAndAccelerateReleasedTest, FSimplePIETestBase,
	"ProjectR.Jet Tests.Unit.053: Reverses its motor state when brake key is pressed and accelerate key is released (in that order)", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST(FAJetAcceleratesItsMotorStateWhenAccelerateKeyIsPressedAndBrakeReleasedTest, FSimplePIETestBase,
	"ProjectR.Jet Tests.Unit.054: Accelerates its motor state when accelerate key is pressed and brake key is released (in that order)", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST(FAJetServerReversesWhenBrakeKeyIsPressedAndAccelerateReleasedTest, FSimplePIETestBase,
	"ProjectR.Jet Tests.Replication.055: server reverses motor state when client has pressed brake key and accelerate key is released (in that order)", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST(FAJetServerAcceleratesWhenAccelerateKeyIsPressedAndBrakeReleasedTest, FSimplePIETestBase,
	"ProjectR.Jet Tests.Replication.056: server accelerates motor state when client has pressed accelerate key and brake key is released (in that order)", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST(FAJetRotatesYawLeftWhenSteeringLeftTest, FSimplePIETestBase,
	"ProjectR.Jet Tests.Unit.057: Rotates yaw left when steering left", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST(FAJetChangesToLeftSteerStateWhenPressingSteerLeftKeyTest, FSimplePIETestBase,
	"ProjectR.Jet Tests.Unit.058: Changes its steer state to LeftSteerState when pressing the SteerLeft key", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST(FAJetChangesToCenterSteerStateWhenReleasingSteerLeftKeyTest, FSimplePIETestBase,
	"ProjectR.Jet Tests.Unit.059: Changes its steer state to CenterSteerState when releasing the SteerLeft key", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST(FAJetChangesToCenterSteerStateWhenReleasingSteerRightKeyTest, FSimplePIETestBase,
	"ProjectR.Jet Tests.Unit.060: Changes its steer state to CenterSteerState when releasing the SteerRight key", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST(FAJetChangesToLeftSteerStateWhenReleasingSteerRightKeyAndSteerLeftIsPressedTest, FSimplePIETestBase,
	"ProjectR.Jet Tests.Unit.061: Changes its steer state to LeftSteerState when releasing the SteerRight key and the SteerLeft key is pressed", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST(FAJetChangesToRightSteerStateWhenReleasingSteerLeftKeyAndSteerRightIsPressedTest, FSimplePIETestBase,
	"ProjectR.Jet Tests.Unit.062: Changes its steer state to LeftSteerState when releasing the SteerLeft key and the SteerRight key is pressed", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST(FAJetChangesToCenterSteerStateWhenPressingSteerRightKeyAndSteerLeftIsPressedTest, FSimplePIETestBase,
	"ProjectR.Jet Tests.Unit.063: Changes its steer state to CenterSteerState when pressing the SteerRight key and the SteerLeft key is pressed", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST(FAJetChangesToCenterSteerStateWhenPressingSteerLeftKeyAndSteerRightIsPressedTest, FSimplePIETestBase,
	"ProjectR.Jet Tests.Unit.064: Changes its steer state to CenterSteerState when pressing the SteerLeft key and the SteerRight key is pressed", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST(FAJetServerChangesSteerToLeftSteerWhenPressingSteerLeftKeyTest, FSimplePIETestBase,
	"ProjectR.Jet Tests.Replication.065: Server changes steer state to LeftSteer when client pressess SteerLeft key", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST(FAJetServerChangesSteerToCenterSteerWhenReleasingSteerLeftKeyTest, FSimplePIETestBase,
	"ProjectR.Jet Tests.Replication.065: Server changes steer state to CenterSteer when client releases SteerLeft key", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST(FAJetServerChangesSteerToCenterSteerWhenReleasingSteerRightKeyTest, FSimplePIETestBase,
	"ProjectR.Jet Tests.Replication.066: Server changes steer state to CenterSteer when client releases SteerRight key", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST(FAJetServerChangesSteerToLeftSteerStateWhenReleasingSteerRightKeyAndSteerLeftIsPressedTest, FSimplePIETestBase,
	"ProjectR.Jet Tests.Replication.067: Server changes steer state to LeftSteer when client releases SteerRight key while the steer left is pressed", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST(FAJetServerChangesSteerToRightSteerStateWhenReleasingSteerLeftKeyAndSteerRightIsPressedTest, FSimplePIETestBase,
	"ProjectR.Jet Tests.Replication.068: Server changes steer state to RightSteer when client releases SteerLeft key while the steerRight is pressed", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST(FAJetServerChangesSteerToCenterSteerStateWhenPressingSteerLeftKeyAndSteerRightIsPressedTest, FSimplePIETestBase,
	"ProjectR.Jet Tests.Replication.069: Server changes steer state to CenterSteer when client pressess SteerLeft key while the steerRight is pressed", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST(FAJetServerChangesSteerToCenterSteerStateWhenPressingSteerRightKeyAndSteerLeftIsPressedTest, FSimplePIETestBase,
	"ProjectR.Jet Tests.Replication.069: Server changes steer state to CenterSteer when client pressess SteerRight key while the steerLeft is pressed", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST(FAJetHidesItsPhysicsMeshTest, FSimplePIETestBase,
	"ProjectR.Jet Tests.Unit.070: Hides its physics mesh model", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST(FAJetHasAModelMeshTest, FSimplePIETestBase,
	"ProjectR.Jet Tests.Unit.071: Has a jet model mesh", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST(FAJetModelMeshIsAttachedToPhysicsComponentTest, FSimplePIETestBase,
	"ProjectR.Jet Tests.Unit.072: Jet model mesh is attached to physics component", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST(FAJetStoresItsMovementEachTickTest, FSimplePIETestBase,
	"ProjectR.Jet Tests.Unit.073: Stores its current movement each tick", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST(FAJetMovementHistorySizeIsLimitedTest, FSimplePIETestBase,
	"ProjectR.Jet Tests.Unit.074: movementHistory size is limited to the one set", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST(FAJetServerAndClientHaveSameMovesAfterAcceleratingTest, FSimplePIETestBase,
	"ProjectR.Jet Tests.Replication.075: Server and client have the same movements after accelerating", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST(FAJetServerAndClientHaveSameMovesAfterBrakingTest, FSimplePIETestBase,
	"ProjectR.Jet Tests.Replication.076: Server and client have the same movements after braking", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST(FAJetServerAndClientHaveSameMovesAfterNeutralizeTest, FSimplePIETestBase,
	"ProjectR.Jet Tests.Replication.077: Server and client have the same movements after neutralize", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST(FAJetServerAndClientHaveSameMovesAfterSteerLeftTest, FSimplePIETestBase,
	"ProjectR.Jet Tests.Replication.078: Server and client have the same movements after steering left", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST(FAJetServerAndClientHaveSameMovesAfterSteerRightTest, FSimplePIETestBase,
	"ProjectR.Jet Tests.Replication.079: Server and client have the same movements after steering right", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST(FAJetServerAndClientHaveSameMovesAfterCenterSteerTest, FSimplePIETestBase,
	"ProjectR.Jet Tests.Replication.080: Server and client have the same movements after center steering", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAJetSpawnsAdjustingIfPossibleButAlwaysSpawnTest,
	"ProjectR.Jet Tests.Unit.081: Collision handling method is set as adjust if possible but always spawn", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAJetIsAlwaysRelevantTest,
	"ProjectR.Jet Tests.Replication.082: Is always relevant for network", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


//jet mesh should be set to collision enabled. (query and physics or physics only).
//delete tests that check velocity alignment to forward or backwards vectors after steering. Or see if it's possible to remade them.
//create a state with state factory to handle the direction that the jet is heading (forwards or backwards). It should update itself every time that acceleration or brake is called.
// maybe move the inReverseInverts method located in the steer component to the state factory.





#endif //WITH_DEV_AUTOMATION_TESTS