// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "Leaderboard.generated.h"

/**
 * 
 */
USTRUCT()
struct FLeaderboard
{
	GENERATED_BODY()
	// PlayerName, Score
	UPROPERTY()
	TMap<FName, int64> Map;
};