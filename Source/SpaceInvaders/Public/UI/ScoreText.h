// 2023, Donatas Mockus, https://github.com/aelliixx/space-invaders

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ScoreText.generated.h"

UCLASS()
class SPACEINVADERS_API UScoreText : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(meta=(BindWidget))
	class UTextBlock* ScoreText;

	UFUNCTION()
	void SetScore(const int64 Score);
	virtual void NativeConstruct() override;
};
