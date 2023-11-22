// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Modules/HealthModule.h"
#include "Modules/ScoreModule.h"
#include "GameFramework/PlayerController.h"
#include "ShipController.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnScoreChangedSignature, int64);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnHealthChangedSignature, float);

UCLASS()
class SPACEINVADERS_API AShipController : public APlayerController
{
	GENERATED_BODY()

	bool IsDead = false;

	UPROPERTY(VisibleAnywhere, Category=Health, meta = (AllowPrivateAccess = "true"))
	UHealthModule* Health;

	UPROPERTY(VisibleAnywhere)
	UScoreModule* Score;

	FName PlayerName;

	void OnDeath(AActor*, AActor*);
	void OnLowerBoundReached();

public:
	AShipController();
	virtual void BeginPlay() override;
	UHealthModule* GetHealthModule() const;
	UScoreModule* GetScoreModule() const;
	void SetPlayerName(FName);
	FName GetPlayerName() const;
	void ShowMouseCursor(const bool);

	FOnScoreChangedSignature OnScoreChangedDelegate;
	FOnHealthChangedSignature OnHealthChangedDelegate;
};
