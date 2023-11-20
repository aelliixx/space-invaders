// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ScoreModule.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SPACEINVADERS_API UScoreModule final : public UActorComponent
{
	GENERATED_BODY()

	int64 Score = 0;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void AddScore(const int64);
	int64 GetScore() const;

protected:
	virtual void BeginPlay() override;

};
