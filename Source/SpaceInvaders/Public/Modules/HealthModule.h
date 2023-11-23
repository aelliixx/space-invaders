// 2023, Donatas Mockus, https://github.com/aelliixx/space-invaders

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

	void DoDamage(float, AActor* = nullptr);
	void SetMaxHP(float);
	float GetCurrentHealth() const;
	float GetMaxHP() const;
	void ResetHealth();
	bool IsDead() const;

	FOnDeathSignature FOnDeathDelegate;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Health)
	float MaxHP = 100;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Health)
	float CurrentHP = MaxHP;
};
