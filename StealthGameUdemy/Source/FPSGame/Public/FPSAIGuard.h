// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FPSAIGuard.generated.h"

class UPawnSensingComponent;


//	Add new enum
UENUM(BlueprintType)
enum class EAIState : uint8
{

	Idle,

	Suspicious,

	Alerted

};


UCLASS()
class FPSGAME_API AFPSAIGuard : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFPSAIGuard();

	/* Need patrol or not */
	UPROPERTY(EditInstanceOnly, Category = "AI")
	bool bIsNeedPatrol;

	/* First point */	/* EditCondition with meta use for do unavailable this variables for edit*/
	UPROPERTY(EditInstanceOnly, Category = "AI", meta = (EditCondition = "bIsNeedPatrol"))
	AActor* FirstPatrolPont;

	/* Second point */	/* EditCondition with meta use for do unavailable this variables for edit*/
	UPROPERTY(EditInstanceOnly, Category = "AI", meta = (EditCondition = "bIsNeedPatrol"))
	AActor* SecondPatrolPont;

	/* Current point */
	UPROPERTY()
	AActor* TargetPatrolPoint;

	UPROPERTY()
	bool bCondition;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UPawnSensingComponent* PawnSensingComp;
		
	UPROPERTY()
	FRotator InitilizeRotation;

	UPROPERTY()
	FTimerHandle TimerHandle_ResetOrientation;

	UPROPERTY(ReplicatedUsing=OnRep_GuardState)
	EAIState GuardState;




public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnPawnSeen(APawn* Pawn);

	UFUNCTION()
	void OnPawnHeard(APawn* NoiseInstigator, const FVector& Location, float Volume);

	UFUNCTION()
	void ResetOrierntation();

	UFUNCTION()
	void SetGuardState(EAIState NewState);

	UFUNCTION(BlueprintImplementableEvent)
	void OnStateChanged(EAIState NewState);

	UFUNCTION()
	void GoToNextPoint();

	UFUNCTION()
	void OnRep_GuardState();

};
