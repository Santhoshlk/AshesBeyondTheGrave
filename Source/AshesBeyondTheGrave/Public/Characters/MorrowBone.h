// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "CharacterState.h"
#include "Characters/AttackStateEnum.h"
#include "MorrowBone.generated.h"


class UInputConfigDataAsset;
class UCapsuleComponent;
class USkeletalMeshComponent;
class UInputMappingContext;
class UInputAction;
class UAnimMontage;
class USpringArmComponent;
class UCameraComponent;

UCLASS()
class ASHESBEYONDTHEGRAVE_API AMorrowBone : public ACharacter
{
	GENERATED_BODY()

public:
	
	AMorrowBone();

	virtual void Tick(float DeltaTime) override;

	//create a function to reset the state of character and then make logic for heavy and special attacks

	UFUNCTION(BlueprintCallable)
	void LightAttackEnd();
	
	UFUNCTION(BlueprintCallable)
	void HeavyAttackEnd();

	UFUNCTION(BlueprintCallable)
	void SuperChargedAttackEnd();
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
protected:
	
	virtual void BeginPlay() override;

    UPROPERTY()
	UCapsuleComponent* Capsule;
	
	UPROPERTY()
	USkeletalMeshComponent* Skeleton;
#pragma region component
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly, Category="Input")
	UInputConfigDataAsset* InputConfigData;
#pragma endregion

#pragma region Montages
	UPROPERTY(EditDefaultsOnly,Category="Input")
	TObjectPtr<UAnimMontage> StartAnimationMontage;

	// create the TArray so that u can have multiple Attack Montages
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TArray<TObjectPtr<UAnimMontage>> LightAttackMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TArray<TObjectPtr<UAnimMontage>> HeavyAttackMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TArray<TObjectPtr<UAnimMontage>> SuperChargedAttackMontage;

#pragma endregion
	
#pragma region Functions
	void StartMontage();
	void Moving(const FInputActionValue& value);

	void Looking(const FInputActionValue& value);

	void StartSprinting(const FInputActionValue& value);
	void RunSprinting(const FInputActionValue& value);

	void EndSprinting(const FInputActionValue& value);

	bool sprint = false;

	void LightAttacks();
	void HeavyAttacks();
	void SuperChargedAttacks();

	void StaticCameraStopped();

	void StaticCameraStarted();
#pragma endregion
	
private:
#pragma region Variables
	ECharacterMoving Movement = ECharacterMoving::ECM_Moving;
	EAttackState AttackState=EAttackState::EAS_NotAttacking;
	EAttackState HeavyAttackState=EAttackState::EAS_NotAttacking;
	int LightAttackCounter=0;
	int HeavyAttackCounter=0;

	//create the spring arm and the camera component
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USpringArmComponent> SpringArm;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UCameraComponent> Camera;

	bool StartingMontageEnded = false;

#pragma endregion 
public:
	UFUNCTION()
 FORCEINLINE	ECharacterMoving GetMovementState() const {
		return Movement;
	}
};
