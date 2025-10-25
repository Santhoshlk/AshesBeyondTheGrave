// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/InputConfigDataAsset.h"

TObjectPtr<UInputAction> UInputConfigDataAsset::FindInputActionByGameplayTag(const FGameplayTag& InInputTag)
{
	for (FMorrowBoneInputConfig InputConfig: NativeInputActions)
	{
		if (InputConfig.InputTag==InInputTag)
		{
			return InputConfig.InputAction;
		}
	}
	return nullptr;
}
