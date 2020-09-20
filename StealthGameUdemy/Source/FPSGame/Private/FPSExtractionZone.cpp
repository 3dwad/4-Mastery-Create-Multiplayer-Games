// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSExtractionZone.h"
#include "Components/BoxComponent.h"
#include "Components/DecalComponent.h"
#include "FPSCharacter.h"
#include "FPSGameMode.h"
#include "FPSHelper.h"
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

void AFPSExtractionZone::OnZoneOverlapBegin(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep,
	const FHitResult& SweepResult)
{
	if (const auto OverlappedPawn = Cast<AFPSCharacter>(OtherActor))
	{
		//	Check character is carrying objective item
		if (OverlappedPawn->bIsCarryingObjective)
		{
			FFPSHelper::PrintToLogEverywhere(this, "OnZoneOverlapBegin()");

			if (auto AuthorityGM = Cast<AFPSGameMode>(GetWorld()->GetAuthGameMode()))
			{
				//	Mission completed
				FFPSHelper::PrintToLogEverywhere(this, "AuthorityGM is valid");
				AuthorityGM->CompleteMission(OverlappedPawn, true);
			}
			else
			{
				FFPSHelper::PrintToLogEverywhere(this, "AuthorityGM is not valid");
			}
		}
			//	Play sound if hi not have objective item
		else
		{
			UGameplayStatics::PlaySound2D(this, ObjectiveMissingSound);
		}
	}
}

