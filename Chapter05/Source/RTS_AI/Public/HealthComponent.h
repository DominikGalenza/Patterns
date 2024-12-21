// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FHealthDeadSignature, AController*, Instigator);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FHealthDamagedSignature, float, NewHealth, float, MaxHealth, float, HealthChange);
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RTS_AI_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UHealthComponent();

	UPROPERTY(BlueprintAssignable)
	FHealthDeadSignature OnHealthDead;

	UPROPERTY(BlueprintAssignable)
	FHealthDamagedSignature OnHealthDamaged;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxHealth;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float CurrentHealth;

private:
	UFUNCTION()
	void DamageTaken(AActor* DamagedActor, float damage, const UDamageType* DamageType, AController* Instigator, AActor* Causer);
};
