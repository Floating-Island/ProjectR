// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

/**
 * This file contains the latent commands necessary for the tests.
 */

#if WITH_DEV_AUTOMATION_TESTS

#include "Misc/AutomationTest.h"
#include "../../TestBaseClasses/SimplePIETestBase.h"

//Test preparation commands:

DEFINE_LATENT_AUTOMATION_COMMAND(FRetrieveAJetMakeItAccelerate);


DEFINE_LATENT_AUTOMATION_COMMAND(FRetrieveAJetMakeItBrake);


DEFINE_LATENT_AUTOMATION_COMMAND(FRetrieveAJetMOCKSetVelocityToTopSpeed);


DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FRetrieveAJetMOCKSetVelocityToDesiredSpeed, float, desiredSpeed);


DEFINE_LATENT_AUTOMATION_COMMAND(FRetrieveAJetMakeItSteerRight);


DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FRetrieveAJetAndPressActionKey, FName, keyName);


DEFINE_LATENT_AUTOMATION_COMMAND(FSpawningAJetSnapedToFloor);


DEFINE_LATENT_AUTOMATION_COMMAND(FRetrieveAJetAndRotateIt);


//DEFINE_LATENT_AUTOMATION_COMMAND(FSpawningAJetAccelerateAndSteerRight);


DEFINE_LATENT_AUTOMATION_COMMAND(FSpawningTwoJetsMakeOneOfThemItAccelerateAndSteerRight);


DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FSpawningAJetTiltItAndMakeItSteerRight, float, roll);


DEFINE_LATENT_AUTOMATION_COMMAND(FSpawningAJetRotatedOverFloorAndAccelerateIt);


DEFINE_LATENT_AUTOMATION_COMMAND(FSpawningAJetAndFloorSideWays);


DEFINE_LATENT_AUTOMATION_COMMAND(FSpawningAJetRotatedOverFloorAndBrakeIt);


DEFINE_LATENT_AUTOMATION_COMMAND(FSpawningAJetRotatedOverFloorAccelerateAndSteerItRight);


DEFINE_LATENT_AUTOMATION_COMMAND_TWO_PARAMETER(FClientPressKey, FName, keyName, int, clientQuantity);


DEFINE_LATENT_AUTOMATION_COMMAND_TWO_PARAMETER(FClientPressActionKey, FName, keyName, int, clientQuantity);


DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FServerRetrieveJetMOCKAndSetTopSpeed, int, clientQuantity);


DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FClientSteerRightJet, int, clientQuantity);


DEFINE_LATENT_AUTOMATION_COMMAND(FRetrieveAJetMOCKSetMotorManagerMOCKAndSetAcceleratingMotorState);


DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FRetrieveAJetAndReleaseActionKey, FName, keyName);


DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FServerRetrieveJetMOCKAndSetStateManagerMocks, int, clientQuantity);


DEFINE_LATENT_AUTOMATION_COMMAND_TWO_PARAMETER(FClientReleaseActionKey, FName, keyName, int, clientQuantity);


DEFINE_LATENT_AUTOMATION_COMMAND(FRetrieveAJetMOCKSetMotorManagerMOCK);


DEFINE_LATENT_AUTOMATION_COMMAND(FRetrieveAJetMOCKSetSteerManagerMOCK);


DEFINE_LATENT_AUTOMATION_COMMAND(FRetrieveAJetMakeItSteerLeft);






//Test check commands:




DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FCheckAJetLocation, FSimplePIETestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FCheckAJetSpeedIncrease, FSimplePIETestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FCheckAJetVelocityDecrease, FSimplePIETestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FCheckAJetSpeedAgainstTopSpeed, FSimplePIETestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FCheckAJetRotatedYawRight, FSimplePIETestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FCheckAJetZLocation, FSimplePIETestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FCheckAJetLocationCoincidentToForwardVector, FSimplePIETestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FCheckAJetLocationParallelToForwardVector, FSimplePIETestBase*, test);


//DEFINE_LATENT_AUTOMATION_COMMAND_TWO_PARAMETER(FCheckAJetUpdatedVelocityWhenAfterSteering, FVector, previousForwardVector, FSimplePIETestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FCheckAJetInvertSteeringWhenInReverse, FSimplePIETestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_TWO_PARAMETER(FCheckAJetUnableToSteerWhenIdle, FRotator, previousRotation, FSimplePIETestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FCheckAJetCenterOfMass, FAutomationTestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FCheckAJetFallSpeed, FSimplePIETestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_TWO_PARAMETER(FCheckAJetSteersAroundUpVector, float, roll, FSimplePIETestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FCheckAJetSpeedOrthogonalityToFloor, FSimplePIETestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_TWO_PARAMETER(FCheckAJetSidewaysRejectsFloor, float, aPreviousDistance, FSimplePIETestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FCheckAJetVelocityMagnitudeOrthogonalityToFloor, FSimplePIETestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_THREE_PARAMETER(FServerCheckJetAccelerated, int, clientQuantity, FVector, previousLocation, FSimplePIETestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_THREE_PARAMETER(FServerCheckJetBrake, int, clientQuantity, FVector, previousLocation, FSimplePIETestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_THREE_PARAMETER(FServerCheckJetSteer, int, clientQuantity, FVector, previousLocation, FSimplePIETestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_TWO_PARAMETER(FCheckAJetToExpectedMotorState, UClass*, expectedStateClass, FSimplePIETestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_THREE_PARAMETER(FServerCheckJetExpectedMotorState, UClass*, expectedStateClass, int, clientQuantity, FSimplePIETestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FCheckAJetRotatedYawLeft, FSimplePIETestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_TWO_PARAMETER(FCheckAJetToExpectedSteerState, UClass*, expectedStateClass, FSimplePIETestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_THREE_PARAMETER(FServerCheckJetExpectedSteerState, UClass*, expectedStateClass, int, clientQuantity, FSimplePIETestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FCheckAJetHidesPhysicsMesh, FSimplePIETestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FCheckAJetHasAModelMesh, FSimplePIETestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FCheckAJetModelMeshAttachment, FSimplePIETestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FCheckAJetHasMovementsStored, FSimplePIETestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FCheckAJetHasMovementHistorySizeLimited, FSimplePIETestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_TWO_PARAMETER(FServerAndClientCheckSameMovementsStoredAcceleration, int, clientQuantity, FSimplePIETestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_TWO_PARAMETER(FServerAndClientCheckSameMovementsStoredBraking, int, clientQuantity, FSimplePIETestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_TWO_PARAMETER(FServerAndClientCheckSameMovementsStoredNeutralize, int, clientQuantity, FSimplePIETestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_TWO_PARAMETER(FServerAndClientCheckSameMovementsStoredSteerLeft, int, clientQuantity, FSimplePIETestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_TWO_PARAMETER(FServerAndClientCheckSameMovementsStoredSteerRight, int, clientQuantity, FSimplePIETestBase*, test);

#endif //WITH_DEV_AUTOMATION_TESTS