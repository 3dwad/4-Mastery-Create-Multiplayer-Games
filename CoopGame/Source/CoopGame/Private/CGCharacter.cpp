// Fill out your copyright notice in the Description page of Project Settings.


#include "CGCharacter.h"
#include "CGWeaponAsset.h"
#include "CGWeapon.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/PawnMovementComponent.h"

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

	GetMovementComponent()->GetNavAgentPropertiesRef().bCanCrouch = true;
}

// Called when the game starts or when spawned
void ACGCharacter::BeginPlay()
{
	Super::BeginPlay();
	
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

void ACGCharacter::SpawnWeapon(UCGWeaponAsset* InAsset)
{
	if (InAsset && InAsset->SkeletalMesh.LoadSynchronous())
	{
		// Create template
		auto TemplateWeapon = NewObject<ACGWeapon>(this, "Weapon", EObjectFlags::RF_Transient);

		TemplateWeapon->SkeletalMesh->SetSkeletalMesh(InAsset->SkeletalMesh.LoadSynchronous());
		TemplateWeapon->BaseDamage = InAsset->BaseDamage;

		FActorSpawnParameters SpawnParams;
		SpawnParams.Template = TemplateWeapon;
		SpawnParams.Instigator = this;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		auto Weapon = GetWorld()->SpawnActor<ACGWeapon>(SpawnParams);
		Weapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, "WeaponSocket");
	}
}

// Called every frame
void ACGCharacter::Tick(float DeltaTime)
{
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

