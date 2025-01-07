// Fill out your copyright notice in the Description page of Project Settings.


#include "CommandUnitMove.h"
#include "ControllableUnit.h"

void UCommandUnitMove::Init(AActor* InitUnit, FVector InitMoveLocation)
{
}

void UCommandUnitMove::Execute()
{
	Super::Execute();
	IControllableUnit::Execute_SetMoveLocation(Unit, MoveLocation);
}
