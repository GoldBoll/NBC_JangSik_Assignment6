#pragma once

#include "CoreMinimal.h"
#include "BasePlatformActor.h"
#include "TimerPlatform.generated.h"

// 도전과제: FTimerHandle을 활용한 발판 소멸/재생성 액터
UCLASS()
class NBC_ASSIGNMENT_API ATimerPlatform : public ABasePlatformActor
{
	GENERATED_BODY()

public:
	ATimerPlatform();

protected:
	virtual void BeginPlay() override;

private:
	void DeactivatePlatform();
	void ActivatePlatform();

public:
	// 발판이 보이는 시간 (초)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform|Timer",
		meta = (ClampMin = "0.1"))
	float ActiveDuration;

	// 발판이 사라져 있는 시간 (초)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform|Timer",
		meta = (ClampMin = "0.1"))
	float InactiveDuration;

private:
	FTimerHandle ActiveTimerHandle;
	FTimerHandle InactiveTimerHandle;
};
