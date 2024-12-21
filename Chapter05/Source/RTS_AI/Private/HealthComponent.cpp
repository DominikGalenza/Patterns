// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	MaxHealth = 100.f;
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	CurrentHealth = MaxHealth;
	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::DamageTaken);
}

void UHealthComponent::DamageTaken(AActor* DamagedActor, float damage, const UDamageType* DamageType, AController* Instigator, AActor* Causer)
{
	float Change = FMath::Min(damage, CurrentHealth);
	CurrentHealth -= Change;
	OnHealthDamaged.Broadcast(CurrentHealth, MaxHealth, Change);
	if (CurrentHealth == 0.f)
	{
		OnHealthDead.Broadcast(Instigator);
	}
}
