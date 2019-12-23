// Fill out your copyright notice in the Description page of Project Settings.

#include "GuessTheIsogramGameModeBase.h"

// Called when the game starts
void AGuessTheIsogramGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	ChangeMenuWidget(StartingWidgetClass); 

	InitializeGame(); 

	GetHints(); 
	
	ProcessGuess(EnteredWord); 

	bIsIsogram(EnteredWord); 

	GetCorrectLetters(EnteredWord); 
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
	GameVariables.MysteryWord = WordList[FMath::RandRange(0, WordList.Num() - 1)]; 

	GameVariables.Lives = 5; 

	GameVariables.bGameNotOver = true; 

	return GameVariables; 
}

// Provide hints to the player 
FHints AGuessTheIsogramGameModeBase::GetHints()
{
	int32 Vowels = 0, Consonants = 0; 

	Hints.WordLength = TEXT("The word is ") + FString::FromInt(GameVariables.MysteryWord.Len()) + TEXT(" letters long"); 

	Hints.FirstLetter = TEXT("The first letter is "); 
	Hints.FirstLetter.AppendChar(GameVariables.MysteryWord[0]); 

	for (int32 Index = 0; Index < GameVariables.MysteryWord.Len(); Index++)
	{
		if (GameVariables.MysteryWord[Index] == 'a' || GameVariables.MysteryWord[Index] == 'e' || GameVariables.MysteryWord[Index] == 'i'
			|| GameVariables.MysteryWord[Index] == 'o' || GameVariables.MysteryWord[Index] == 'u')
			Vowels++;
		else
			Consonants++; 
	}
	
	Hints.Letters = TEXT("The word contains ") + FString::FromInt(Vowels) + TEXT(" vowel(s) and ") + FString::FromInt(Consonants) + 
		TEXT(" consonant(s)"); 

	return Hints; 
}

// Process the player's guess
FGameVariables AGuessTheIsogramGameModeBase::ProcessGuess(const FString& Guess)
{
	if (Guess == GameVariables.MysteryWord)
		GameVariables.bGameNotOver = false; 

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

FCorrectLetters AGuessTheIsogramGameModeBase::GetCorrectLetters(const FString& Guess)
{
	int32 SameLetterCount = 0, DifferentLetterCount = 0; 

	for (int32 GuessIndex = 0; GuessIndex < Guess.Len(); GuessIndex++)
	{
		if (Guess[GuessIndex] == GameVariables.MysteryWord[GuessIndex])
		{
			SameLetterCount++;
			continue; 
		}

		for (int32 MysteryIndex = 0; MysteryIndex < GameVariables.MysteryWord.Len(); MysteryIndex++)
		{
			if (Guess[GuessIndex] == GameVariables.MysteryWord[MysteryIndex])
			{
				DifferentLetterCount++;
				continue; 
			}
		}
	}

	CorrectLetters.SamePlaceLetter.Append(FString::FromInt(SameLetterCount)); 

	CorrectLetters.DifferentPlaceLetter.Append(FString::FromInt(DifferentLetterCount)); 

	return CorrectLetters; 
}