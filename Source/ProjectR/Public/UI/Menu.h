// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Menu.generated.h"

class UButton;
/**
 * 
 */
UCLASS()
class PROJECTR_API UMenu : public UUserWidget
{
	GENERATED_BODY()

protected:
  FVector2D buttonAbsoluteCenterPosition(UButton* aButton);
};
