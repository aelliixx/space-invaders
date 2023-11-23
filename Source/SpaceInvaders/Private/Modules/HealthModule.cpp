// 2023, Donatas Mockus, https://github.com/aelliixx/space-invaders


#include "Modules/HealthModule.h"

#include "AI/Alien.h"
#include "Player/ShipController.h"
#include "Player/ShipPlayer.h"


void UHealthModule::OnDeath(AActor* Source)
{
	FOnDeathDelegate.Broadcast(GetOwner(), Source);
}

UHealthModule::UHealthModule()
{
	PrimaryComponentTick.bCanEverTick = false;
}


void UHealthModule::BeginPlay()
{
	Super::BeginPlay();
}


void UHealthModule::DoDamage(const float HitPoints, AActor* Source)
{
	CurrentHP = FMath::Clamp(CurrentHP - HitPoints, 0, MaxHP);
	if (const AShipController* PlayerController = Cast<AShipController>(GetOwner()))
		PlayerController->OnHealthChangedDelegate.Broadcast(CurrentHP);

	if (CurrentHP <= 0)
		OnDeath(Source);
}

void UHealthModule::SetMaxHP(const float HitPoints)
{
	MaxHP = HitPoints;
	CurrentHP = HitPoints;
}

float UHealthModule::GetCurrentHealth() const
{
	return CurrentHP;
}

float UHealthModule::GetMaxHP() const
{
	return MaxHP;
}

void UHealthModule::ResetHealth()
{
	CurrentHP = MaxHP;
}

bool UHealthModule::IsDead() const
{
	return CurrentHP <= 0;
}
