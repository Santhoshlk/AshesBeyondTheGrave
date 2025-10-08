// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "CharacterState.h"
#include "MorrowBone.generated.h"



class UCapsuleComponent;
class UskeletalMeshComponent;
class UInputMappingContext;
class UInputAction;
class UAnimMontage;
UCLASS()
class ASHESBEYONDTHEGRAVE_API AMorrowBone : public ACharacter
{
	GENERATED_BODY()

public:
	
	AMorrowBone();

	virtual void Tick(float DeltaTime) override;


	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
protected:
	
	virtual void BeginPlay() override;

    UPROPERTY()
	UCapsuleComponent* Capsule;
	
	UPROPERTY()
	USkeletalMeshComponent* Skeleton;

	
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* MoveAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* LookAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* SprintAction;

	UPROPERTY(EditDefaultsOnly,Category="Input")
	UInputAction* JumpAction;

	//create an input action for Light attacks
	UPROPERTY(EditDefaultsOnly,Category="Input")
	TObjectPtr<UInputAction> LightAttackAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")

	UInputMappingContext* MappingContext;

	UPROPERTY(EditDefaultsOnly,Category="Input")
	TObjectPtr<UAnimMontage> StartAnimationMontage;

	// create the TArray so that u can have multiple Attack Montages
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TArray<TObjectPtr<UAnimMontage>> LightAttackMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TArray<TObjectPtr<UAnimMontage>> HeavyAttackMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TArray<TObjectPtr<UAnimMontage>> SuperChargedAttackMontage;

	void StartMontage();
	void Moving(const FInputActionValue& value);

	void Looking(const FInputActionValue& value);

	void StartSprinting(const FInputActionValue& value);
	void RunSprinting(const FInputActionValue& value);

	void EndSprinting(const FInputActionValue& value);

	bool sprint = false;

	void LightAttacks();
	
protected:

	ECharacterMoving Movement = ECharacterMoving::ECM_Moving;
	
public:
	UFUNCTION()
 FORCEINLINE	ECharacterMoving GetMovementState() {
		return Movement;
	}
};
