// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/EnemyGrid.h"
#include "DrawDebugHelpers.h"
#include "SpaceInvadersGameState.h"


void AEnemyGrid::InitialiseGrid()
{
	GridWidth = Grid.ColumnSize * Grid.EnemySize.Y;
	double RowPosition = Grid.EnemySize.Y / 2;
	for (int32 Row = 0; Row < Grid.SpawnList.Num(); ++Row)
	{
		// Center the aliens on screen 
		double ColPosition = (2 * GetActorLocation().Y - Grid.EnemySize.X * Grid.ColumnSize + Grid.EnemySize.X) / 2;
		for (int32 Col = 0; Col < Grid.ColumnSize; ++Col)
		{
			FVector Position = FVector{RowPosition, ColPosition, 0} + GetActorLocation();
			ColPosition += Grid.EnemySize.X;
			if (!Grid.SpawnList[Row])
				continue;
			auto Enemy = GetWorld()->SpawnActor<AAlien>(Grid.SpawnList[Row], Position, FRotator::ZeroRotator);
			Enemy->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
			AliveEnemies.Add(Enemy);
		}
		RowPosition += Grid.EnemySize.Y;
	}
}

void AEnemyGrid::ResetGrid()
{
	if (!GridData) return;
	SetActorLocation(OriginalLocation);
	AliveEnemies.Empty();
	if (const auto NewGrid = GridData->FindRow<FGridLayout>(FName{FString::FromInt(CurrentLevel)},
	                                                        FString::FromInt(CurrentLevel)))
	{
		Grid = *NewGrid;
		InitialiseGrid();
	}
}

void AEnemyGrid::MoveGrid()
{
	const FVector AddMovement{Grid.MovementSpeed.X, Grid.MovementSpeed.Y, 0.0};
	SetActorLocation(GetActorLocation() + AddMovement);

	if (GetActorLocation().Y + GridWidth / 2 >= Grid.SideBounds.Y)
	{
		const FVector NewLocation{
			GetActorLocation().X + Grid.WrapXDisplacement, Grid.SideBounds.X + GridWidth / 2, 0.0
		};
		SetActorLocation(NewLocation);
	}

	for (const auto Enemy : AliveEnemies)
	{
		if (Enemy)
			Enemy->SwapMesh();
	}

	if (GetActorLocation().X <= Grid.LowerBound)
	{
		Cast<ASpaceInvadersGameState>(GetWorld()->GetGameState())->OnLowerBoundReachedDelegate.Broadcast();
		GetWorld()->GetTimerManager().ClearTimer(MoveLoop);
	}
}

bool AEnemyGrid::AreAnyAlive() const
{
	for (const auto& Enemy : AliveEnemies)
	{
		if (Enemy && !Enemy->GetHealthModule()->IsDead())
			return true;
	}
	return false;
}

AEnemyGrid::AEnemyGrid()
{
	PrimaryActorTick.bCanEverTick = true;
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
}

void AEnemyGrid::BeginPlay()
{
	Super::BeginPlay();
	OriginalLocation = GetActorLocation();
	ResetGrid();
	GetWorld()->GetTimerManager().SetTimer(MoveLoop, this, &AEnemyGrid::MoveGrid, 1.0f, true);
}

void AEnemyGrid::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	GetWorld()->GetTimerManager().ClearAllTimersForObject(this);
}

void AEnemyGrid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!AreAnyAlive())
	{
		int Null = 0;
		int Dead = 0;
		for (const auto& Enemy : AliveEnemies)
		{
			if (!Enemy)
			{
				Null++;
				continue;
			}
			if (Enemy->GetHealthModule()->IsDead())
			{
				Dead++;
				GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Dead enemy: ") +
										 FString::FromInt(Enemy->GetHealthModule()->GetCurrentHealth()));
				continue;
			}
		}
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("No enemies alive. Enemy count: ") +
								 FString::FromInt(AliveEnemies.Num()));
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Null: ") + FString::FromInt(Null));
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Dead: ") + FString::FromInt(Dead));
		++CurrentLevel %= GridData->GetRowNames().Num() + 1;
		ResetGrid();
	}
}
