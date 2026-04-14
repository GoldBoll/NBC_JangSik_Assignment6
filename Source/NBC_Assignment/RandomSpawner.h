#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BasePlatformActor.h"
#include "RandomSpawner.generated.h"

UCLASS()
class NBC_ASSIGNMENT_API ARandomSpawner : public AActor
{
	GENERATED_BODY()

public:
	ARandomSpawner();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	void SpawnOnePlatform();			// 타이머 콜백 — 1개 스폰
	void StartSpawnTimer(int32 Count);	// Count만큼 타이머 예약

public:
	// 초기 스폰 발판 수
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner",
		meta = (ClampMin = "1", ClampMax = "50"))
	int32 SpawnCount;

	// 발판 간 최소 거리 (cm)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner",
		meta = (ClampMin = "100"))
	float MinSpawnDistance;

	// 발판 간 최대 거리 (cm) — 점프 가능 범위 내
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner",
		meta = (ClampMin = "100"))
	float MaxSpawnDistance;

	// 높이 차이 최대값 (cm)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner",
		meta = (ClampMin = "0", ClampMax = "300"))
	float HeightVariation;

	// 발판 생성 간격 (초)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner",
		meta = (ClampMin = "0.1"))
	float SpawnInterval;

	// 스폰할 플랫폼 클래스 목록
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner")
	TArray<TSubclassOf<ABasePlatformActor>> PlatformClasses;

private:
	FVector LastSpawnedLocation;
	FTimerHandle SpawnTimerHandle;
	int32 RemainingSpawns; // 타이머로 생성해야 할 잔여 개수
};
