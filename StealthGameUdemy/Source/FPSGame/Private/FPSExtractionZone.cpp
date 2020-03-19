// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSExtractionZone.h"
#include "Components/BoxComponent.h"
#include "Components/DecalComponent.h"
#include "FPSCharacter.h"
#include "FPSGameMode.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AFPSExtractionZone::AFPSExtractionZone()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxZone = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxZone"));
	BoxZone->SetCollisionResponseToAllChannels(ECR_Ignore);
	BoxZone->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	RootComponent = BoxZone;
	//	Add delegate bind
	BoxZone->OnComponentBeginOverlap.AddDynamic(this, &AFPSExtractionZone::OnZoneOverlapBegin);

	
	DecalComp = CreateDefaultSubobject<UDecalComponent>(TEXT("DecalComp"));
	DecalComp->DecalSize = FVector(200.f);
	DecalComp->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AFPSExtractionZone::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFPSExtractionZone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFPSExtractionZone::OnZoneOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	class AFPSCharacter* L_OverlappedPawn = Cast<AFPSCharacter>(OtherActor);
	//	Check character to nulptr, call return if hi is
	if (L_OverlappedPawn == nullptr)
	{
		return;
	}
	//	Check character is carrying objective item
	if (L_OverlappedPawn->bIsCarryingObjective)
	{
		UE_LOG(LogTemp, Warning, TEXT("Overlap!"));

		AFPSGameMode* L_GM = Cast<AFPSGameMode>(GetWorld()->GetAuthGameMode());

		if (L_GM)
		{
			//	Mission completed
			L_GM->CompleteMission(L_OverlappedPawn);
		}

	}
	//	Play sound if hi not have objective item
	else
	{
		UGameplayStatics::PlaySound2D(this, ObjectiveMissingSound);

	}
}

