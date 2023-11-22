// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "Leaderboard/Leaderboard.h"
#include "LeaderboardSaveGame.generated.h"

/**
 * 
 */



UCLASS()
class SPACEINVADERS_API ULeaderboardSaveGame : public USaveGame
{
	GENERATED_BODY()
public:
	UPROPERTY()
	FLeaderboard Leaderboard;
};
