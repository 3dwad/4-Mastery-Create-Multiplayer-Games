// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CGHealthComponent.generated.h"

class UDamageType;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FHealthZeroSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FTakeDamageSignature, float, Damage, float, CurrentHealth);


UCLASS( ClassGroup=(COOP), meta=(BlueprintSpawnableComponent) )
class COOPGAME_API UCGHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCGHealthComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly)
	float CurrentHealth;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	float DefaultHealth;

	UFUNCTION()
	void HealthDecrease_OnTakeAnyDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

	public:

	UPROPERTY(BlueprintAssignable, Category="Game|Damage")
	FHealthZeroSignature OnHealthZero;

	UPROPERTY(BlueprintAssignable, Category="Game|Damage")
	FTakeDamageSignature OnTakeDamage;

};
