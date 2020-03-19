// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FPSBlackHole.generated.h"

UCLASS()
class FPSGAME_API AFPSBlackHole : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFPSBlackHole();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class USphereComponent* ReactionZone;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class USphereComponent* DestroyZone;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* BlackHole;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TArray<UPrimitiveComponent*> OverlappingComponents;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float ReactionRadius;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//	Declaration function for delegate
	UFUNCTION()
	void OverlapDestroyZone(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
