// Fill out your copyright notice in the Description page of Project Settings.


#include "Iceball.h"

AIceball::AIceball()
{
	PrimaryActorTick.bCanEverTick = true;
	IsAttacking = false;
	IsMovingToSocketComplete = true;
}

void AIceball::BeginPlay()
{
	Super::BeginPlay();

	TArray<USpringArmComponent*> SpringArms;
	GetParentActor()->GetComponents<USpringArmComponent>(SpringArms);
	DefaultSocket = SpringArms[2];

	CurrentSocket = DefaultSocket;
	MeshSphere = FindComponentByClass<UStaticMeshComponent>();
}

void AIceball::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}