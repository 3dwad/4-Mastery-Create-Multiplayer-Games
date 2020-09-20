// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSAIGuard.h"
#include "FPSHelper.h"
#include "FPSGameMode.h"

#include "Perception/PawnSensingComponent.h"
#include "DrawDebugHelpers.h"
#include "TimerManager.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "Engine/Engine.h"
#include "Net/UnrealNetwork.h"


// Sets default values
AFPSAIGuard::AFPSAIGuard()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComp"));

	GuardState = EAIState::Idle;

	PawnSensingComp->OnSeePawn.AddDynamic(this, &AFPSAIGuard::OnPawnSeen);
	PawnSensingComp->OnHearNoise.AddDynamic(this, &AFPSAIGuard::OnPawnHeard);
}

// Called when the game starts or when spawned
void AFPSAIGuard::BeginPlay()
{
	Super::BeginPlay();

	//	Remember rotation at start
	InitilizeRotation = GetActorRotation();

	if (bIsNeedPatrol)
	{
		GoToNextPoint();
	}
}

// Called every frame
void AFPSAIGuard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (TargetPatrolPoint)
	{

		//	Every frame check distance between guard and target point. When guard close to point
		float Distance = UKismetMathLibrary::Vector_Distance(GetActorLocation(), TargetPatrolPoint->GetActorLocation());

		GEngine->AddOnScreenDebugMessage(1, 0.f, FColor::Red, FString::SanitizeFloat(Distance));

		if (Distance < 70.f)
		{
			GoToNextPoint();

			GEngine->AddOnScreenDebugMessage(2, 2.f, FColor::Red, "Go To Next Point is called");
			
		}

				
	}
}

void AFPSAIGuard::OnPawnSeen(APawn* Pawn)
{

	if (!Pawn)
	{
		return;
	}

	GetController()->StopMovement();

	DrawDebugSphere(GetWorld(), Pawn->GetActorLocation(), 30.f, 8.f, FColor::Red, false,2.f);
	AFPSGameMode* L_GM = Cast<AFPSGameMode>(GetWorld()->GetAuthGameMode());
	if (L_GM)
	{
		//	Mission field
		L_GM->CompleteMission(Pawn, false);
	}
	//	new guard state
	SetGuardState(EAIState::Alerted);
}

void AFPSAIGuard::OnPawnHeard(APawn* NoiseInstigator, const FVector& Location, float Volume)
{
	//	Stop function if guard state is alerted
	if (GuardState == EAIState::Alerted)
	{
		return;
	}
		
	//	Debug
	DrawDebugSphere(GetWorld(), Location, 30.f, 8.f, FColor::Green, false, 2.f);

	GetController()->StopMovement();

	//	Equal FindLookAtRotation
	FVector Direction = Location - GetActorLocation();
	Direction.Normalize();

	FRotator NewLookAt = FRotationMatrix::MakeFromX(Direction).Rotator();	
	NewLookAt.Pitch = 0.f;
	NewLookAt.Roll = 0.f;
	SetActorRotation(NewLookAt);

	//	New guard state	
	SetGuardState(EAIState::Suspicious);
	
	//	Create timer. Clear previous if already exist
	GetWorldTimerManager().ClearTimer(TimerHandle_ResetOrientation);
	GetWorldTimerManager().SetTimer(TimerHandle_ResetOrientation, this, &AFPSAIGuard::ResetOrierntation, 5.f);	

}

void AFPSAIGuard::ResetOrierntation()
{
	//	Stop function if guard state is alerted
	if (GuardState == EAIState::Alerted)
	{
		return;
	}

	if (bIsNeedPatrol)
	{
		GoToNextPoint();
	}
	SetActorRotation(InitilizeRotation);

	//	New guard state
	SetGuardState(EAIState::Idle);
}

void AFPSAIGuard::SetGuardState(EAIState NewState)
{
	if (NewState != GuardState)
	{
		GuardState = NewState;

		if (HasAuthority())
		{
			OnRep_GuardState();
		}
	}
}

void AFPSAIGuard::GoToNextPoint()
{
	if (TargetPatrolPoint == nullptr || TargetPatrolPoint == FirstPatrolPont)
	{
		TargetPatrolPoint = SecondPatrolPont;
	}
	else
	{
		TargetPatrolPoint = FirstPatrolPont;
	}

	UAIBlueprintHelperLibrary::SimpleMoveToActor(GetController(), TargetPatrolPoint);
}

void AFPSAIGuard::OnRep_GuardState()
{
	FFPSHelper::PrintToLogEverywhere(this,"OnRep_GuardState()");
	OnStateChanged(GuardState);
}

void AFPSAIGuard::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AFPSAIGuard, GuardState);
}






