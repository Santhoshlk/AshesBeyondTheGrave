// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "MorrowBone.generated.h"



class UCapsuleComponent;
class UskeletalMeshComponent;
class UInputMappingContext;
class UInputAction;
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


	UCapsuleComponent* Capsule;
	
	
	USkeletalMeshComponent* Skeleton;

	
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* MoveAction;
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* LookAction;
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputMappingContext* MappingContext;

	void Moving(const FInputActionValue& value);

	void Looking(const FInputActionValue& value);
	
};
