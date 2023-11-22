// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Alien.h"
#include "GameFramework/Actor.h"
#include "EnemyGrid.generated.h"


USTRUCT()
struct FGridLayout : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<AAlien>> SpawnList;
	UPROPERTY(EditAnywhere)
	FVector2f EnemySize = {90, 90};

	UPROPERTY(EditAnywhere)
	int32 ColumnSize = 5;

	UPROPERTY(EditAnywhere)
	FVector2D MovementSpeed = {-1, 15};

	// When the aliens wrap around the screen, how much more should they move towards the player
	UPROPERTY(EditAnywhere)
	double WrapXDisplacement = 20;

	UPROPERTY(EditAnywhere)
	FVector2D SideBounds = {-1300, 1300};

	UPROPERTY(EditAnywhere)
	double LowerBound = 600;
};

UCLASS()
class SPACEINVADERS_API AEnemyGrid : public AActor
{
	GENERATED_BODY()

	FTimerHandle MoveLoop;

	UPROPERTY()
	TArray<AAlien*> AliveEnemies;

	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root;

	UPROPERTY(VisibleAnywhere)
	FGridLayout Grid;
	UPROPERTY(VisibleAnywhere)
	float GridWidth;

	FVector OriginalLocation;

	void InitialiseGrid();
	void ResetGrid();
	void MoveGrid();
	bool AreAnyAlive() const;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UDataTable> GridData;

	UPROPERTY(EditAnywhere)
	int32 CurrentLevel = 1;
	
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:
	// Sets default values for this actor's properties
	AEnemyGrid();
	virtual void Tick(float DeltaTime) override;


};
