// 2023, Donatas Mockus, https://github.com/aelliixx/space-invaders

#pragma once

#include "CoreMinimal.h"
#include "HealthBar.h"
#include "ScoreText.h"
#include "Blueprint/UserWidget.h"
#include "PlayerHUD.generated.h"

/**
 * 
 */
UCLASS()
class SPACEINVADERS_API UPlayerHUD : public UUserWidget
{
	GENERATED_BODY()

	void NativeConstruct() override;

	UPROPERTY(meta=(BindWidget))
	UHealthBar* HealthBar;
	UPROPERTY(meta=(BindWidget))
	UScoreText* ScoreText;
};
