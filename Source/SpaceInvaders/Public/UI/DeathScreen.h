// 2023, Donatas Mockus, https://github.com/aelliixx/space-invaders

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "DeathScreen.generated.h"

UCLASS()
class SPACEINVADERS_API UDeathScreen : public UUserWidget
{
	GENERATED_BODY()
	UPROPERTY(meta=(BindWidget))
	UTextBlock* ScoreText;

	UPROPERTY(meta=(BindWidget))
	UButton* Restart;

	UPROPERTY(meta=(BindWidget))
	UButton* MainMenu;

	UFUNCTION()
	void OnRestart();
	UFUNCTION()
	void OnExitToMainMenu();

public:
	void SetScore(int64) const;
	virtual void NativeConstruct() override;
};
