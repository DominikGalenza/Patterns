#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PlayerController_Ch7.generated.h"

class UWidget_Score_CH7;
class ACharacter_CH7;
UCLASS(Abstract)
class RTS_AI_API APlayerController_Ch7 : public APlayerController
{
	GENERATED_BODY()

public:
	void Init();
	void AddPoints(int PointsToAdd);

protected:
	int Points;

	UPROPERTY(EditAnywhere)
	TSubclassOf<APawn> PlayerPawn;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<ACharacter_CH7> PlayerCharacter;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UWidget_Score_CH7> ScoreWidgetClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UWidget_Score_CH7> ScoreWidget;
};
