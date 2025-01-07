// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Command.h"
#include "CommandUnitMove.generated.h"

/**
 * 
 */
UCLASS()
class RTS_AI_API UCommandUnitMove : public UCommand
{
	GENERATED_BODY()
	
public:
	void Init(AActor* InitUnit, FVector InitMoveLocation);
	virtual void Execute() override;

private:
	TObjectPtr<AActor> Unit;
	FVector MoveLocation;
};
