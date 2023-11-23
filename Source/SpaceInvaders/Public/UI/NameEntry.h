// 2023, Donatas Mockus, https://github.com/aelliixx/space-invaders

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/EditableText.h"
#include "NameEntry.generated.h"

/**
 * 
 */
UCLASS()
class SPACEINVADERS_API UNameEntry : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UEditableText> NameField;
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UButton> ConfirmButton;
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UButton> CancelButton;

	UFUNCTION()
	void LoadGame();
	UFUNCTION()
	void Cancel();
	UFUNCTION()
	void ValidateName(const FText& Text);

public:
	virtual void NativeConstruct() override;
};
