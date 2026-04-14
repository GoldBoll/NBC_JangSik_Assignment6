#include "RandomSpawner.h"
#include "RotatingPlatform.h"
#include "MovingPlatform.h"
#include "TimerPlatform.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"

ARandomSpawner::ARandomSpawner()
{
	PrimaryActorTick.bCanEverTick = true;

	SpawnCount       = 10;
	MinSpawnDistance = 300.f;
	MaxSpawnDistance = 550.f;
	HeightVariation  = 20.f;
	SpawnInterval    = 2.f;
	RemainingSpawns  = 0;

	PlatformClasses.Add(ARotatingPlatform::StaticClass());
	PlatformClasses.Add(AMovingPlatform::StaticClass());
	PlatformClasses.Add(ATimerPlatform::StaticClass());

	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, TEXT("[RandomSpawner] 생성자 호출됨"));
}

void ARandomSpawner::BeginPlay()
{
	Super::BeginPlay();

	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan,
			FString::Printf(TEXT("[RandomSpawner] BeginPlay 호출됨 — PlatformClasses 수: %d"), PlatformClasses.Num()));

	LastSpawnedLocation = GetActorLocation();
	LastSpawnedLocation.Z -= 90;
	
	ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(this, 0);
	if (PlayerCharacter)
	{
		LastSpawnedLocation = PlayerCharacter->GetActorLocation();
		LastSpawnedLocation.Z -= 90;
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan,
				FString::Printf(TEXT("[RandomSpawner] 플레이어 위치 감지: %s"), *LastSpawnedLocation.ToString()));
	}
	else
	{
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow,
				FString::Printf(TEXT("[RandomSpawner] 플레이어를 찾지 못함 — Spawner 위치(%s) 기준으로 스폰"), *LastSpawnedLocation.ToString()));
	}

	StartSpawnTimer(SpawnCount);
}

void ARandomSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ARandomSpawner::StartSpawnTimer(int32 Count)
{
	if (PlatformClasses.Num() == 0)
	{
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("[RandomSpawner] PlatformClasses가 비어있습니다."));
		return;
	}

	RemainingSpawns = Count;

	// SpawnInterval 간격으로 SpawnOnePlatform 반복 호출
	GetWorld()->GetTimerManager().SetTimer(SpawnTimerHandle,this,	&ARandomSpawner::SpawnOnePlatform,SpawnInterval,	true );
}

void ARandomSpawner::SpawnOnePlatform()
{
	if (RemainingSpawns <= 0)
	{
		GetWorld()->GetTimerManager().ClearTimer(SpawnTimerHandle);
		return;
	}

	// X축 앞 방향으로 전진, Y축으로 좌우 분산
	float ForwardDist  = FMath::RandRange(MinSpawnDistance, MaxSpawnDistance);
	float LateralDist  = FMath::RandRange(-MaxSpawnDistance * 0.4f, MaxSpawnDistance * 0.4f);
	float Height       = FMath::RandRange(-HeightVariation, HeightVariation);

	FVector SpawnLocation = LastSpawnedLocation;
	SpawnLocation.X += ForwardDist;
	SpawnLocation.Y += LateralDist;
	SpawnLocation.Z += Height;

	TSubclassOf<ABasePlatformActor> SelectedClass =
		PlatformClasses[FMath::RandRange(0, PlatformClasses.Num() - 1)];

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride =
		ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	ABasePlatformActor* NewPlatform = GetWorld()->SpawnActor<ABasePlatformActor>(
		SelectedClass,
		SpawnLocation,
		FRotator::ZeroRotator,
		SpawnParams
	);

	if (NewPlatform)
	{
		NewPlatform->RotationSpeed = FMath::RandRange(30.f, 150.f);
		NewPlatform->MoveSpeed     = FMath::RandRange(100.f, 350.f);
		NewPlatform->MaxRange      = FMath::RandRange(150.f, 400.f);
		NewPlatform->MoveAxis      = static_cast<EMoveAxis>(FMath::RandRange(0, 1));

		LastSpawnedLocation = SpawnLocation;
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green,
				FString::Printf(TEXT("[RandomSpawner] 발판 스폰 성공 (잔여: %d)"), RemainingSpawns - 1));
	}
	else
	{
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red,
				FString::Printf(TEXT("[RandomSpawner] 발판 스폰 실패: %s"), *SpawnLocation.ToString()));
	}

	--RemainingSpawns;
}
