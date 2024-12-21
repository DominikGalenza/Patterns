#include "AIController_CH7.h"

#include "AIUnit_CH7.h"

void AAIController_CH7::Init()
{
	if (APawn* AIPawn = GetPawn())
	{
		if (Unit = Cast<AAIUnit_CH7>(AIPawn))
		{
			Unit->Init();
			Unit->OnUnitDeath.AddDynamic(this, &AAIController_CH7::HandleUnitDeath);
		}
	}
}

void AAIController_CH7::HandleUnitDeath(AController* Causer, int Points)
{
	OnControllerDeath.Broadcast(Causer, Points);
}
