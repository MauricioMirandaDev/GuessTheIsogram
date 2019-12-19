// Fill out your copyright notice in the Description page of Project Settings.


#include "GuessTheIsogramGameModeBase.h"

// Called when the game starts
void AGuessTheIsogramGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	ChangeMenuWidget(StartingWidgetClass); 
}

// Remove the current widget and create a new one
void AGuessTheIsogramGameModeBase::ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass)
{
	// If there is a widget being used, remove it
	if (CurrentWidget != nullptr)
	{
		CurrentWidget->RemoveFromViewport(); 

		CurrentWidget = nullptr; 
	}

	// If there is a new widget for us to us, add it to the viewport
	if (NewWidgetClass != nullptr)
	{
		CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), NewWidgetClass); 

		if (CurrentWidget != nullptr)
			CurrentWidget->AddToViewport(); 
	}
}