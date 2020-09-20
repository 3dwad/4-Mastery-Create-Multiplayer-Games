
#include "FPSHelper.h"

void FFPSHelper::PrintToLogEverywhere(AActor* InActor, const FString InString)
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