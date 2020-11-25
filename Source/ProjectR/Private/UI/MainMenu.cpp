// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MainMenu.h"

void UMainMenu::quit()
{
	GetWorld()->GetFirstPlayerController()->ConsoleCommand("quit");
}
