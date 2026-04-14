#include "BasePlatformActor.h"

ABasePlatformActor::ABasePlatformActor()
{
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	RootComponent = MeshComponent;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> PlaneMesh(TEXT("/Engine/BasicShapes/Plane.Plane"));
	if (PlaneMesh.Succeeded())
	{
		MeshComponent->SetStaticMesh(PlaneMesh.Object);
		MeshComponent->SetRelativeScale3D(FVector(2.f, 2.f, 1.f)); // 200x200cm
	}

	// 회전 기본값
	bIs_Rotate = false;
	RotationSpeed = 90.f;

	// 이동 기본값
	bIs_Move = false;
	MoveAxis = EMoveAxis::X;
	MoveSpeed = 200.f;
	MaxRange = 300.f;

	CurrentOffset = 0.f;
	MoveDir = 1.f;
}

void ABasePlatformActor::BeginPlay()
{
	Super::BeginPlay();
	StartLocation = GetActorLocation();
}

void ABasePlatformActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// 회전
	if (bIs_Rotate)
	{
		AddActorLocalRotation(FRotator(0.f, RotationSpeed * DeltaTime, 0.f));
	}

	// 이동 (왕복)
	if (bIs_Move)
	{
		CurrentOffset += MoveDir * MoveSpeed * DeltaTime;

		// 범위 끝에 도달하면 방향 반전
		if (FMath::Abs(CurrentOffset) >= MaxRange)
		{
			MoveDir *= -1.f;
			CurrentOffset = FMath::Sign(CurrentOffset) * MaxRange;
		}

		FVector NewLocation = StartLocation;
		switch (MoveAxis)
		{
		case EMoveAxis::X: NewLocation.X += CurrentOffset; break;
		case EMoveAxis::Y: NewLocation.Y += CurrentOffset; break;
		case EMoveAxis::Z: NewLocation.Z += CurrentOffset; break;
		}
		SetActorLocation(NewLocation);
	}
}
