#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactable.generated.h"

UCLASS()
class MEGAJAM_API AInteractable : public AActor
{
	GENERATED_BODY()
	
public:	

	virtual void Interact();
};

UCLASS()
class ACrystal : public AInteractable
{
	GENERATED_BODY()

public:

	void Interact();
};

UCLASS()
class AChest : public AInteractable
{
	GENERATED_BODY()

public:

	void Interact();
};

UCLASS()
class ADoor : public AInteractable
{
	GENERATED_BODY()

public:

	void Interact();
};

UCLASS()
class ACrystalPlace : public AInteractable
{
	GENERATED_BODY()

public:

	void Interact();
};

UCLASS()
class AShrine : public AInteractable
{
	GENERATED_BODY()

public:

	void Interact();
};