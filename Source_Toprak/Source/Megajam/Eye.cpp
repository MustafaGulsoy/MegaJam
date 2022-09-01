// Fill out your copyright notice in the Description page of Project Settings.


#include "Eye.h"

// Sets default values
AEye::AEye()
{
	IsSocketFilled = false;
}

void AEye::BeginPlay()
{
	Super::BeginPlay();

	TArray<USpringArmComponent*> SpringArms;
	GetComponents<USpringArmComponent>(SpringArms);
	Socket = SpringArms[0];
	
}

USpringArmComponent* AEye::GetSocket()
{
	return Socket;
}

void AEye::SetBall(AFireballActor* ball)
{
	Ball = ball;
}

AFireballActor* AEye::GetBall()
{
	return Ball;
}