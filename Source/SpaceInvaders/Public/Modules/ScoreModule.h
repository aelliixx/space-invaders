// 2023, Donatas Mockus, https://github.com/aelliixx/space-invaders

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
	void ResetScore();

protected:
	virtual void BeginPlay() override;

};
