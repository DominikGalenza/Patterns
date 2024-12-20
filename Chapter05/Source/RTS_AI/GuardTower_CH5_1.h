#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "Components/TimelineComponent.h"
#include "GuardTower_CH5_1.generated.h"

class UArrowComponent;
class USpotLightComponent;
UCLASS()
class RTS_AI_API AGuardTower_CH5_1 : public AActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess = true))
	TObjectPtr<UStaticMeshComponent> TowerMesh;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess = true))
	TObjectPtr<USceneComponent> LightPivot;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess = true))
	TObjectPtr<UStaticMeshComponent> LightMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess = true))
	TObjectPtr<USpotLightComponent> SpotLight;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess = true))
	TObjectPtr<UArrowComponent> Arrow;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	TObjectPtr<USphereComponent> Sphere;

	FOnTimelineFloat OnTimelineUpdate;
	FOnTimelineEventStatic OnTimelineFinished;

	UFUNCTION()
	void HandleRotateLightUpdate(float value);

	UFUNCTION()
	void HandleRotateLightFinished();

	void StartRotation();
	void StopRotation();

public:	
	// Sets default values for this actor's properties
	AGuardTower_CH5_1();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool RotateForward;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool EnemySpotted;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DetectionRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DetectionRadius;

	UPROPERTY()
	TObjectPtr<UTimelineComponent> TRotateLight;

	UPROPERTY(EditAnywhere)
	UCurveFloat* Curve;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<ACharacter> EnemyUnit;

	UFUNCTION()
	void OnSphereOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool FromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnSphereOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
