// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "FPSGameMode.generated.h"

UCLASS()
class AFPSGameMode : public AGameModeBase
{
	GENERATED_BODY()

protected:

	//	Variable with Actor class reference
	UPROPERTY(EditDefaultsOnly,Category = "Spectating")
	TSubclassOf<AActor> SpectatingViewPoint;

public:

	AFPSGameMode();


	UFUNCTION()
	void CompleteMission(APawn* InstigatorPawn, bool IsSucces);

	UFUNCTION(BlueprintImplementableEvent,Category = "GameMode")
	void OnMissionCompleted(APawn* InstigatorPawn, bool IsSucces);

};



