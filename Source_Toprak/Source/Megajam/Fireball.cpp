// Fill out your copyright notice in the Description page of Project Settings.


#include "Fireball.h"

AFireball::AFireball()
{
	PrimaryActorTick.bCanEverTick = true;
	IsAttacking = false;
	IsMovingToSocketComplete = true;
}

void AFireball::BeginPlay()
{
	Super::BeginPlay();

	TArray<USpringArmComponent*> SpringArms;
	GetParentActor()->GetComponents<USpringArmComponent>(SpringArms);
	DefaultSocket = SpringArms[1];

	CurrentSocket = DefaultSocket;
	MeshSphere = FindComponentByClass<UStaticMeshComponent>();
}

void AFireball::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}