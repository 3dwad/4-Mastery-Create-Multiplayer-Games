// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSBlackHole.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/Engine.h"
#include "Components/PrimitiveComponent.h"


// Sets default values
AFPSBlackHole::AFPSBlackHole()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent->SetupAttachment(GetRootComponent());

	BlackHole = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BlackHole"));
	BlackHole->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	BlackHole->SetupAttachment(GetRootComponent());

	DestroyZone = CreateDefaultSubobject<USphereComponent>(TEXT("DestroyZone"));
	DestroyZone->SetupAttachment(GetRootComponent());
	ReactionZone = CreateDefaultSubobject<USphereComponent>(TEXT("ReactionZone"));
	ReactionZone->SetupAttachment(GetRootComponent());

	
	
	
}

// Called when the game starts or when spawned
void AFPSBlackHole::BeginPlay()
{


	Super::BeginPlay();

		
	FString ArrayLenght = FString::FromInt(OverlappingComponents.Num());

	GEngine->AddOnScreenDebugMessage(1, 5.f, FColor::Green, ArrayLenght);

	ReactionRadius = ReactionZone->GetUnscaledSphereRadius();
	
	//	Call delegate on component begin overlap 
	DestroyZone->OnComponentBeginOverlap.AddDynamic(this, &AFPSBlackHole::OverlapDestroyZone);


}

// Called every frame
void AFPSBlackHole::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ReactionZone->GetOverlappingComponents(OverlappingComponents);

	//	For each loop
	for (int32 i = 0; i < OverlappingComponents.Num(); i += 1)
	{

		UPrimitiveComponent* PrimComp = OverlappingComponents[i];

		if (PrimComp && PrimComp->IsSimulatingPhysics())
		{

			PrimComp->AddRadialForce(GetActorLocation(), ReactionRadius, -1500000.f, ERadialImpulseFalloff::RIF_Constant);

			GEngine->AddOnScreenDebugMessage(1, 0.f, FColor::Green, "Its work");
		}
		


	}


}

void AFPSBlackHole::OverlapDestroyZone(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	UE_LOG(LogTemp, Warning, TEXT("Overap"));
	OtherActor->Destroy();

}

