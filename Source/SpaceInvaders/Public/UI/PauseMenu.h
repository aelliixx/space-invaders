// 2023, Donatas Mockus, https://github.com/aelliixx/space-invaders

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "PauseMenu.generated.h"

/**
 * 
 */
UCLASS()
class SPACEINVADERS_API UPauseMenu : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UButton> ResumeButton;
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UButton> QuitButton;
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> ScoreText;

	UFUNCTION()
	void OnResumeClicked();
	UFUNCTION()
	void OnQuitClicked();

public:
	virtual void NativeConstruct() override;
	void SetScore(int64);
};
