// Fill out your copyright notice in the Description page of Project Settings.

#include "GuessTheIsogramGameModeBase.h"

// Called when the game starts
void AGuessTheIsogramGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	ChangeMenuWidget(StartingWidgetClass); 

	InitializeGame(); 

	GetHints(); 

	bGuessedCorrectly(EnteredWord);

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
	UE_LOG(LogTemp, Warning, TEXT("Game initialized: %s"), *GameVariables.MysteryWord);

	GameVariables.Lives = 10; 

	GameVariables.bGameNotOver = true; 

	return GameVariables; 
}

// Provide hints to the player 
FHints AGuessTheIsogramGameModeBase::GetHints()
{
	int32 Vowels = 0, Consonants = 0; 

	Hints.WordLength = TEXT("The word is ") + FString::FromInt(GameVariables.MysteryWord.Len()) + TEXT(" letters long");
	UE_LOG(LogTemp, Warning, TEXT("Myster word: %s"), *GameVariables.MysteryWord);

	Hints.FirstLetter = TEXT("The first letter is "); 
	Hints.FirstLetter.AppendChar(GameVariables.MysteryWord[0]); 
	UE_LOG(LogTemp, Warning, TEXT("Myster word: %s"), *GameVariables.MysteryWord);

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
	UE_LOG(LogTemp, Warning, TEXT("Myster word: %s"), *GameVariables.MysteryWord);

	return Hints; 
}

// Check if the player guessed the mystery word correctly 
bool AGuessTheIsogramGameModeBase::bGuessedCorrectly(const FString& Guess)
{
	if (Guess == GameVariables.MysteryWord)
		return true;
	else
		return false; 
}

// If the player did not guess the mystery word correctly, figure out why and deduct a life where necessary
FGameVariables AGuessTheIsogramGameModeBase::ProcessGuess(const FString& Guess)
{
	if (!bIsIsogram(Guess))
	{
		GameVariables.Lives--; 

		if (GameVariables.Lives == 0)
			GameVariables.bGameNotOver = false; 
		else
			GameVariables.bGameNotOver = true;

		return GameVariables; 
	}

	if (Guess.Len() != GameVariables.MysteryWord.Len())
	{
		GameVariables.Lives--;

		if (GameVariables.Lives == 0)
			GameVariables.bGameNotOver = false;
		else
			GameVariables.bGameNotOver = true;

		return GameVariables; 
	}

	if (Guess != GameVariables.MysteryWord)
	{
		GameVariables.Lives--; 

		if (GameVariables.Lives == 0)
			GameVariables.bGameNotOver = false; 
		else
			GameVariables.bGameNotOver = true;

		return GameVariables; 
	}

	return GameVariables; 
}

// Check if the player's guess is an isogram
bool AGuessTheIsogramGameModeBase::bIsIsogram(const FString& Guess)
{
	for (int32 Index = 0; Index < Guess.Len(); Index++)
	{
		for (int32 Comparison = Index + 1; Comparison < Guess.Len(); Comparison++)
		{
			if (Guess[Index] == Guess[Comparison])
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