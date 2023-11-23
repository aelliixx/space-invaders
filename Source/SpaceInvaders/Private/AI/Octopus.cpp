// 2023, Donatas Mockus, https://github.com/aelliixx/space-invaders


#include "AI/Octopus.h"


AOctopus::AOctopus()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> Octopus1(TEXT("/Game/SpaceInvaders/Art/3D/Octopus1.Octopus1"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> Octopus2(TEXT("/Game/SpaceInvaders/Art/3D/Octopus2.Octopus2"));
	NormalMesh = Octopus1.Object;
	AlternateMesh = Octopus2.Object;
	Mesh->SetStaticMesh(NormalMesh);
	
	PointWorth = 20;
	FireInterval = {5, 30};
	ChanceToDropPowerup = 0.1f;

	Health->SetMaxHP(15);
}
