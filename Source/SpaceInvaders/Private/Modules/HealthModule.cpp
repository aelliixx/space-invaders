// Fill out your copyright notice in the Description page of Project Settings.


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
	PrimaryComponentTick.bCanEverTick = true;
}


void UHealthModule::BeginPlay()
{
	Super::BeginPlay();
}


void UHealthModule::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UHealthModule::DoDamage(const float HitPoints, AActor* Source)
{
	CurrentHP = FMath::Max(0, CurrentHP - HitPoints);
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
