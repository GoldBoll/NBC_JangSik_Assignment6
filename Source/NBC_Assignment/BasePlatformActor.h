#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BasePlatformActor.generated.h"

UENUM(BlueprintType)
enum class EMoveAxis : uint8
{
	X UMETA(DisplayName = "X (앞뒤)"),
	Y UMETA(DisplayName = "Y (좌우)"),
	Z UMETA(DisplayName = "Z (상하)")
};

UCLASS()
class NBC_ASSIGNMENT_API ABasePlatformActor : public AActor
{
	GENERATED_BODY()

public:
	ABasePlatformActor();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* MeshComponent;

public:
	// 회전 설정
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform|Rotation")
	bool bIs_Rotate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform|Rotation",
		meta = (EditCondition = "bIs_Rotate", ClampMin = "-720", ClampMax = "720"))
	float RotationSpeed; // deg/s

	// 이동 설정
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform|Movement")
	bool bIs_Move;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform|Movement",
		meta = (EditCondition = "bIs_Move"))
	EMoveAxis MoveAxis;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform|Movement",
		meta = (EditCondition = "bIs_Move", ClampMin = "0"))
	float MoveSpeed; // cm/s

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform|Movement",
		meta = (EditCondition = "bIs_Move", ClampMin = "0"))
	float MaxRange; // cm

private:
	FVector StartLocation;
	float CurrentOffset;
	float MoveDir; // 1.f or -1.f
};
