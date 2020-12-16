// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

/**
 * This file cointains the latent commands necessary for the tests.
 */

#if WITH_DEV_AUTOMATION_TESTS

#include "Misc/AutomationTest.h"

//Test preparation commands:

DEFINE_LATENT_AUTOMATION_COMMAND(FSpawningAJetMakeItAccelerate);


DEFINE_LATENT_AUTOMATION_COMMAND(FSpawningAJetMakeItBrake);


DEFINE_LATENT_AUTOMATION_COMMAND(FSpawningAJetSetVelocityToTopSpeed);


DEFINE_LATENT_AUTOMATION_COMMAND(FSpawningAJetMakeItSteerRight);


DEFINE_LATENT_AUTOMATION_COMMAND(FSpawningAJetPressAccelerationKey);


DEFINE_LATENT_AUTOMATION_COMMAND(FSpawningAJetPressSteerRightKey);


DEFINE_LATENT_AUTOMATION_COMMAND(FSpawningAJetPressBrakeKey);


DEFINE_LATENT_AUTOMATION_COMMAND(FSpawningAJetSnapedToFloor);


DEFINE_LATENT_AUTOMATION_COMMAND(FSpawningAJetRotateAndAccelerate);


DEFINE_LATENT_AUTOMATION_COMMAND(FSpawningAJetRotateAndBrake);


//DEFINE_LATENT_AUTOMATION_COMMAND(FSpawningAJetAccelerateAndSteerRight);


DEFINE_LATENT_AUTOMATION_COMMAND(FSpawningAJetBrakeAndSteerRight);


DEFINE_LATENT_AUTOMATION_COMMAND(FSpawningAJeSteerRightWhenIdle);


DEFINE_LATENT_AUTOMATION_COMMAND(FSpawningAJet);


DEFINE_LATENT_AUTOMATION_COMMAND(FSpawningTwoJetsMakeOneOfThemItAccelerateAndSteerRight);


DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FSpawningAJetTiltItAndMakeItSteerRight, float, roll);


DEFINE_LATENT_AUTOMATION_COMMAND(FSpawningAJetRotatedOverFloorAndAccelerateIt);


DEFINE_LATENT_AUTOMATION_COMMAND(FSpawningAJetAndFloorSideWays);


DEFINE_LATENT_AUTOMATION_COMMAND(FSpawningAJetRotatedOverFloorAndBrakeIt);


DEFINE_LATENT_AUTOMATION_COMMAND(FSpawningAJetRotatedOverFloorAccelerateAndSteerItRight);






//Test check commands:




DEFINE_LATENT_AUTOMATION_COMMAND_THREE_PARAMETER(FCheckAJetLocation, int, aTickCount, int, aTickLimit, FAutomationTestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_THREE_PARAMETER(FCheckAJetSpeedIncrease, int, aTickCount, int, aTickLimit, FAutomationTestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_THREE_PARAMETER(FCheckAJetVelocityDecrease, int, aTickCount, int, aTickLimit, FAutomationTestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_THREE_PARAMETER(FCheckAJetSpeedAgainstTopSpeed, int, aTickCount, int, aTickLimit, FAutomationTestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_THREE_PARAMETER(FCheckAJetRotatedYaw, int, aTickCount, int, aTickLimit, FAutomationTestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_THREE_PARAMETER(FCheckAJetZLocation, int, aTickCount, int, aTickLimit, FAutomationTestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_THREE_PARAMETER(FCheckAJetLocationCoincidentToForwardVector, int, aTickCount, int, aTickLimit, FAutomationTestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_THREE_PARAMETER(FCheckAJetLocationParallelToForwardVector, int, aTickCount, int, aTickLimit, FAutomationTestBase*, test);


//DEFINE_LATENT_AUTOMATION_COMMAND_FOUR_PARAMETER(FCheckAJetUpdatedVelocityWhenAfterSteering, int, aTickCount, int, aTickLimit, FVector, previousForwardVector, FAutomationTestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_THREE_PARAMETER(FCheckAJetInvertSteeringWhenInReverse, int, aTickCount, int, aTickLimit, FAutomationTestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_FOUR_PARAMETER(FCheckAJetUnableToSteerWhenIdle, int, aTickCount, int, aTickLimit, FRotator, previousRotation, FAutomationTestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FCheckAJetCenterOfMass, FAutomationTestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_THREE_PARAMETER(FCheckAJetFallSpeed, int, aTickCount, int, aTickLimit, FAutomationTestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_FOUR_PARAMETER(FCheckAJetSteersAroundUpVector, int, aTickCount, int, aTickLimit, float, roll, FAutomationTestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_THREE_PARAMETER(FCheckAJetSpeedOrthogonalityToFloor, int, aTickCount, int, aTickLimit, FAutomationTestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_FOUR_PARAMETER(FCheckAJetSidewaysRejectsFloor, int, aTickCount, int, aTickLimit, float, aPreviousDistance, FAutomationTestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_THREE_PARAMETER(FCheckAJetVelocityMagnitudeOrthogonalityToFloor, int, aTickCount, int, aTickLimit, FAutomationTestBase*, test);





#endif //WITH_DEV_AUTOMATION_TESTS