// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"

// Sets default values
AProjectile::AProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> Mesh(TEXT("/Game/LevelPrototyping/Meshes/SM_Cylinder.SM_Cylinder"));

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));

	if (Mesh.Succeeded())
	{
		ProjectileMesh->SetStaticMesh(Mesh.Object);
		ProjectileMesh->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
		ProjectileMesh->SetWorldScale3D(FVector(1.f));
		ProjectileMesh->BodyInstance.SetCollisionProfileName("Projectile");
		ProjectileMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
		ProjectileMesh->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
		ProjectileMesh->CanCharacterStepUpOn = ECB_No;
	}


	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = ProjectileMesh;
	ProjectileMovement->InitialSpeed = 1000.f;
	ProjectileMovement->MaxSpeed = 1000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;

	InitialLifeSpan = 1.5f;
}

void AProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// Only add impulse and destroy projectile if we hit a physics
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
	{
		AMegajamCharacter* Player = Cast<AMegajamCharacter>(OtherActor);
		if (Player)
		{
			Player->LaunchCharacter(GetVelocity(), true, true);
		}

		Destroy();
	}
}