#include "Interactable.h"
#include "MegajamCharacter.h"

void AInteractable::Interact()
{

}

void ACrystal::Interact()
{
	AMegajamCharacter::IncreaseCrystalNum(this);
	FindComponentByClass<UMeshComponent>()->SetVisibility(false);
}

void AChest::Interact()
{
	return;
}

void ADoor::Interact()
{
	return;
}

void ACrystalPlace::Interact()
{
	return;
}

void AShrine::Interact()
{
	return;
}
