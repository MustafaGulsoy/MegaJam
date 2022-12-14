// Copyright Epic Games, Inc. All Rights Reserved.

#include "MegaJamCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"

//////////////////////////////////////////////////////////////////////////
// AMegaJamCharacter

AMegaJamCharacter::AMegaJamCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rate for input
	TurnRateGamepad = 50.f;


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

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)
}

// Called every frame
void AMegaJamCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (grabbedObject == nullptr)
	{

	}
	else
	{
		//staticMesh->AddForce(FVector(1, 2, 3));
		//
		//
		
		staticMesh->SetWorldLocation(FMath::VInterpTo
		(
			grabbedObject->GetActorLocation(),
			GetWorld()->GetFirstPlayerController()->PlayerCameraManager->GetCameraLocation() +
			GetWorld()->GetFirstPlayerController()->PlayerCameraManager->GetActorForwardVector() * grabDistance +FVector(0,0,100),
			DeltaTime,
			3.f
		));
		UE_LOG(LogTemp, Display, TEXT("%s"), *((GetActorLocation() - GetWorld()->GetFirstPlayerController()->PlayerCameraManager->GetCameraLocation()) * -2 +
			GetActorLocation()).ToString());
	
	
	
	}

}

//////////////////////////////////////////////////////////////////////////
// Input

void AMegaJamCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAction("Grab", IE_Pressed, this, &AMegaJamCharacter::Grab);


	PlayerInputComponent->BindAxis("Move Forward / Backward", this, &AMegaJamCharacter::MoveForward);
	PlayerInputComponent->BindAxis("Move Right / Left", this, &AMegaJamCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn Right / Left Mouse", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("Turn Right / Left Gamepad", this, &AMegaJamCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("Look Up / Down Mouse", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("Look Up / Down Gamepad", this, &AMegaJamCharacter::LookUpAtRate);

	PlayerInputComponent->BindAxis("Grab Distance", this, &AMegaJamCharacter::SetGrabDistance);

	// handle touch devices
	PlayerInputComponent->BindTouch(IE_Pressed, this, &AMegaJamCharacter::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &AMegaJamCharacter::TouchStopped);
}

void AMegaJamCharacter::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
	Jump();
}

void AMegaJamCharacter::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
	StopJumping();
}

void AMegaJamCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * TurnRateGamepad * GetWorld()->GetDeltaSeconds());
}

void AMegaJamCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * TurnRateGamepad * GetWorld()->GetDeltaSeconds());
}

void AMegaJamCharacter::MoveForward(float Value)
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

void AMegaJamCharacter::MoveRight(float Value)
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


void AMegaJamCharacter::Grab()
{

	if (grabbedObject == nullptr)
	{
		AMegaJamCharacter::GrabItem();
	}
	else
	{
		AMegaJamCharacter::ReleaseItem();

	}
}

void AMegaJamCharacter::GrabItem() {

	UE_LOG(LogTemp, Display, TEXT("Anything can happen"));

	if (grabbedObject == nullptr)
	{
		FHitResult hit;
		FVector ForwardVector = GetWorld()->GetFirstPlayerController()->PlayerCameraManager->GetActorForwardVector();
		FVector start = GetWorld()->GetFirstPlayerController()->PlayerCameraManager->GetTransform().GetLocation() + FVector(0, 0, 80);
		FVector end = ((ForwardVector * 1000.f) + start);
		DrawDebugLine(GetWorld(), start, end, FColor::Green, false, 10, 0, 1);

		FCollisionQueryParams collisionParams;

		isHit = GetWorld()->LineTraceSingleByChannel(hit, start, end, ECC_Visibility, collisionParams);

		if (isHit)
		{
			if (hit.GetActor() != GetOwner())
			{
				grabbedObject = hit.GetActor();
				UE_LOG(LogTemp, Display, TEXT("%s"), *grabbedObject->GetName());
				staticMesh = Cast<UStaticMeshComponent>(hit.GetActor()->GetRootComponent());
				staticMesh->SetEnableGravity(false);
			}
		}
	}
}
void AMegaJamCharacter::ReleaseItem()
{
	staticMesh->SetEnableGravity(true);
	grabbedObject = nullptr;
	staticMesh = nullptr;

	UE_LOG(LogTemp, Display, TEXT("Birakti"));

}


void AMegaJamCharacter::SetGrabDistance(float value) 
{
	grabDistance += value;

}