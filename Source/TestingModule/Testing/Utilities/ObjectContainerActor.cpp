// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectContainerActor.h"

// Sets default values
AObjectContainerActor::AObjectContainerActor()
{
	PrimaryActorTick.bCanEverTick = false;
	storedObject = nullptr;
}

UObject* AObjectContainerActor::retrieveStoredObject()
{
	return storedObject;
}
