// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/ShipController.h"


void AShipController::OnDeath(AActor* It, AActor* Source)
{
	if (It == this)
	{
		GEngine->AddOnScreenDebugMessage(static_cast<uint64>(-1), 5, FColor::Orange, TEXT("Player died!"));
		// TODO: Handle player death
	}
}

AShipController::AShipController()
{
	Health = CreateDefaultSubobject<UHealthModule>(TEXT("Health"));
	Score = CreateDefaultSubobject<UScoreModule>(TEXT("Score"));
}

void AShipController::BeginPlay()
{
	Super::BeginPlay();
	Health->FOnDeathDelegate.AddUObject(this, &AShipController::OnDeath);
}

UHealthModule* AShipController::GetHealthModule() const
{
	return Health;
}

UScoreModule* AShipController::GetScoreModule() const
{
	return Score;
}
