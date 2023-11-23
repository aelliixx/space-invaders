// 2023, Donatas Mockus, https://github.com/aelliixx/space-invaders

#pragma once

#include "CoreMinimal.h"
#include "NameEntry.h"
#include "AI/Alien.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "MainMenu.generated.h"

/**
 * 
 */
UCLASS()
class SPACEINVADERS_API UMainMenu : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UButton> StartGameButton;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UButton> QuitGameButton;
	UPROPERTY(meta=(BindWidget))
	
	TObjectPtr<UTextBlock> CrabPoints;
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> OctopusPoints;

	TSubclassOf<UNameEntry> NameEntryWidgetClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AAlien> CrabClass;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AAlien> OctopusClass;

	

	UFUNCTION()
	void QuitGame();
	UFUNCTION()
	void StartGame();
	
public:

	UMainMenu(const FObjectInitializer& ObjectInitializer);
	
	virtual void NativeConstruct() override;
};
