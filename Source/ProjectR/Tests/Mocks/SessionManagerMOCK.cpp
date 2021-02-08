// Fill out your copyright notice in the Description page of Project Settings.


#include "SessionManagerMOCK.h"

IOnlineSubsystem* USessionManagerMOCK::retrieveSessionSubsystem()
{
	return onlineSubsystem;
}

IOnlineSessionPtr USessionManagerMOCK::retrieveSessionInterface()
{
	return sessionInterface;
}
