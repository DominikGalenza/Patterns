// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Command.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class RTS_AI_API UCommand : public UObject
{
	GENERATED_BODY()
	
public:
	virtual void Execute();
};
