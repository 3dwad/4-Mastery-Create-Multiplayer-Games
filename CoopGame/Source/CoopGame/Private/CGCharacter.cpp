// Fill out your copyright notice in the Description page of Project Settings.


#include "CGCharacter.h"
#include "CGWeaponAsset.h"
#include "CGWeapon.h"
#include "CGHealthComponent.h"
#include "Camera/CameraComponent.h"
#include "CoopGame/CoopGame.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Net/UnrealNetwork.h"

// Sets default values
ACGCharacter::ACGCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	SpringArm->SetupAttachment(GetRootComponent());
	SpringArm->bUsePawnControlRotation = true;
	
	Camera = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	Camera->SetupAttachment(SpringArm);

	HealthComponent = CreateDefaultSubobject<UCGHealthComponent>("HealthComponent");
}

// Called when the game starts or when spawned
void ACGCharacter::BeginPlay()
{
	Super::BeginPlay();
	GetMovementComponent()->GetNavAgentPropertiesRef().bCanCrouch = true;

	HealthComponent->OnTakeDamage.AddDynamic(this, &ACGCharacter::OnHealthChange);

	// if(GetLocalRole() == ROLE_Authority)
	// {
	// 	if (WeaponDataAsset)
	// 	{
	// 		Weapon = SpawnWeapon(WeaponDataAsset);
	// 	}
	// }

	if (HasAuthority())
	{
		if(BaseWeaponClass)
		{FActorSpawnParameters SpawnParams;

			SpawnParams.Owner = this;
			SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

			Weapon = GetWorld()->SpawnActor<ACGWeapon>(BaseWeaponClass, SpawnParams);
			Weapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, "WeaponSocket");
		}
	}
}

void ACGCharacter::MoveForward(float InValue)
{
	AddMovementInput(GetActorForwardVector() * InValue);

}

void ACGCharacter::MoveRight(float InValue)
{
	AddMovementInput(GetActorRightVector() * InValue);
}

void ACGCharacter::BeginCrouch()
{
	Crouch();
}

void ACGCharacter::EndCrouch()
{
	UnCrouch();
}

void ACGCharacter::CrouchToggle()
{
	bIsCrouched ? EndCrouch() : BeginCrouch();
}

ACGWeapon* ACGCharacter::SpawnWeapon(UCGWeaponAsset* InAsset)
{
	if (InAsset)
	{
		// Create template
		// auto TemplateWeapon = NewObject<ACGWeapon>(this, "Weapon", EObjectFlags::RF_Transient);
		//
		// TemplateWeapon->SkeletalMesh->SetSkeletalMesh(InAsset->SkeletalMesh.LoadSynchronous());
		// TemplateWeapon->BaseDamage = InAsset->BaseDamage;
		// TemplateWeapon->DamageType = InAsset->DamageType;

		FActorSpawnParameters SpawnParams;
		//SpawnParams.Template = TemplateWeapon;
		SpawnParams.Owner = this;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		auto OutWeapon = GetWorld()->SpawnActor<ACGWeapon>(SpawnParams);
		OutWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, "WeaponSocket");
		// OutWeapon->SkeletalMesh->SetSkeletalMesh(InAsset->SkeletalMesh.LoadSynchronous());
		// OutWeapon->BaseDamage = InAsset->BaseDamage;
		// OutWeapon->DamageType = InAsset->DamageType;
		return OutWeapon;
	}

	return nullptr;
}

// Called every frame
void ACGCharacter::Tick(float DeltaTime)
{
	FCGHelper::PrintLocalRole(this);
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ACGCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ACGCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ACGCharacter::MoveRight);

	PlayerInputComponent->BindAxis("LookUp", this, &ACGCharacter::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("Turn", this, &ACGCharacter::AddControllerYawInput);

	PlayerInputComponent->BindAction("Crouch", EInputEvent::IE_Pressed, this, &ACGCharacter::CrouchToggle);
	PlayerInputComponent->BindAction("Jump", EInputEvent::IE_Pressed, this, &ACGCharacter::Jump);
}

FVector ACGCharacter::GetPawnViewLocation() const
{
	return Camera->GetComponentLocation();
}

// void ACGCharacter::SetupWeapon_Client_Implementation()
// {
// 	if(Weapon)
// 	{
// 		Weapon->SkeletalMesh->SetSkeletalMesh(WeaponDataAsset->SkeletalMesh.LoadSynchronous());
// 		Weapon->BaseDamage = WeaponDataAsset->BaseDamage;
// 		Weapon->DamageType = WeaponDataAsset->DamageType;
// 	}
// 	else
// 	{
// 		UE_LOG(LogTemp,Error,TEXT("Weapon is null"));
// 	}
// }

void ACGCharacter::OnHealthChange_Implementation(float Damage, float CurrentHealth)
{
}

void ACGCharacter::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ACGCharacter, WeaponDataAsset);
	DOREPLIFETIME(ACGCharacter, Weapon);
}
