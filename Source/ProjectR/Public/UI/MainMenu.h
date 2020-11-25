// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenu.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTR_API UMainMenu : public UUserWidget
{
	GENERATED_BODY()

public:
	void quit();
	
};
