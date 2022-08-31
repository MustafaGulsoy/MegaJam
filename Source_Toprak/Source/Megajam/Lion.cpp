// Fill out your copyright notice in the Description page of Project Settings.


#include "Lion.h"

// Sets default values
ALion::ALion()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MuzzleOffset = FVector(100.0f, 0.0f, 10.0f);
}

// Called when the game starts or when spawned
void ALion::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ALion::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ProjectileFireTimer += DeltaTime;

	if (ProjectileFireTimer >= Cooldown)
	{
		RaycastToFindPlayer();
	}

}

void ALion::RaycastToFindPlayer()
{
	TArray<FHitResult> hits;
	FVector forward = GetActorForwardVector();
	FVector start = GetActorLocation();
	FVector end = (forward * RaycastRange) + start;
	FCollisionQueryParams* col = new FCollisionQueryParams();
	col->AddIgnoredActor(this);

	DrawDebugLine(GetWorld(), start, end, FColor::Orange, false);

	if (GetWorld()->LineTraceMultiByChannel(hits, start, end, ECC_Pawn, *col))
	{
		for (FHitResult hit : hits)
		{
			AMegajamCharacter* Player = Cast<AMegajamCharacter>(hit.GetActor());
			
			if (Player)
			{
				Fire();
			}
		}
	}
}

void ALion::Fire()
{
	if (ProjectileClass != nullptr)
	{
		UWorld* const World = GetWorld();
		if (World != nullptr)
		{
			ProjectileFireTimer = 0;

			const FRotator SpawnRotation = GetActorRotation();
			const FVector SpawnLocation = GetActorLocation() + SpawnRotation.RotateVector(MuzzleOffset);

			FActorSpawnParameters ActorSpawnParams;
			ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

			World->SpawnActor<AProjectile>(ProjectileClass, SpawnLocation, SpawnRotation, ActorSpawnParams);
		}
	}
}

