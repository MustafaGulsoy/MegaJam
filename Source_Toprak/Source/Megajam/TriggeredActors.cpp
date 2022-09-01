// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggeredActors.h"

ATriggeredActors::ATriggeredActors()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ATriggeredActors::BeginPlay()
{
	Super::BeginPlay();
	
	BoxTrigger = FindComponentByClass<UBoxComponent>();
	if (BoxTrigger)
	{
		UE_LOG(LogTemp, Warning, TEXT("Hello"));
		BoxTrigger->OnComponentBeginOverlap.AddDynamic(this, &ATriggeredActors::OnOverlapBegin);
	}
}

void ATriggeredActors::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATriggeredActors::OnOverlapBegin
(
	UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult
){
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
		UE_LOG(LogTemp, Warning, TEXT("%s"), *OtherActor->GetName());
}