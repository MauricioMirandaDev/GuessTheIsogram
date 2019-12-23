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
	FString SamePlaceLetter = TEXT("Amount of letters guessed correctly and in the same place: ");

	// Letters the player guessed correctly, but are in a different place
	UPROPERTY(BlueprintReadWrite)
	FString DifferentPlaceLetter = TEXT("Amount of letters guessed correctly but in the wrong place: "); 
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

		// Check if the player correctly guessed the mystery word
		UFUNCTION(BlueprintCallable, Category = "UMG Game")
			FGameVariables GuessedCorrectly(const FString& Guess); 

		// Check if the player's guess is an isogram
		UFUNCTION(BlueprintCallable, Category = "UMG Game")
			bool bIsIsogram(const FString& Guess); 

		// Check if the player's guess is the same length
		UFUNCTION(BlueprintCallable, Category = "UMG Game")
			bool bIsSameLength(const FString& Guess); 

		// Tell the player which letters they guessed correctly
		UFUNCTION(BlueprintCallable, Category = "UMG Game")
			FCorrectLetters GetCorrectLetters(const FString& Guess); 

		FCorrectLetters CorrectLetters; 

		// Check if the player is out of lives
		UFUNCTION(BlueprintCallable, Category = "UMG Game")
			FGameVariables OutOfLives(); 

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

		const TArray<FString> WordList = 
		{
			TEXT("red"),
			TEXT("ray"),
			TEXT("dog"),
			TEXT("cat")
		};
};
