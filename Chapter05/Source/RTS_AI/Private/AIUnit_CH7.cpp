#include "AIUnit_CH7.h"

#include "RTS_AI/Public/HealthComponent.h"

AAIUnit_CH7::AAIUnit_CH7()
{
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health"));
}

void AAIUnit_CH7::Init()
{
	HealthComponent->OnHealthDead.AddDynamic(this, &AAIUnit_CH7::HandleHealthDeath);
}

void AAIUnit_CH7::HandleHealthDeath(AController* Causer)
{
	OnUnitDeath.Broadcast(Causer, PointValue);
	Destroy();
}
