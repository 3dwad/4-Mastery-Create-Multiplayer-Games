// Fill out your copyright notice in the Description page of Project Settings.


#include "CGHealthComponent.h"


// Sets default values for this component's properties
UCGHealthComponent::UCGHealthComponent()
{
	DefaultHealth = 100.f;
}


// Called when the game starts
void UCGHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	CurrentHealth = DefaultHealth;
	if(AActor* CurrentOwner = GetOwner())
	{
		CurrentOwner->OnTakeAnyDamage.AddDynamic(this, &UCGHealthComponent::HealthDecrease_OnTakeAnyDamage);
	}
	
}

void UCGHealthComponent::HealthDecrease_OnTakeAnyDamage(AActor* DamagedActor, float Damage,const UDamageType* DamageType, AController* InstigatedBy,AActor* DamageCauser)
{
	if (Damage < CurrentHealth)
	{
		CurrentHealth -= Damage;
		OnTakeDamage.Broadcast(Damage,CurrentHealth);
		return;
	}

	CurrentHealth = 0;
	OnHealthZero.Broadcast();
}

