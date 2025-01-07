#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "ControllableUnit.h"
#include "GameFramework/Character.h"
#include "Command.h"
#include "EliteUnit.generated.h"

class AWeapon_Base;

UCLASS(Abstract)
class RTS_AI_API AEliteUnit : public ACharacter, public IControllableUnit
{
	GENERATED_BODY()

public:
	AEliteUnit();
	
	UFUNCTION(BlueprintCallable)
	void Init(UBlackboardComponent* inBlackboard);
	
	virtual void StopMoving_Implementation() override;
	virtual void SetMoveLocation_Implementation(FVector targetLocation) override;
	virtual void QueueMoveLocation_Implementation(FVector targetLocation) override;
	virtual void AttackTarget_Implementation(UObject* target) override;
	virtual void MoveLocationReached_Implementation() override;

protected:
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<AAIController> AIController;
	UPROPERTY(VisibleInstanceOnly)
	TObjectPtr<UBlackboardComponent> Blackboard;
	UPROPERTY(VisibleInstanceOnly)
	bool bIsMoving;

	TQueue<TObjectPtr<UCommand>> CommandQueue;
};
