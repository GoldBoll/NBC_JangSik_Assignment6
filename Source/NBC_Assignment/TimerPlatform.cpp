#include "TimerPlatform.h"

ATimerPlatform::ATimerPlatform()
{
	// MeshComponent와 Plane 메시는 ABasePlatformActor에서 처리
	ActiveDuration   = 3.f;
	InactiveDuration = 2.f;
}

void ATimerPlatform::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer(
		ActiveTimerHandle,
		this,
		&ATimerPlatform::DeactivatePlatform,
		ActiveDuration,
		false
	);
}

void ATimerPlatform::DeactivatePlatform()
{
	SetActorHiddenInGame(true);
	SetActorEnableCollision(false);

	GetWorld()->GetTimerManager().SetTimer(
		InactiveTimerHandle,
		this,
		&ATimerPlatform::ActivatePlatform,
		InactiveDuration,
		false
	);
}

void ATimerPlatform::ActivatePlatform()
{
	SetActorHiddenInGame(false);
	SetActorEnableCollision(true);

	GetWorld()->GetTimerManager().SetTimer(
		ActiveTimerHandle,
		this,
		&ATimerPlatform::DeactivatePlatform,
		ActiveDuration,
		false
	);
}
