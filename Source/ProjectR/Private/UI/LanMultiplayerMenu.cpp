// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/LanMultiplayerMenu.h"

bool ULanMultiplayerMenu::Initialize()
{
	bool initializeResult = Super::Initialize();
	bIsFocusable = true;
	return initializeResult;
}
