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

#if WITH_DEV_AUTOMATION_TESTS

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAJetIsntNullWhenInstantiatedTest, 
	"ProjectR.Jet Tests.Unit.000: Isn't null when instantiated", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAJetSpeedIsZeroWhenInstantiatedTest, 
	"ProjectR.Jet Tests.Unit.001: Speed is zero when instantiated", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


//uses a MOCK
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAJetHasAStaticMeshTest, 
	"ProjectR.Jet Tests.Unit.002: Has a static mesh as physics mesh", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


//uses a MOCK
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAJetMeshIsTheRootComponentTest, 
	"ProjectR.Jet Tests.Unit.003: Mesh is the root component", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


//uses a MOCK
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAJetHasGravityEnabledTest, 
	"ProjectR.Jet Tests.Unit.004: Has gravity enabled", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


//uses a MOCK
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAJetDoesntAffectNavigationVolumeTest, 
	"ProjectR.Jet Tests.Unit.005: Doesn't affect navigation volume", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


//uses a MOCK
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAJetIsMovableTest, 
	"ProjectR.Jet Tests.Unit.006: Is movable", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAJetDefaultAccelerationIsGreaterThanZeroTest, 
	"ProjectR.Jet Tests.Unit.007: Default acceleration is greater than zero", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAJetMovesForwardWhenAcceleratedTest, 
	"ProjectR.Jet Tests.Unit.008: Moves forward when accelerated", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAJetSpeedIncreasesWhenAcceleratesTest, 
	"ProjectR.Jet Tests.Unit.009: Speed increases when accelerates", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAJetDefaultBrakeValueIsGreaterThanZeroTest, 
	"ProjectR.Jet Tests.Unit.010: Default brake value is greater than zero", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAJetVelocityNegativeWhenBrakesTest, 
	"ProjectR.Jet Tests.Unit.011: Velocity is negative when brakes", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAJetDefaultTopSpeedIsGreaterThanZeroTest, 
	"ProjectR.Jet Tests.Unit.012: Default top speed is greater than zero", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


//uses a MOCK
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAJetDoesntAccelerateWhenAtTopSpeedTest, 
	"ProjectR.Jet Tests.Unit.013: Doesn't accelerate when at top speed", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAJetRotatesYawRightWhenSteeringRightTest, 
	"ProjectR.Jet Tests.Unit.014: Rotates yaw right when steering right", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAJetDefaultSteerRadiusIsGreaterThanZeroTest, 
	"ProjectR.Jet Tests.Unit.015: Default steer radius is greater than zero", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAJetAcceleratesWhenPressingAccelerationKeyTest, 
	"ProjectR.Jet Tests.Unit.016: Accelerates when pressing acceleration key", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAJetMovesRightWhenPressingSteerRightKeyTest, 
	"ProjectR.Jet Tests.Unit.017: Moves right when pressing steer right key", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAJetBrakesWhenPressingBrakeKeyTest, 
	"ProjectR.Jet Tests.Unit.018: Brakes when pressing brake key", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


//uses a MOCK
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAJetHasASpringArmTest, 
	"ProjectR.Jet Tests.Unit.019: Has a spring arm", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


//uses a MOCK
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAJetSpringArmIsAttachedToRootComponentTest, 
	"ProjectR.Jet Tests.Unit.020: Spring arm is attached to root component", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


//uses a MOCK
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAJetHasACameraTest, 
	"ProjectR.Jet Tests.Unit.021: Has a camera", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


//uses a MOCK
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAJetCameraIsAttachedToSpringArmTest, 
	"ProjectR.Jet Tests.Unit.022: Camera is attached to spring arm", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


//uses a mock
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAJetGetsUpwardsImpulseFromAntiGravityOnFloorTest, 
	"ProjectR.Jet Tests.Integration.023: Gets upwards impulse from anti-gravity on floor", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAJetAcceleratesAlongItsForwardVectorWhenAcceleratedAfterRotationTest, 
	"ProjectR.Jet Tests.Unit.024: Accelerates along its forward vector when accelerated after being rotated", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAJetBrakesAlongItsBackwardsVectorWhileRotatedTest, 
	"ProjectR.Jet Tests.Unit.025: Brakes along its backwards vector after being rotated", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


//IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAJetUpdatesVelocityDirectionAfterSteeringTest,
//	"ProjectR.Jet Tests.Unit.026: Updates velocity direction after steering",
//  EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAJetInvertsSteeringWhenInReverseTest, 
	"ProjectR.Jet Tests.Unit.027: Inverts steering when in reverse", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAJetIsntAbleToSteerWhenIdleTest, 
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


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAJetFallingSpeedWhenSteeringSameAsNoSteeringTest, 
	"ProjectR.Jet Tests.Unit.032: Two jets fall at the same speed even if one moves and steers", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAJetRotatesPitchRightWhenTiltedAndSteersRightTest, 
	"ProjectR.Jet Tests.Unit.033: Rotates pitch right when tilted and steers right", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


//uses a mock
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAJetAcceleratesOrthogonalToSurfaceNormalTest, 
	"ProjectR.Jet Tests.Integration.034: Accelerates orthogonal to the floor surface up vector", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAJetSidewaysRejectsAFloorSidewaysTest, 
	"ProjectR.Jet Tests.Integration.035: Activates anti-gravity even if sideways near a sideways floor", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


//uses a mock
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAJetBrakesOrthogonalToSurfaceNormalTest, 
	"ProjectR.Jet Tests.Integration.036: Brakes orthogonal to the floor surface up vector", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


//uses a mock
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAJetSteersOrthogonalToSurfaceNormalTest, 
	"ProjectR.Jet Tests.Integration.037: steers orthogonal to the floor surface up vector", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAJetReplicatesTest, 
	"ProjectR.Jet Tests.Replication.038: Replicates to other clients", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAJetReplicatesMovementTest, 
	"ProjectR.Jet Tests.Replication.039: Replicates movement to other clients", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAJetServerAccelerateReplicatesAccelerationTest, 
	"ProjectR.Jet Tests.Replication.040: serverAccelerate replicates acceleration to other clients", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAJetServerAcceleratesWhenPressingAccelerationKeyTest, 
	"ProjectR.Jet Tests.Replication.041: server accelerates when client pressess acceleration key", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAJetServerBrakeReplicatesBrakingTest, 
	"ProjectR.Jet Tests.Replication.042: serverBrake replicates braking to other clients", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAJetServerBrakseWhenPressingBrakeKeyTest, 
	"ProjectR.Jet Tests.Replication.043: server brakes when client pressess brake key", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAJetServerSteerReplicatesSteeringTest, 
	"ProjectR.Jet Tests.Replication.044: serverSteer replicates steering to other clients", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAJetServerSteersWhenPressingSteerKeyTest, 
	"ProjectR.Jet Tests.Replication.044: server steers when client pressess steer key", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


//jet mesh should be set to collision enabled. (query and physics or physics only).
//delete tests that check velocity alignment to forward or backwards vectors after steering. Or see if it's possible to remade them.
//create a state with state factory to handle the direction that the jet is heading (forwards or backwards). It should update itself every time that acceleration or brake is called.
// maybe move the inReverseInverts method located in the steer component to the state factory.





#endif //WITH_DEV_AUTOMATION_TESTS