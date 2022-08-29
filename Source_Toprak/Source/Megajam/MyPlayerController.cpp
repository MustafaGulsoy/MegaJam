// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"

AMyPlayerController::AMyPlayerController()
{

}

void AMyPlayerController::BeginPlay()
{
	Super::BeginPlay();

	possessedPawn = Cast<AMegajamCharacter>(GetPawn());
	
	TArray<AActor*> ChildActors;
	possessedPawn->GetAttachedActors(ChildActors);
	FireballActor = Cast<AFireballActor>(ChildActors[0]);
	IceballActor = Cast<AFireballActor>(ChildActors[1]);
}

void AMyPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("Jump", IE_Pressed, this, &AMyPlayerController::CallJump);
	InputComponent->BindAction("Jump", IE_Released, this, &AMyPlayerController::CallStopJumping);
	InputComponent->BindAction("FireballFire", IE_Pressed, this, &AMyPlayerController::CallFireballFire);
	InputComponent->BindAction("IceballFire", IE_Pressed, this, &AMyPlayerController::CallIceballFire);
	InputComponent->BindAction("Dash", IE_Pressed, this, &AMyPlayerController::CallDash);
	InputComponent->BindAction("HitTheGround", IE_Pressed, this, &AMyPlayerController::CallHitTheGround);

	InputComponent->BindAxis("Move Forward / Backward", this, &AMyPlayerController::CallMoveForward);
	InputComponent->BindAxis("Move Right / Left", this, &AMyPlayerController::CallMoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	InputComponent->BindAxis("Turn Right / Left Mouse", this, &AMyPlayerController::CallAddControllerYawInput);
	InputComponent->BindAxis("Look Up / Down Mouse", this, &AMyPlayerController::CallAddControllerPitchInput);
	
}

void AMyPlayerController::Tick(float DeltaTime)
{
	if (!possessedPawn)
	{
		possessedPawn = Cast<AMegajamCharacter>(GetPawn());

	}
}

void AMyPlayerController::CallMoveForward(float value)
{
	if (possessedPawn)
	{
		possessedPawn->MoveForward(value);
	}
}

void AMyPlayerController::CallMoveRight(float value)
{
	if (possessedPawn)
	{
		possessedPawn->MoveRight(value);
	}
}

void AMyPlayerController::CallJump()
{
	if (possessedPawn)
	{
		possessedPawn->Jump();
	}
}

void AMyPlayerController::CallStopJumping()
{
	if (possessedPawn)
	{
		possessedPawn->StopJumping();
	}
}

void AMyPlayerController::CallAddControllerYawInput(float rate)
{
	if (possessedPawn)
	{
		possessedPawn->AddControllerYawInput(rate);
	}
}

void AMyPlayerController::CallAddControllerPitchInput(float rate)
{
	if (possessedPawn)
	{
		possessedPawn->AddControllerPitchInput(rate);
	}
}

void AMyPlayerController::CallFireballFire()
{
	if (FireballActor)
	{
		FireballActor->Fire();
	}
}

void AMyPlayerController::CallIceballFire()
{
	if (IceballActor)
	{
		IceballActor->Fire();
	}
}

void AMyPlayerController::CallDash()
{
	if (possessedPawn)
	{
		possessedPawn->Dash();
	}
}


void AMyPlayerController::CallHitTheGround()
{
	if (IceballActor && FireballActor)
	{
		IceballActor->HitTheGround();
		FireballActor->HitTheGround();
	}
}
