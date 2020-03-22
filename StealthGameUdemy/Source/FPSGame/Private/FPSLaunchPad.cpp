// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSLaunchPad.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "FPSCharacter.h"
#include "Engine/Engine.h"
// #include "Engine/World.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AFPSLaunchPad::AFPSLaunchPad()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	MeshMain = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshMain"));
	MeshMain->SetupAttachment(GetRootComponent());

	MeshArrow = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshArrow"));
	MeshArrow->SetupAttachment(GetRootComponent());

	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger"));
	TriggerBox->SetupAttachment(GetRootComponent());
	TriggerBox->SetCollisionObjectType(ECC_WorldDynamic);
	TriggerBox->SetCollisionResponseToAllChannels(ECR_Ignore);
	TriggerBox->SetCollisionResponseToChannel(ECC_Pawn, ECollisionResponse::ECR_Overlap);
	TriggerBox->SetCollisionResponseToChannel(ECC_PhysicsBody, ECR_Overlap);

	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &AFPSLaunchPad::OnOverlapBegin);

	
}

// Called when the game starts or when spawned
void AFPSLaunchPad::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFPSLaunchPad::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFPSLaunchPad::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(2, 5.f, FColor::White, OtherActor->GetClass()->GetName());
	}


	//	Cast to PlayerCharacter, and do if valid
	if (AFPSCharacter* L_PlayerCharacter = Cast<AFPSCharacter>(OtherActor))
	{

		//	Debug
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(1, 5.f, FColor::Red, "Character Overlap");
		}

	//	Calculate Launch Velocity and launch
		LaunchVelocity = CalculateVelocity();
		L_PlayerCharacter->LaunchCharacter(LaunchVelocity, true, true);
		UGameplayStatics::SpawnEmitterAtLocation(this, ParticleForLaunch, OtherActor->GetActorLocation());
		
	}

	//	If Character not valid< check invite component to simulate physic, and add impulse to him
	else if ((OtherComp) && (OtherComp->IsSimulatingPhysics()))
	{

		LaunchVelocity = CalculateVelocity();
		OtherComp->AddImpulse(LaunchVelocity,NAME_None,true);
		UGameplayStatics::SpawnEmitterAtLocation(this, ParticleForLaunch, OtherActor->GetActorLocation());
		

		//	Debug
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(3, 5.f, FColor::Green, "Component Overlap");
		}
	}

}
		
	
//	Calculate velocity for LauncPad
FVector AFPSLaunchPad::CalculateVelocity()
{
	
	FRotator L_LaunchDirection = GetActorRotation();
	L_LaunchDirection.Pitch += LaunchPitch;	
	FVector L_NewDirectionVector = L_LaunchDirection.Vector() * LaunchStrength;
	
	return FVector (L_NewDirectionVector);
}




