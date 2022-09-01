// Fill out your copyright notice in the Description page of Project Settings.


#include "FireballActor.h"
#include "Eye.h"

AEye* AttachedEye;

// Sets default values
AFireballActor::AFireballActor()
{
	PrimaryActorTick.bCanEverTick = true;
	IsAttacking = false;
	IsMovingToSocketComplete = true;
}

void AFireballActor::BeginPlay()
{
	Super::BeginPlay();

	TArray<USpringArmComponent*> SpringArms;
	GetParentActor()->GetComponents<USpringArmComponent>(SpringArms);
	if (BallType == BallType::Fire)
	{
		DefaultSocket = SpringArms[2];
	} 
	else if (BallType == BallType::Ice)
	{
		DefaultSocket = SpringArms[3];
	}

	CurrentSocket = DefaultSocket;
	MeshSphere = FindComponentByClass<UStaticMeshComponent>();
}

void AFireballActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (CurrentSocket != DefaultSocket && !ShouldComeBack())
	{
		SetActorLocation
		(
			FMath::VInterpTo
			(
				GetActorLocation(),
				CurrentSocket->GetComponentTransform().GetLocation(),
				DeltaTime,
				3.f
			),
			true
		);
	}
	else if (IsAttacking && !ShouldComeBack())
	{
		SetActorLocation
		(
			FMath::VInterpTo
			(
				GetActorLocation(),
				TargetLoc,
				DeltaTime,
				FireballSpeedFire
			),
			true
		);
	}
	else if (CurrentSocket->GetComponentTransform().GetLocation() != GetActorLocation())
	{
		FVector loc = DefaultSocket->GetComponentTransform().GetLocation();
		SetActorLocation
		(
			FMath::VInterpTo
			(
				GetActorLocation(),
				loc,
				DeltaTime,
				3.f
			),
			false
		);

		if (FVector::Dist(loc, GetActorLocation()) < 20)
		{
			MeshSphere->SetSimulatePhysics(true);
		}
	}
}

void AFireballActor::Fire()
{
	if (!IsAttacking)
	{
		RaycastFromCamera();
		IsAttacking = true;
		if (CurrentSocket == DefaultSocket)
		{
			TargetLoc = GetWorld()->GetFirstPlayerController()->PlayerCameraManager->GetActorForwardVector();
			TargetLoc *= FireballRange;
			TargetLoc += GetWorld()->GetFirstPlayerController()->PlayerCameraManager->GetTransform().GetLocation();
		}
	}
	else
	{
		if (AttachedEye)
		{
			AttachedEye->IsSocketFilled = false;
			AttachedEye->SetBall(nullptr);
			AttachedEye = nullptr;

		}
		CurrentSocket = DefaultSocket;
		AttachToComponent(
			CurrentSocket,
			FAttachmentTransformRules::KeepWorldTransform
		);
		IsAttacking = false;
	}
}

void AFireballActor::RaycastFromCamera()
{
	TArray<FHitResult> hits;
	FVector forward = GetWorld()->GetFirstPlayerController()->PlayerCameraManager->GetActorForwardVector();
	FVector start = GetWorld()->GetFirstPlayerController()->PlayerCameraManager->GetTransform().GetLocation();
	FVector end = (forward * FireballRange) + start;
	FCollisionQueryParams* col = new FCollisionQueryParams();
	col->AddIgnoredActor(this);

	if (GetWorld()->LineTraceMultiByChannel(hits, start, end, ECC_Camera, *col))
	{
		for (FHitResult hit : hits)
		{
			AEye* Eye = Cast<AEye>(hit.GetActor());
			if (Eye && !Eye->IsSocketFilled)
			{
				CurrentSocket = Eye->GetSocket();
				AttachedEye = Eye;
				Eye->IsSocketFilled = true;
				Eye->SetBall(this);

				AttachToComponent(
					CurrentSocket,
					FAttachmentTransformRules::KeepWorldTransform
				);

				MeshSphere->SetSimulatePhysics(false);

				if (Eye->BallType == BallType)
				{
					UE_LOG(LogTemp, Log, TEXT("Same type"));
				}
			}
		}
	}
}

void AFireballActor::HitTheGround()
{
	if (MeshSphere->GetLinearDamping() != 30)
	{
		MeshSphere->AddImpulse(FVector(0.f, 0.f, 8000));
		MeshSphere->SetLinearDamping(30);
	}
	else
	{
		MeshSphere->AddImpulse(FVector(0.f, 0.f, -4000.f));
		MeshSphere->SetLinearDamping(1);
	}
}

bool AFireballActor::ShouldComeBack()
{
	if (FVector::Dist(GetParentActor()->GetActorLocation(), GetActorLocation()) > 1500)
	{
		if (AttachedEye)
		{
			AttachedEye->IsSocketFilled = false;
			AttachedEye->SetBall(nullptr);
			AttachedEye = nullptr;
		}
		CurrentSocket = DefaultSocket;
		IsAttacking = false;
		return true;
	}
	return false;
}