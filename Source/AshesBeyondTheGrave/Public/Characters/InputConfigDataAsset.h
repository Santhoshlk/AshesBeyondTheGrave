// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "InputConfigDataAsset.generated.h"

class UInputMappingContext;
class UInputAction;
/**
 * 
 */
// create a struct
USTRUCT(BlueprintType)
struct FMorrowBoneInputConfig
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,meta=(AllowPrivateAccess=true))
	FGameplayTag InputTag;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,meta=(Category="Input"))
	TObjectPtr<UInputAction> InputAction;
};
UCLASS()
class ASHESBEYONDTHEGRAVE_API UInputConfigDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,meta=(AllowPrivateAccess=true))
	TObjectPtr<UInputMappingContext> InputMappingContext;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,meta=(AllowPrivateAccess=true))
	TArray<FMorrowBoneInputConfig> NativeInputActions;

   
	TObjectPtr<UInputAction> FindInputActionByGameplayTag(const FGameplayTag &InInputTag);
};
