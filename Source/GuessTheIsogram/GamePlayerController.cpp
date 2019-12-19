// Fill out your copyright notice in the Description page of Project Settings.


#include "GamePlayerController.h"

// Called when the game starts
void AGamePlayerController::BeginPlay()
{
	Super::BeginPlay(); 

	SetInputMode(FInputModeGameAndUI()); 
}
