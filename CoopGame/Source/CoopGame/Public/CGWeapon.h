// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CGWeapon.generated.h"

class USkeletalMeshComponent;

UCLASS()
class COOPGAME_API ACGWeapon : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ACGWeapon();

	UPROPERTY(VisibleAnywhere, Category="Game|Weapon")
	USkeletalMeshComponent* SkeletalMesh;

	UFUNCTION( Server, Reliable, BlueprintCallable,Category="Weapon",WithValidation)
	void Fire_Server();




	
	UFUNCTION(Client,Reliable,Category="Weapon")
	void FireClient(FVector InStartLocation, FVector InEndLocation);

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite, Category="Game|Weapon")
	float BaseDamage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Game|Weapon")
	TSubclassOf<UDamageType> DamageType;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
