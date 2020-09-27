// Copyright Epic Games, Inc. All Rights Reserved.

#include "CoopGame.h"

#include "DrawDebugHelpers.h"
#include "Modules/ModuleManager.h"

IMPLEMENT_PRIMARY_GAME_MODULE( FDefaultGameModuleImpl, CoopGame, "CoopGame" );

void FCGHelper::PrintLocalRole(AActor* InActor)
{
    switch (InActor->GetLocalRole()) {
        case ROLE_None:
            DrawDebugString(InActor->GetWorld(),InActor->GetActorLocation() + FVector(0.f,0.f,50.f),"Actor: "+InActor->GetActorLabel()+". Role: None",nullptr,FColor::Black,0.f);
            break;
    case ROLE_SimulatedProxy:
        DrawDebugString(InActor->GetWorld(),InActor->GetActorLocation() + FVector(0.f,0.f,50.f),"Actor: "+InActor->GetActorLabel()+". Role: SimulatedProxy",nullptr,FColor::Black,0.f);
        break;
    case ROLE_AutonomousProxy:
        DrawDebugString(InActor->GetWorld(),InActor->GetActorLocation() + FVector(0.f,0.f,50.f),"Actor: "+InActor->GetActorLabel()+". Role: AutonomousProxy",nullptr,FColor::Black,0.f);
        break;
    case ROLE_Authority:
        DrawDebugString(InActor->GetWorld(),InActor->GetActorLocation() + FVector(0.f,0.f,50.f),"Actor: "+InActor->GetActorLabel()+". Role: Authority",nullptr,FColor::Black,0.f);
        break;
    case ROLE_MAX:
        DrawDebugString(InActor->GetWorld(),InActor->GetActorLocation() + FVector(0.f,0.f,50.f),"Actor: "+InActor->GetActorLabel()+". Role: MAX",nullptr,FColor::Black,0.f);
        break;
    default:
         DrawDebugString(InActor->GetWorld(),InActor->GetActorLocation() + FVector(0.f,0.f,50.f),"Actor: "+InActor->GetActorLabel()+". Role: default",nullptr,FColor::Black,0.f);
    }
}

void FCGHelper::PrintEverywhere(AActor* InActor, const FString InString)
{
    switch (InActor->GetLocalRole())
    {
    case ROLE_None:
        //		GEngine->AddOnScreenDebugMessage(1, 3.f, FColor::Green, "OnRep_GuardState() call on None");
        UE_LOG(LogTemp,Warning,TEXT("%s call on None"), *InString)
        break;
    case ROLE_SimulatedProxy:
        //		GEngine->AddOnScreenDebugMessage(1, 3.f, FColor::Green, "OnRep_GuardState() call on SimulatedProxy");
        UE_LOG(LogTemp,Warning,TEXT("%s call on SimulatedProxy"), *InString)
        break;
    case ROLE_AutonomousProxy:
        //		GEngine->AddOnScreenDebugMessage(1, 3.f, FColor::Green, "OnRep_GuardState() call on AutonomousProxy");
        UE_LOG(LogTemp,Warning,TEXT("%s call on AutonomousProxy"), *InString)
        break;
    case ROLE_Authority:
        //		GEngine->AddOnScreenDebugMessage(1, 3.f, FColor::Green, "OnRep_GuardState() call on Authority");
        UE_LOG(LogTemp,Warning,TEXT("%s call on Authority"), *InString)
        break;
    case ROLE_MAX:
        //		GEngine->AddOnScreenDebugMessage(1, 3.f, FColor::Green, "OnRep_GuardState() call on MAX");
        UE_LOG(LogTemp,Warning,TEXT("%s call on MAX"), *InString)
        break;
    default: ;
    }
}
