#pragma once

UENUM(BlueprintType)

enum class ECharacterMoving : uint8
{
	ECM_Moving UMETA(DisplayName = "Moving"),
	ECM_Sprinting UMETA(DisplayName = "Sprinting")
};