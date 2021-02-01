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


DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FServerSpawnJet, int, clientQuantity);


DEFINE_LATENT_AUTOMATION_COMMAND_TWO_PARAMETER(FClientPressKey, FName, keyName, int, clientQuantity);


DEFINE_LATENT_AUTOMATION_COMMAND_TWO_PARAMETER(FClientPressActionKey, FName, keyName, int, clientQuantity);


DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FServerSpawnJetToSteer, int, clientQuantity);


DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FClientSteerRightJet, int, clientQuantity);


DEFINE_LATENT_AUTOMATION_COMMAND(FSpawningAJetReleaseAccelerationKey);


DEFINE_LATENT_AUTOMATION_COMMAND(FSpawningAJetReleaseBrakeKey);


DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FServerSpawnJetMOCK, int, clientQuantity);


DEFINE_LATENT_AUTOMATION_COMMAND_TWO_PARAMETER(FClientReleaseActionKey, FName, keyName, int, clientQuantity);


DEFINE_LATENT_AUTOMATION_COMMAND(FSpawningAJetPressAccelerationAndBrakeKey);


DEFINE_LATENT_AUTOMATION_COMMAND(FSpawningAJetPressBrakeAndAccelerationKey);


DEFINE_LATENT_AUTOMATION_COMMAND(FSpawningAJetPressBrakeAndReleaseAccelerationKey);


DEFINE_LATENT_AUTOMATION_COMMAND(FSpawningAJetPressAccelerateAndReleaseBrakeKey);


DEFINE_LATENT_AUTOMATION_COMMAND(FSpawningAJetMakeItSteerLeft);


DEFINE_LATENT_AUTOMATION_COMMAND(FSpawningAJetPressSteerLeftKey);






//Test check commands:




DEFINE_LATENT_AUTOMATION_COMMAND_THREE_PARAMETER(FCheckAJetLocation, int, tickCount, int, tickLimit, FAutomationTestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_THREE_PARAMETER(FCheckAJetSpeedIncrease, int, tickCount, int, tickLimit, FAutomationTestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_THREE_PARAMETER(FCheckAJetVelocityDecrease, int, tickCount, int, tickLimit, FAutomationTestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_THREE_PARAMETER(FCheckAJetSpeedAgainstTopSpeed, int, tickCount, int, tickLimit, FAutomationTestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_THREE_PARAMETER(FCheckAJetRotatedYawRight, int, tickCount, int, tickLimit, FAutomationTestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_THREE_PARAMETER(FCheckAJetZLocation, int, tickCount, int, tickLimit, FAutomationTestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_THREE_PARAMETER(FCheckAJetLocationCoincidentToForwardVector, int, tickCount, int, tickLimit, FAutomationTestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_THREE_PARAMETER(FCheckAJetLocationParallelToForwardVector, int, tickCount, int, tickLimit, FAutomationTestBase*, test);


//DEFINE_LATENT_AUTOMATION_COMMAND_FOUR_PARAMETER(FCheckAJetUpdatedVelocityWhenAfterSteering, int, tickCount, int, tickLimit, FVector, previousForwardVector, FAutomationTestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_THREE_PARAMETER(FCheckAJetInvertSteeringWhenInReverse, int, tickCount, int, tickLimit, FAutomationTestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_FOUR_PARAMETER(FCheckAJetUnableToSteerWhenIdle, int, tickCount, int, tickLimit, FRotator, previousRotation, FAutomationTestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FCheckAJetCenterOfMass, FAutomationTestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_THREE_PARAMETER(FCheckAJetFallSpeed, int, tickCount, int, tickLimit, FAutomationTestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_FOUR_PARAMETER(FCheckAJetSteersAroundUpVector, int, tickCount, int, tickLimit, float, roll, FAutomationTestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_THREE_PARAMETER(FCheckAJetSpeedOrthogonalityToFloor, int, tickCount, int, tickLimit, FAutomationTestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_FOUR_PARAMETER(FCheckAJetSidewaysRejectsFloor, int, tickCount, int, tickLimit, float, aPreviousDistance, FAutomationTestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_THREE_PARAMETER(FCheckAJetVelocityMagnitudeOrthogonalityToFloor, int, tickCount, int, tickLimit, FAutomationTestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_FIVE_PARAMETER(FServerCheckJetAccelerated, int, tickCount, int, tickLimit, int, clientQuantity, FVector, previousLocation, FAutomationTestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_FIVE_PARAMETER(FServerCheckJetBrake, int, tickCount, int, tickLimit, int, clientQuantity, FVector, previousLocation, FAutomationTestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_FIVE_PARAMETER(FServerCheckJetSteer, int, tickCount, int, tickLimit, int, clientQuantity, FVector, previousLocation, FAutomationTestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_FOUR_PARAMETER(FCheckAJetToExpectedMotorState, UClass*, expectedStateClass, int, tickCount, int, tickLimit, FAutomationTestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_FIVE_PARAMETER(FServerCheckJetExpectedMotorState, UClass*, expectedStateClass, int, tickCount, int, tickLimit, int, clientQuantity, FAutomationTestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_THREE_PARAMETER(FCheckAJetRotatedYawLeft, int, tickCount, int, tickLimit, FAutomationTestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_FOUR_PARAMETER(FCheckAJetToExpectedSteerState, UClass*, expectedStateClass, int, tickCount, int, tickLimit, FAutomationTestBase*, test);


#endif //WITH_DEV_AUTOMATION_TESTS