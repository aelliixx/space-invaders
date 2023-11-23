// 2023, Donatas Mockus, https://github.com/aelliixx/space-invaders


#include "UI/ScoreText.h"
#include "Components/TextBlock.h"
#include "Player/ShipController.h"
#include "Player/ShipPlayer.h"
#include "UI/HUDManager.h"


void UScoreText::SetScore(const int64 Score)
{
	ScoreText->SetText(FText::Format(FTextFormat::FromString(TEXT("Score: {0}")), Score));
}

void UScoreText::NativeConstruct()
{
	Super::NativeConstruct();
	Cast<AShipController>(GetOwningPlayer())->OnScoreChangedDelegate.AddUObject(this, &UScoreText::SetScore);
}
