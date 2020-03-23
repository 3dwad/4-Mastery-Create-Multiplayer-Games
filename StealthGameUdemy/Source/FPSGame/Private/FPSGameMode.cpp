// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "FPSGameMode.h"
#include "FPSHUD.h"
#include "FPSCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet//GameplayStatics.h"

AFPSGameMode::AFPSGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Blueprints/BP_Player"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AFPSHUD::StaticClass();
}

void AFPSGameMode::CompleteMission(APawn* InstigatorPawn, bool bIsSucces)
{

	if (InstigatorPawn)
	{
		InstigatorPawn->DisableInput(nullptr);

		if (SpectatingViewPoint)
		{

			//	Local variable on Actor object reference
			AActor* NewViewTarget;

			//	Get first actor of class
			NewViewTarget = UGameplayStatics::GetActorOfClass(this, SpectatingViewPoint);

			//	Cast controller from instigator pawn to APlayerController
			APlayerController* PC = Cast<APlayerController>(InstigatorPawn->GetController());
			if (PC)
			{
				PC->SetViewTargetWithBlend(NewViewTarget, 0.5f, EViewTargetBlendFunction::VTBlend_Cubic);
			}
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Spectating class is nullptr"));
		}
	}

	OnMissionCompleted(InstigatorPawn,bIsSucces);		
}
