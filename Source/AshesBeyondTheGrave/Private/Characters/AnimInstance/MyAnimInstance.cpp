// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/AnimInstance/MyAnimInstance.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Characters/MorrowBone.h"
#include "Kismet/KismetMathLibrary.h"

void UMyAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	Character = Cast<AMorrowBone>(TryGetPawnOwner());
	if (Character)
	{
		MovementInput = Character->GetCharacterMovement();
	}

}

void UMyAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	
	if (MovementInput)
	{
		GroundSpeed = UKismetMathLibrary::VSizeXY(MovementInput->Velocity);
		
	}
	if (Character)
	{
		CharacterMovementState = Character->GetMovementState();
	}
}
