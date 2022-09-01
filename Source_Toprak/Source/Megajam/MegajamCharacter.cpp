// Copyright Epic Games, Inc. All Rights Reserved.

#include "MegajamCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include <Runtime/Engine/Classes/Components/SphereComponent.h>

//////////////////////////////////////////////////////////////////////////
// AMegajamCharacter

AMegajamCharacter::AMegajamCharacter()
{

	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;


	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	IsDashed = false;
	DashStartTime = 0;
	CollectedCrystalNum = 0;
}

void AMegajamCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	DashStartTime += DeltaTime;

	if (IsDashed && DashStartTime >= 1.f)
	{
		FindComponentByClass<UMeshComponent>()->SetVisibility(true);
	}

	if (DashStartTime >= DashCooldown)
	{
		IsDashed = false;
	}

	if (GrabbedObject)
	{
		FQuat x = GetWorld()->GetFirstPlayerController()->PlayerCameraManager->GetActorQuat();
		x.Y = 0;
		x.X = 0;
		SetActorRotation(x);

		GrabbedObject->GetRootComponent()->SetWorldLocationAndRotation
		(
			FMath::VInterpTo
			(
				GrabbedObject->GetActorLocation(),
				GetWorld()->GetFirstPlayerController()->PlayerCameraManager->GetActorForwardVector() * GrabSocket + GetActorLocation(),
				DeltaTime,
				5.f
			),
			FMath::RInterpTo
			(
				GrabbedObject->GetActorRotation(),
				GetActorRotation(),
				DeltaTime,
				5.f
			),
			true
		);
	}

	InteractRaycast();
}

void AMegajamCharacter::MoveForward(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AMegajamCharacter::MoveRight(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}

void AMegajamCharacter::Dash()
{
	if (!IsDashed && (Controller != nullptr))
	{
		FindComponentByClass<UMeshComponent>()->SetVisibility(false);
		LaunchCharacter(GetActorForwardVector() * DashForce, true, true);
		DashStartTime = 0;
		IsDashed = true;
	}
}

void AMegajamCharacter::Grab()
{
	FHitResult hit;
	FVector forward = GetWorld()->GetFirstPlayerController()->PlayerCameraManager->GetActorForwardVector();
	FVector start = GetWorld()->GetFirstPlayerController()->PlayerCameraManager->GetTransform().GetLocation();
	FVector end = forward * 2000.f + start;
	FCollisionQueryParams* col = new FCollisionQueryParams();
	col->AddIgnoredActor(this);

	if (GetWorld()->LineTraceSingleByChannel(hit, start, end, ECC_WorldDynamic, *col))
	{
		if (hit.GetActor()->IsRootComponentMovable())
		{
			GrabbedObject = hit.GetActor();
			GrabbedObject->FindComponentByClass<UStaticMeshComponent>()->SetSimulatePhysics(false);
		}
	}
}

void AMegajamCharacter::GrabEnd()
{
	if (GrabbedObject)
	{
		GrabbedObject->FindComponentByClass<UStaticMeshComponent>()->SetSimulatePhysics(true);
		GrabbedObject = nullptr;
	}
}

void AMegajamCharacter::AdjustDistanceGrabbedObject(float value)
{
	GrabSocket += 30 * value;
}

void AMegajamCharacter::InteractRaycast()
{
	FHitResult hit;
	FVector forward = GetWorld()->GetFirstPlayerController()->PlayerCameraManager->GetActorForwardVector();
	FVector start = GetWorld()->GetFirstPlayerController()->PlayerCameraManager->GetTransform().GetLocation();
	FVector end = forward * 500.f + start;
	FCollisionQueryParams* col = new FCollisionQueryParams();
	col->AddIgnoredActor(this);

	bInteractObject = GetWorld()->LineTraceSingleByChannel(hit, start, end, ECC_Visibility, *col);
	
	if (bInteractObject)
	{
		InteractableObj = Cast<AInteractable>(hit.GetActor());
		// UI Press button
	}
}

void AMegajamCharacter::Interact()
{
	if (bInteractObject)
	{
		ACrystal* Crystal = Cast<ACrystal>(InteractableObj);

		if (Crystal)
		{
			Crystal->Interact();
		}

		else
		{
			AChest* Chest = Cast<AChest>(InteractableObj);

			if (Chest)
			{
				Chest->Interact();
			}

			else
			{
				ADoor* Door = Cast<ADoor>(InteractableObj);

				if (Door)
				{
					Door->Interact();
				}

				else
				{
					ACrystalPlace* CrystalPlace = Cast<ACrystalPlace>(InteractableObj);

					if (CrystalPlace)
					{
						CrystalPlace->Interact();
					}

					else
					{
						AShrine* Shrine = Cast<AShrine>(InteractableObj);

						if (Shrine)
						{
							Shrine->Interact();
						}
					}
				}
			}
		}
	}
}