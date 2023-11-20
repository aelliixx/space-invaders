// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "ShipPlayer.generated.h"

UCLASS()
class SPACEINVADERS_API AShipPlayer : public APawn
{
	GENERATED_BODY()

	FTimerHandle FireDelayHandle;
	bool CanFire = true;


public:
	// Sets default values for this pawn's properties
	AShipPlayer();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category=Mesh, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* PlayerMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category=Movement, meta = (AllowPrivateAccess = "true"))
	class UFloatingPawnMovement* PlayerMovement;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Shooting)
	float FireDelay = 0.5f;

	void ResetFire() { CanFire = true; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	void MoveRight(const float);
	void Fire();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
