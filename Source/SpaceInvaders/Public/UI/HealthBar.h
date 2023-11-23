// 2023, Donatas Mockus, https://github.com/aelliixx/space-invaders

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HealthBar.generated.h"

/**
 * 
 */
UCLASS()
class SPACEINVADERS_API UHealthBar : public UUserWidget
{
	GENERATED_BODY()
	
	UPROPERTY(meta=(BindWidget))
	class UProgressBar* Bar;

	float MaxHP;

	UFUNCTION()
	void SetHealth(const float Health);
	virtual void NativeConstruct() override;
};
