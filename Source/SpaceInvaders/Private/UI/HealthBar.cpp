// 2023, Donatas Mockus, https://github.com/aelliixx/space-invaders


#include "UI/HealthBar.h"

#include "Components/ProgressBar.h"
#include "Player/ShipController.h"
#include "UI/HUDManager.h"


void UHealthBar::SetHealth(const float Health)
{
	Bar->SetPercent(Health / MaxHP);
}

void UHealthBar::NativeConstruct()
{
	Super::NativeConstruct();
	const auto Controller = Cast<AShipController>(GetOwningPlayer());
	Controller->OnHealthChangedDelegate.AddUObject(this, &UHealthBar::SetHealth);
	MaxHP = Controller->GetHealthModule()->GetMaxHP();
	Bar->SetPercent(Controller->GetHealthModule()->GetCurrentHealth() / MaxHP);
}
