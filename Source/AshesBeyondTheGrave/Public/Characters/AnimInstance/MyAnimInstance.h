// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MyAnimInstance.generated.h"

/**
 * 
 */
class AMorrowBone;
class UCharacterMovementComponent;
UCLASS()
class ASHESBEYONDTHEGRAVE_API UMyAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
public:

	virtual void NativeInitializeAnimation() override;
	
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	UPROPERTY(BlueprintReadOnly, Category = "Character")
	AMorrowBone* Character;

	UPROPERTY(BlueprintReadOnly, Category = "CharacterMovement")
	UCharacterMovementComponent* MovementInput;

	UPROPERTY(BlueprintReadOnly, Category = "Variables")
	float GroundSpeed;
};
