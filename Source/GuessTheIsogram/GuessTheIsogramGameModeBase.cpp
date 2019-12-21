// Fill out your copyright notice in the Description page of Project Settings.

#include "GuessTheIsogramGameModeBase.h"

// Called when the game starts
void AGuessTheIsogramGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	ChangeMenuWidget(StartingWidgetClass); 

	InitializeGame(); 

	bIsIsogram(EnteredWord); 
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

// Set up game variables
FGameVariables AGuessTheIsogramGameModeBase::InitializeGame()
{
	FGameVariables GameVariables; 

	GameVariables.MysteryWord = WordList[FMath::RandRange(0, WordList.Num() - 1)]; 

	GameVariables.Lives = 5; 

	GameVariables.bGameOver = false; 

	return GameVariables; 
}

// Check if the player's guess is an isogram
bool AGuessTheIsogramGameModeBase::bIsIsogram(const FString& Word)
{
	for (int32 Index = 0; Index < Word.Len(); Index++)
	{
		for (int32 Comparison = Index + 1; Comparison < Word.Len(); Comparison++)
		{
			if (Word[Index] == Word[Comparison])
				return false; 
		}
	}

	return true; 
}