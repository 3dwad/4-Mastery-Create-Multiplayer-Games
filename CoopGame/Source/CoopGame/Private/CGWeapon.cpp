// Fill out your copyright notice in the Description page of Project Settings.


#include "CGWeapon.h"

// Sets default values
ACGWeapon::ACGWeapon()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>("SkeletalMesh");
	RootComponent = SkeletalMesh;
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

