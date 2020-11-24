// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

/**
 * This file cointains the latent commands necessary for the tests.
 */

#if WITH_DEV_AUTOMATION_TESTS

#include "Misc/AutomationTest.h"

//Test preparation commands:

DEFINE_LATENT_AUTOMATION_COMMAND(FSpawningAJetMakeItAccelerateCommand);


DEFINE_LATENT_AUTOMATION_COMMAND(FSpawningAJetMakeItBrakeCommand);


DEFINE_LATENT_AUTOMATION_COMMAND(FSpawningAJetSetVelocityToTopSpeedCommand);


DEFINE_LATENT_AUTOMATION_COMMAND(FSpawningAJetMakeItSteerRightCommand);


DEFINE_LATENT_AUTOMATION_COMMAND(FSpawningAJetPressAccelerationKeyCommand);


DEFINE_LATENT_AUTOMATION_COMMAND(FSpawningAJetPressSteerRightKeyCommand);


DEFINE_LATENT_AUTOMATION_COMMAND(FSpawningAJetPressBrakeKeyCommand);


DEFINE_LATENT_AUTOMATION_COMMAND(FSpawningAJetSnapedToFloorCommand);


DEFINE_LATENT_AUTOMATION_COMMAND(FSpawningAJetRotateAndAccelerateCommand);


DEFINE_LATENT_AUTOMATION_COMMAND(FSpawningAJetRotateAndBrakeCommand);


//DEFINE_LATENT_AUTOMATION_COMMAND(FSpawningAJetAccelerateAndSteerRightCommand);


DEFINE_LATENT_AUTOMATION_COMMAND(FSpawningAJetBrakeAndSteerRightCommand);


DEFINE_LATENT_AUTOMATION_COMMAND(FSpawningAJeSteerRightWhenIdleCommand);


DEFINE_LATENT_AUTOMATION_COMMAND(FSpawningAJetCommand);


DEFINE_LATENT_AUTOMATION_COMMAND(FSpawningTwoJetsMakeOneOfThemItAccelerateAndSteerRightCommand);


DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FSpawningAJetTiltItAndMakeItSteerRightCommand, float, roll);


DEFINE_LATENT_AUTOMATION_COMMAND(FSpawningAJetRotatedOverFloorAndAccelerateItCommand);


DEFINE_LATENT_AUTOMATION_COMMAND(FSpawningAJetAndFloorSideWaysCommand);


DEFINE_LATENT_AUTOMATION_COMMAND(FSpawningAJetRotatedOverFloorAndBrakeItCommand);


DEFINE_LATENT_AUTOMATION_COMMAND(FSpawningAJetRotatedOverFloorAccelerateAndSteerItRightCommand);






//Test check commands:




DEFINE_LATENT_AUTOMATION_COMMAND_THREE_PARAMETER(FCheckAJetLocationCommand, int, aTickCount, int, aTickLimit, FAutomationTestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_THREE_PARAMETER(FCheckAJetSpeedIncreaseCommand, int, aTickCount, int, aTickLimit, FAutomationTestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_THREE_PARAMETER(FCheckAJetVelocityDecreaseCommand, int, aTickCount, int, aTickLimit, FAutomationTestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_THREE_PARAMETER(FCheckAJetSpeedAgainstTopSpeedCommand, int, aTickCount, int, aTickLimit, FAutomationTestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_THREE_PARAMETER(FCheckAJetRotatedYawCommand, int, aTickCount, int, aTickLimit, FAutomationTestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_THREE_PARAMETER(FCheckAJetZLocationCommand, int, aTickCount, int, aTickLimit, FAutomationTestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_THREE_PARAMETER(FCheckAJetLocationCoincidentToForwardVectorCommand, int, aTickCount, int, aTickLimit, FAutomationTestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_THREE_PARAMETER(FCheckAJetLocationParallelToForwardVectorCommand, int, aTickCount, int, aTickLimit, FAutomationTestBase*, test);


//DEFINE_LATENT_AUTOMATION_COMMAND_FOUR_PARAMETER(FCheckAJetUpdatedVelocityWhenAfterSteeringCommand, int, aTickCount, int, aTickLimit, FVector, previousForwardVector, FAutomationTestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_THREE_PARAMETER(FCheckAJetInvertSteeringWhenInReverseCommand, int, aTickCount, int, aTickLimit, FAutomationTestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_FOUR_PARAMETER(FCheckAJetUnableToSteerWhenIdleCommand, int, aTickCount, int, aTickLimit, FRotator, previousRotation, FAutomationTestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FCheckAJetCenterOfMassCommand, FAutomationTestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_THREE_PARAMETER(FCheckAJetFallSpeedCommand, int, aTickCount, int, aTickLimit, FAutomationTestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_FOUR_PARAMETER(FCheckAJetSteersAroundUpVectorCommand, int, aTickCount, int, aTickLimit, float, roll, FAutomationTestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_THREE_PARAMETER(FCheckAJetSpeedOrthogonalityToFloorCommand, int, aTickCount, int, aTickLimit, FAutomationTestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_FOUR_PARAMETER(FCheckAJetSidewaysRejectsFloorCommand, int, aTickCount, int, aTickLimit, float, aPreviousDistance, FAutomationTestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_THREE_PARAMETER(FCheckAJetVelocityMagnitudeOrthogonalityToFloorCommand, int, aTickCount, int, aTickLimit, FAutomationTestBase*, test);





#endif //WITH_DEV_AUTOMATION_TESTS