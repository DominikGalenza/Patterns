#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AIController_CH7.generated.h"

class AAIUnit_CH7;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FControllerDeathSignature, AController*, Causer, int, Points);
UCLASS(Abstract)
class RTS_AI_API AAIController_CH7 : public AAIController
{
	GENERATED_BODY()

public:
	void Init();

	UPROPERTY(BlueprintAssignable)
	FControllerDeathSignature OnControllerDeath;

protected:
	UFUNCTION()
	void HandleUnitDeath(AController* Causer, int Points);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<AAIUnit_CH7> Unit;
};
