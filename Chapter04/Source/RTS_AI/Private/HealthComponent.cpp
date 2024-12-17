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

	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::DamageTaken);
	CurrentHealth = MaxHealth;
}

void UHealthComponent::DamageTaken(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* Instigator, AActor* Causer)
{
	CurrentHealth = FMath::Max(CurrentHealth - Damage, 0.f);
	OnComponentDamaged.Broadcast(Instigator, Damage, CurrentHealth);
	if (CurrentHealth <= 0.f)
	{
		OnComponentDead.Broadcast(Instigator);
	}
}
