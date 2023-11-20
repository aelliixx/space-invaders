// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Modules/HealthModule.h"
#include "GameFramework/Actor.h"
#include "Alien.generated.h"

UCLASS()
class SPACEINVADERS_API AAlien : public AActor
{
	GENERATED_BODY()

	FTimerHandle FireHandle;
	FTimerHandle MeshAnimationHandle;

	UPROPERTY()
	UMaterialInterface* RocketMaterial;

	UPROPERTY()
	TObjectPtr<UStaticMesh> NormalMesh;
	UPROPERTY()
	TObjectPtr<UStaticMesh> AlternateMesh;
	
	void Fire();

	uint8 CurrentMeshIndex;
	void SwapMesh();

protected:
	UPROPERTY()
	UHealthModule* Health;

	UPROPERTY()
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, Category=Score)
	int64 PointWorth = 10; // How many points is killing this alien worth

	UPROPERTY(EditAnywhere, Category=Stats)
	FVector2f FireInterval = {10, 20}; // How often the alien fires its weapons

	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type) override;

public:
	AAlien();
	virtual void Tick(float DeltaTime) override;

	UHealthModule* GetHealthModule() const;
	int64 GetPointWorth() const;
};
