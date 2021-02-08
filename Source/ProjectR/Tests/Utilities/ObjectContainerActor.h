// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ObjectContainerActor.generated.h"

UCLASS()
class PROJECTR_API AObjectContainerActor : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY()
		UObject* storedObject;
	
public:	
	// Sets default values for this actor's properties
	AObjectContainerActor();

	template <class aDerivedUObjectClass>
	void storeObjectOfType();

	UObject* retrieveStoredObject();
};

template <class aDerivedUObjectClass>
void AObjectContainerActor::storeObjectOfType()
{
	storedObject = NewObject<aDerivedUObjectClass>(this, aDerivedUObjectClass::StaticClass()->GetFName());
}
