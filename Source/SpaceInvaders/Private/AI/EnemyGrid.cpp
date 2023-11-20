// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/EnemyGrid.h"
#include "DrawDebugHelpers.h"
#include "Components/BillboardComponent.h"


// Sets default values
AEnemyGrid::AEnemyGrid()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickInterval = 1;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
}

// Called when the game starts or when spawned
void AEnemyGrid::BeginPlay()
{
	Super::BeginPlay();
	Width = ColumnSize * EnemySize.Y;
	double RowPosition = EnemySize.Y / 2;
	for (int32 Row = 0; Row < SpawnList.Num(); ++Row)
	{
		// Center the aliens on screen 
		double ColPosition = (2 * GetActorLocation().Y - EnemySize.X * ColumnSize + EnemySize.X) / 2;
		for (int32 Col = 0; Col < ColumnSize; ++Col)
		{
			FVector Position = FVector{RowPosition, ColPosition, 0} + GetActorLocation();
			ColPosition += EnemySize.X;
			if (!SpawnList[Row])
				continue;
			auto Enemy = GetWorld()->SpawnActor<AAlien>(SpawnList[Row], Position, FRotator::ZeroRotator);
			Enemy->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
			AliveEnemies.Add(Enemy);
		}
		RowPosition += EnemySize.Y;
	}
}

// Called every frame
void AEnemyGrid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	const FVector AddMovement{MovementSpeed.X * DeltaTime, MovementSpeed.Y * DeltaTime, 0.0};
	SetActorLocation(GetActorLocation() + AddMovement);

	if (GetActorLocation().Y + Width / 2 >= SideBounds.Y)
	{
		const FVector NewLocation{GetActorLocation().X + WrapXDisplacement, SideBounds.X + Width / 2, 0.0};
		SetActorLocation(NewLocation);
	}

	if (GetActorLocation().X<= LowerBound)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Orange, TEXT("YOU LOST!"));
		PrimaryActorTick.UnRegisterTickFunction();
	}
}
