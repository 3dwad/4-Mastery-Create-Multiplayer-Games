// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "FPSGameMode.h"
#include "FPSHUD.h"
#include "FPSGameState.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet//GameplayStatics.h"
#include "EngineUtils.h"

AFPSGameMode::AFPSGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Blueprints/BP_Player"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom classes
	HUDClass = AFPSHUD::StaticClass();
	GameStateClass = AFPSGameState::StaticClass();
}

void AFPSGameMode::CompleteMission(APawn* InstigatorPawn, const bool InIsSuccess)
{
	if (SpectatingViewPointClass)
	{
		//	Get first actor of class
		if (AActor* NewViewTarget = UGameplayStatics::GetActorOfClass(this, SpectatingViewPointClass))
		{
			for (TActorIterator<APlayerController> PlayerControllerIt(GetWorld()); PlayerControllerIt; ++PlayerControllerIt)
			{
				auto CurrentPlayerController = *PlayerControllerIt;

				CurrentPlayerController->SetViewTargetWithBlend(NewViewTarget, 0.5f, VTBlend_Cubic);
			}
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Spectating class is nullptr"));
	}

	if (auto GameState = GetGameState<AFPSGameState>())
	{
		GameState->MulticastOnMissionCompleted(InstigatorPawn, InIsSuccess);
	}
	OnMissionCompleted(InstigatorPawn, InIsSuccess);
}
