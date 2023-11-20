// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthModule.generated.h"

DECLARE_MULTICAST_DELEGATE_TwoParams(FOnDeathSignature, AActor* /* It */, AActor* /* Killer */)

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SPACEINVADERS_API UHealthModule final : public UActorComponent
{
	GENERATED_BODY()

	void OnDeath(AActor* = nullptr);

public:
	UHealthModule();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	void DoDamage(float, AActor* = nullptr);
	void SetMaxHP(float);
	float GetCurrentHealth() const;
	float GetMaxHP() const;

	FOnDeathSignature FOnDeathDelegate;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Health)
	float MaxHP = 100;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Health)
	float CurrentHP = MaxHP;
};
