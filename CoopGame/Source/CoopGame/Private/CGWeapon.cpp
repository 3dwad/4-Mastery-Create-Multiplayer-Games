// Fill out your copyright notice in the Description page of Project Settings.


#include "CGWeapon.h"

#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ACGWeapon::ACGWeapon()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>("SkeletalMesh");
	RootComponent = SkeletalMesh;
}

void ACGWeapon::Fire()
{
	if (AActor* CurrentOwner = GetOwner())
	{
		FVector EyeLocation;
		FRotator EyeRotation;

		
		CurrentOwner->GetActorEyesViewPoint(EyeLocation, EyeRotation);

		FVector ShootDirection = EyeRotation.Vector();
		FVector EndTrace = EyeLocation + ShootDirection * 10000;

		FCollisionQueryParams QueryParams;
		QueryParams.AddIgnoredActor(CurrentOwner);
		QueryParams.AddIgnoredActor(this);
		QueryParams.bTraceComplex = true;

		FHitResult HitResult;
		if (GetWorld()->LineTraceSingleByChannel(HitResult, EyeLocation, EndTrace, ECC_Visibility, QueryParams))
		{
			if (AActor* HitActor = HitResult.GetActor())
			{
				UE_LOG(LogTemp,Warning,TEXT("Hit actor is %s, damage is %s"), *HitActor->GetActorLabel(), *FString::SanitizeFloat(BaseDamage))
				UGameplayStatics::ApplyPointDamage(HitActor, BaseDamage, ShootDirection, HitResult, GetInstigatorController(), this, DamageType);
			}
		}

		DrawDebugLine(GetWorld(),EyeLocation,EndTrace,FColor::Green,false,1.f,0,1);
	}
}

// Called when the game starts or when spawned
void ACGWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACGWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

