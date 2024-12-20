#include "GuardTower_CH5_1.h"

#include "Components/ArrowComponent.h"
#include "Components/SpotLightComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/KismetSystemLibrary.h"

AGuardTower_CH5_1::AGuardTower_CH5_1()
{
	PrimaryActorTick.bCanEverTick = true;
	RotateForward = true;
	EnemySpotted = false;
	DetectionRange = 4000.f;
	DetectionRadius = 250.f;

	TowerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TowerMesh"));
	RootComponent = TowerMesh;
	
	LightPivot = CreateDefaultSubobject<USceneComponent>(TEXT("LightPivot"));
	LightPivot->SetupAttachment(TowerMesh);
	
	LightMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LightMesh"));
	LightMesh->SetupAttachment(LightPivot);
	
	SpotLight = CreateDefaultSubobject<USpotLightComponent>(TEXT("SpotLight"));
	SpotLight->SetupAttachment(LightMesh);
	
	Arrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
	Arrow->SetupAttachment(LightMesh);

	TRotateLight = CreateDefaultSubobject<UTimelineComponent>(TEXT("TRotateLight"));
	OnTimelineUpdate.BindUFunction(this, FName("HandleRotateLightUpdate"));
	OnTimelineFinished.BindUFunction(this, FName("HandleRotateLightFinished"));

	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	Sphere->SetupAttachment(LightMesh);
	Sphere->OnComponentBeginOverlap.AddDynamic(this, &AGuardTower_CH5_1::OnSphereOverlapBegin);
	Sphere->OnComponentEndOverlap.AddDynamic(this, &AGuardTower_CH5_1::OnSphereOverlapEnd);
}

void AGuardTower_CH5_1::BeginPlay()
{
	Super::BeginPlay();

	if (Curve == nullptr)
	{
		return;
	}

	TRotateLight->AddInterpFloat(Curve, OnTimelineUpdate, FName("Alpha"));
	TRotateLight->SetTimelineFinishedFunc(OnTimelineFinished);
	TRotateLight->SetLooping(false);
	TRotateLight->SetIgnoreTimeDilation(true);

	StartRotation();
}

void AGuardTower_CH5_1::HandleRotateLightUpdate(float value)
{
	LightPivot->SetRelativeRotation(FRotator(0.f, FMath::Lerp(-40.f, 40.f, value), 0.f));
}

void AGuardTower_CH5_1::HandleRotateLightFinished()
{
	RotateForward = !RotateForward;
	StartRotation();
}

void AGuardTower_CH5_1::StartRotation()
{
	if (RotateForward)
	{
		TRotateLight->Play();
	}
	else
	{
		TRotateLight->Reverse();
	}
}

void AGuardTower_CH5_1::StopRotation()
{
	TRotateLight->Stop();
}

void AGuardTower_CH5_1::OnSphereOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool FromSweep, const FHitResult& SweepResult)
{
	if (EnemyUnit != nullptr)
	{
		return;
	}

	EnemyUnit = Cast<ACharacter>(OtherActor);

	if (EnemyUnit == nullptr)
	{
		return;
	}

	FHitResult hit(ForceInit);
	FVector start = Arrow->GetComponentLocation();
	FVector end = EnemyUnit->GetActorLocation();

	if (UKismetSystemLibrary::LineTraceSingle(GetWorld(), start, end, UEngineTypes::ConvertToTraceType(ECC_Visibility),
		false, { EnemyUnit }, EDrawDebugTrace::ForDuration, hit, true, FLinearColor::Red, FLinearColor::Green, 0.5f))
	{
		return;
	}

	EnemySpotted = true;
	StopRotation();
}

void AGuardTower_CH5_1::OnSphereOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (EnemyUnit != OtherActor)
	{
		return;
	}

	EnemySpotted = false;
	EnemyUnit = nullptr;
	StartRotation();
}

