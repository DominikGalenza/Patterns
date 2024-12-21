#include "GameMode_CH7.h"

#include "AIController_CH7.h"
#include "PlayerController_Ch7.h"
#include "Kismet/GameplayStatics.h"

void AGameMode_CH7::PostLogin(APlayerController* NewPlayer)
{
	if (APlayerController_Ch7* CastedPlayerController = Cast<APlayerController_Ch7>(NewPlayer))
	{
		PlayerController = CastedPlayerController;
		PlayerController->Init();
	}

	Super::PostLogin(NewPlayer);
}

void AGameMode_CH7::Logout(AController* Exiting)
{
	if (Exiting == PlayerController)
	{
		PlayerController = nullptr;
	}

	Super::Logout(Exiting);
}

void AGameMode_CH7::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> Actors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AAIController::StaticClass(), Actors);

	for (AActor* Actor : Actors)
	{
		AIControllers.Add(Cast<AAIController_CH7>(Actor));
	}

	for (AAIController_CH7* AI : AIControllers)
	{
		AI->Init();
		AI->OnControllerDeath.AddDynamic(this, &AGameMode_CH7::HandleControllerDeath);
	}
}

void AGameMode_CH7::HandleControllerDeath(AController* Causer, int Points)
{
	PlayerController->AddPoints(Points);
}
