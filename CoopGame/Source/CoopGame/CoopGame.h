// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

class FCGHelper
{
public:
    static void PrintLocalRole(AActor* InActor);
    static void PrintEverywhere(AActor* InActor, const FString InString);
};
