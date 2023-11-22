// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/LeaderboardWidget.h"

#include "SpaceInvadersGameInstance.h"
#include "Blueprint/WidgetTree.h"

void ULeaderboardEntry::SetEntry(const FText& Score, const FText& Name)
{
	ScoreTextBlock->SetText(Score);
	NameTextBlock->SetText(Name);
}

ULeaderboardWidget::ULeaderboardWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	static ConstructorHelpers::FClassFinder<ULeaderboardEntry> EntryWidget(
		TEXT("/Game/SpaceInvaders/UI/W_LeaderboardEntry"));
	EntryWidgetClass = EntryWidget.Class;
}

void ULeaderboardWidget::CreateLeaderboard()
{
	const auto Leaderboard = Cast<USpaceInvadersGameInstance>(GetGameInstance())
	                         ->LoadLeaderboard()
	                         ->Leaderboard
	                         .Map;

	if (Leaderboard.Num() == 0)
	{
		const auto EntryWidget = WidgetTree->ConstructWidget<UTextBlock>();
		if (!EntryWidget) return;
		EntryWidget->SetText(FText::FromString("No players yet"));
		FSlateFontInfo FontInfo;

		TObjectPtr<UObject> FontObject = LoadObject<UObject>(
			this, TEXT("/Game/SpaceInvaders/Art/Fonts/VT323-Regular_Font"));
		if (FontObject)
			FontInfo.FontObject = FontObject;

		FontInfo.Size = 24;
		EntryWidget->SetJustification(ETextJustify::Center);
		EntryWidget->SetFont(FontInfo);
		Container->AddChildToVerticalBox(EntryWidget);
		return;
	}

	// Convert the map to an array sorted by score and limited to 10 entries
	TArray<FName> LeaderboardArray;
	Leaderboard.GenerateKeyArray(LeaderboardArray);
	LeaderboardArray.Sort([&Leaderboard](const FName& A, const FName& B)
	{
		return Leaderboard[A] > Leaderboard[B];
	});
	LeaderboardArray.SetNum(FMath::Min(10, LeaderboardArray.Num()));

	for (const auto& Name : LeaderboardArray)
	{
		const auto EntryWidget = CreateWidget<ULeaderboardEntry>(this, EntryWidgetClass, Name);
		if (!EntryWidget) return;
		EntryWidget->SetEntry(
			FText::FromString(FString::FromInt(Leaderboard[Name])),
			FText::FromName(Name));
		Container->AddChildToVerticalBox(EntryWidget);
	}
}

void ULeaderboardWidget::NativeConstruct()
{
	Super::NativeConstruct();
	CreateLeaderboard();
}
