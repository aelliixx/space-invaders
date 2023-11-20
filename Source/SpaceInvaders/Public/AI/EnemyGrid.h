// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Alien.h"
#include "GameFramework/Actor.h"
#include "EnemyGrid.generated.h"

UCLASS()
class SPACEINVADERS_API AEnemyGrid : public AActor
{
	GENERATED_BODY()

	UPROPERTY()
	TArray<AAlien*> AliveEnemies;

	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root;


public:
	// Sets default values for this actor's properties
	AEnemyGrid();

	UPROPERTY(VisibleAnywhere)
	float Width;

	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<AAlien>> SpawnList;
	UPROPERTY(EditAnywhere)
	FVector2f EnemySize;

	UPROPERTY(EditAnywhere)
	int32 ColumnSize = 5;

	UPROPERTY(EditAnywhere)
	FVector2D MovementSpeed;

	// When the aliens wrap around the screen, how much more should they move towards the player
	UPROPERTY(EditAnywhere)
	double WrapXDisplacement;

	UPROPERTY(EditAnywhere)
	FVector2D SideBounds;

	UPROPERTY(EditAnywhere)
	double LowerBound;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
