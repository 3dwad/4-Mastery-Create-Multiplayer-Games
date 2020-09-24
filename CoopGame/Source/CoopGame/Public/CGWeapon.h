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

	UPROPERTY()
	USkeletalMeshComponent* SkeletalMesh;

	UFUNCTION(BlueprintCallable,Category="Weapon")
	void Fire();

	UPROPERTY()
	float BaseDamage;
	
	TSubclassOf<UDamageType> DamageType;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
