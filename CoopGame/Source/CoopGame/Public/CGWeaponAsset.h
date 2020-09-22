// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "UObject/ObjectMacros.h"

#include "CGWeaponAsset.generated.h"

class USkeletalMesh;

/**
 * 
 */
UCLASS(BlueprintType)
class COOPGAME_API UCGWeaponAsset : public UDataAsset
{
	GENERATED_BODY()

	public:
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	TSoftObjectPtr<USkeletalMesh> SkeletalMesh;

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	float BaseDamage;
};
