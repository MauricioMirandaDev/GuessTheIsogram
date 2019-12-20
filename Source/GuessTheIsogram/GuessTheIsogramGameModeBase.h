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
	bool bGameOver; 
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

	protected:
		// Called when the game starts
		virtual void BeginPlay() override; 

		// The widget our game starts with
		UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG Game")
			TSubclassOf<UUserWidget> StartingWidgetClass; 

		// The widget instance we use as our menu
		UPROPERTY()
			UUserWidget* CurrentWidget; 

		const TArray<FString> WordList = 
		{
			TEXT("red"),
			TEXT("ray"),
			TEXT("dog"),
			TEXT("cat")
		};
};
