#include "EliteUnit.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "CommandUnitMove.h"
#include "Kismet/KismetSystemLibrary.h"

AEliteUnit::AEliteUnit()
{
}

void AEliteUnit::Init(UBlackboardComponent* inBlackboard)
{
	bIsMoving = false;
	Blackboard = inBlackboard;
}

void AEliteUnit::StopMoving_Implementation()
{
	bIsMoving = false;
	
	Blackboard->SetValueAsBool("HasMoveLocation", false);
	Blackboard->ClearValue("MoveToLocation");
	
}

void AEliteUnit::SetMoveLocation_Implementation(FVector targetLocation)
{
	bIsMoving = true;
	
	Blackboard->SetValueAsBool("HasMoveLocation", true);
	Blackboard->SetValueAsVector("MoveToLocation", targetLocation);
}

void AEliteUnit::AttackTarget_Implementation(UObject* target)
{
	AActor* targetActor = Cast<AActor>(target);
	if(!targetActor) return;

	FHitResult traceResult(ForceInit);
	if(!UKismetSystemLibrary::LineTraceSingle(GetWorld(), GetActorLocation(), targetActor->GetActorLocation(),
		UEngineTypes::ConvertToTraceType(ECC_Visibility), false,
		{this}, EDrawDebugTrace::ForDuration, traceResult, true,
		FLinearColor::Red, FLinearColor::Green, 5)) return;

	if(traceResult.GetActor() == targetActor)
	{
		UGameplayStatics::ApplyDamage(traceResult.GetActor(), 100.0f, GetController(), this, UDamageType::StaticClass());
	}
	else
	{
		UE_LOG(LogTemp, Display, TEXT("No Line of sight"));
	}
}

void AEliteUnit::QueueMoveLocation_Implementation(FVector targetLocation)
{
	if (!bIsMoving)
	{
		AIController->GetBlackboardComponent()->SetValueAsVector("MoveToLocation", targetLocation);
		bIsMoving = true;
		return;
	}

	TObjectPtr<UCommandUnitMove> MoveCommand = NewObject<UCommandUnitMove>(this);
	MoveCommand->Init(this, targetLocation);
	CommandQueue.Enqueue(MoveCommand);
}

void AEliteUnit::MoveLocationReached_Implementation()
{
	bIsMoving = false;
	if (!CommandQueue.IsEmpty())
	{
		TObjectPtr<UCommand> Command;
		CommandQueue.Dequeue(Command);
		Command->Execute();
	}
	
	Execute_StopMoving(this);
}
