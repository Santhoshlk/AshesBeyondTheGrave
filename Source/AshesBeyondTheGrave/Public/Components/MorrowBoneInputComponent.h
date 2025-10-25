// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "GameplayTagContainer.h"
#include "Characters/InputConfigDataAsset.h"
#include "MorrowBoneInputComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class ASHESBEYONDTHEGRAVE_API UMorrowBoneInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()
public:
	
   template<class UserObject,typename CallBackFunc>
	void BindingInputs( UInputConfigDataAsset* &DataAsset,const FGameplayTag& InInputTag,ETriggerEvent TriggerEvent,const UserObject &Object,CallBackFunc Func);
};

template <class UserObject, typename CallBackFunc>
void UMorrowBoneInputComponent::BindingInputs( UInputConfigDataAsset* &DataAsset,const FGameplayTag& InInputTag, ETriggerEvent TriggerEvent,
	const UserObject& Object, CallBackFunc Func)
{
	checkf(DataAsset,TEXT("Invalid DataAsset"));
	if (TObjectPtr<UInputAction> InputAction=DataAsset->FindInputActionByGameplayTag(InInputTag))
	{
		BindAction(InputAction,TriggerEvent,Object,Func);
	}
}
