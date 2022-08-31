// Fill out your copyright notice in the Description page of Project Settings.


#include "Eye.h"

// Sets default values
AEye::AEye()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	IsSocketFilled = false;
}

void AEye::BeginPlay()
{
	Super::BeginPlay();

	TArray<USpringArmComponent*> SpringArms;
	GetComponents<USpringArmComponent>(SpringArms);
	Socket = SpringArms[0];
	
}

void AEye::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

USpringArmComponent* AEye::GetSocket()
{
	return Socket;
}