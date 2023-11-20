// Fill out your copyright notice in the Description page of Project Settings.


#include "Modules/ScoreModule.h"

#include "Player/ShipController.h"
#include "Player/ShipPlayer.h"


int64 UScoreModule::GetScore() const
{
	return Score;
}

void UScoreModule::BeginPlay()
{
	Super::BeginPlay();
}


void UScoreModule::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UScoreModule::AddScore(const int64 Points)
{
	Score += Points;
	if (const AShipController* Controller = Cast<AShipController>(GetOwner()))
	{
		Controller->OnScoreChangedDelegate.Broadcast(Score);
	}
}
