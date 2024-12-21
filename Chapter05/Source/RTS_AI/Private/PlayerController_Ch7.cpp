#include "PlayerController_Ch7.h"

#include "Character_CH7.h"
#include "Widget_Score_CH7.h"
#include "GameFramework/GameModeBase.h"
#include "Kismet/GameplayStatics.h"

void APlayerController_Ch7::Init()
{
	if (GetPawn() != nullptr)
	{
		GetPawn()->Destroy();
	}

	UWorld* const World = GetWorld();
	AActor* Start = UGameplayStatics::GetGameMode(World)->FindPlayerStart(this);

	FVector PawnSpawnLocation = Start != nullptr ? Start->GetActorLocation() : FVector::ZeroVector;
	FRotator PawnSpawnRotation = Start != nullptr ? Start->GetActorRotation() : FRotator::ZeroRotator;

	FActorSpawnParameters PawnSpawnParameters;
	PawnSpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	APawn* PossessedPawn = World->SpawnActor<APawn>(PlayerPawn, PawnSpawnLocation, PawnSpawnRotation, PawnSpawnParameters);
	Possess(PossessedPawn);

	if (PlayerCharacter = Cast<ACharacter_CH7>(PossessedPawn))
	{
		PlayerCharacter->Init();
	}

	ScoreWidget = CreateWidget<UWidget_Score_CH7>(this, ScoreWidgetClass.Get());
	ScoreWidget->AddToViewport();
}

void APlayerController_Ch7::AddPoints(int PointsToAdd)
{
	Points += PointsToAdd;
	ScoreWidget->UpdatePoints(Points);
}
