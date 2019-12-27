// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Blueprint/UserWidget.h"
#include "GuessTheIsogramGameModeBase.generated.h"

/**
 * 
 */

// Variables that will be used for game logic
USTRUCT(BlueprintType)
struct FGameVariables
{
	GENERATED_USTRUCT_BODY()
		
	UPROPERTY(BlueprintReadWrite)
	FString MysteryWord;

	UPROPERTY(BlueprintReadWrite)
	int32 Lives;

	UPROPERTY(BlueprintReadWrite)
	bool bGameNotOver; 

	UPROPERTY(BlueprintReadWrite)
	FString ErrorMessage; 
};

// Hints as to what the mystery word is
USTRUCT(BlueprintType)
struct FHints
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite)
	FString WordLength;

	UPROPERTY(BlueprintReadWrite)
	FString FirstLetter;

	UPROPERTY(BlueprintReadWrite)
	FString Letters;
};

// Amount of letters the player guessed correctly
USTRUCT(BlueprintType)
struct FCorrectLetters
{
	GENERATED_USTRUCT_BODY()

	// Letters the player guessed correctly, and are in the same place
	UPROPERTY(BlueprintReadWrite)
	FString SamePlaceHint = TEXT("Amount of letters guessed correctly and in the same place: ");

	UPROPERTY(BlueprintReadWrite)
	FString SamePlaceLetters; 

	// Letters the player guessed correctly, but are in a different place
	UPROPERTY(BlueprintReadWrite)
	FString DifferentPlaceHint = TEXT("Amount of letters guessed correctly but in the wrong place: "); 

	UPROPERTY(BlueprintReadWrite)
	FString DifferentPlaceLetters; 
};

UCLASS()
class GUESSTHEISOGRAM_API AGuessTheIsogramGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
	public:
		// Remove the current widget and create a new one
		UFUNCTION(BlueprintCallable, Category = "UMG Game")
			void ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass); 

		// Set up game variables
		UFUNCTION(BlueprintCallable, Category = "UMG Game")
			FGameVariables InitializeGame(); 

		FGameVariables GameVariables;

		// Provide hints to the player 
		UFUNCTION(BlueprintCallable, Category = "UMG Game")
			FHints GetHints(); 

		FHints Hints;  

		// Check if the player guessed the mystery word correctly 
		UFUNCTION(BlueprintCallable, Category = "UMG Game")
			bool bGuessedCorrectly(const FString& Guess); 

		// If the player did not guess the mystery word correctly, figure out why and deduct a life where necessary
		UFUNCTION(BlueprintCallable, Category = "UMG Game")
			FGameVariables ProcessGuess(const FString& Guess);

		// Check if the player's guess is an isogram
			bool bIsIsogram(const FString& Guess); 

		// Tell the player which letters they guessed correctly
		UFUNCTION(BlueprintCallable, Category = "UMG Game")
			FCorrectLetters GetCorrectLetters(const FString& Guess); 

		FCorrectLetters CorrectLetters; 

	protected:
		// Called when the game starts
		virtual void BeginPlay() override; 

		// The widget our game starts with
		UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG Game")
			TSubclassOf<UUserWidget> StartingWidgetClass; 

		// The widget instance we use as our menu
		UPROPERTY()
			UUserWidget* CurrentWidget; 

		// The player's guess
		UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG Game")
			FString EnteredWord; 

		// The total amount of lives
		UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG Game")
			int32 TotalLives; 

		const TArray<FString> WordList = 
		{
			TEXT("cat"),
			TEXT("bae"),
			TEXT("fish")
		};
};
