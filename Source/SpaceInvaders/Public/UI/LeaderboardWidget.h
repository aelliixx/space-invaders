// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/HorizontalBox.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "LeaderboardWidget.generated.h"

/**
 * 
 */

UCLASS()
class ULeaderboardEntry : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> ScoreTextBlock;
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> NameTextBlock;
public:

	void SetEntry(const FText& Score, const FText& Name);
};

UCLASS()
class SPACEINVADERS_API ULeaderboardWidget : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UVerticalBox> Container;

	UPROPERTY()
	TSubclassOf<ULeaderboardEntry> EntryWidgetClass;

public:
	ULeaderboardWidget(const FObjectInitializer& ObjectInitializer);

	void CreateLeaderboard();
	virtual void NativeConstruct() override;
};
