// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CGCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UCGWeaponAsset;

UCLASS()
class COOPGAME_API ACGCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACGCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void MoveForward(float InValue);
	void MoveRight(float InValue);
	
	void BeginCrouch();
	void EndCrouch();

	void CrouchToggle();

	UFUNCTION(BlueprintCallable)
	void SpawnWeapon(UCGWeaponAsset* InAsset);

	UPROPERTY(VisibleAnywhere, Category="Components")
	UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere, Category="Components")
	USpringArmComponent* SpringArm;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
