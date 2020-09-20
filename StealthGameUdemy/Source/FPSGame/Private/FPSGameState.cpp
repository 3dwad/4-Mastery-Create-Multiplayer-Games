// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSGameState.h"
#include "FPSPlayerController.h"

#include "EngineUtils.h"


void AFPSGameState::MulticastOnMissionCompleted_Implementation(APawn* InstigatorPawn, bool InIsSuccess)
{
    for (TActorIterator<APlayerController> PlayerControllerIt(GetWorld()); PlayerControllerIt; ++PlayerControllerIt)
    {
        auto CurrentPlayerController = Cast<AFPSPlayerController>(*PlayerControllerIt);
        if (CurrentPlayerController && CurrentPlayerController->IsLocalController())
        {
            CurrentPlayerController->OnMissionCompleted(InstigatorPawn, InIsSuccess);

            if (auto CurrentPawn = CurrentPlayerController->GetPawn())
            {
                CurrentPawn->DisableInput(CurrentPlayerController);
            }
        }
    }
}
