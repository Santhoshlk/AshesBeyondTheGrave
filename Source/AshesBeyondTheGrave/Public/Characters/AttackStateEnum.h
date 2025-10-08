#pragma once

#include "CoreMinimal.h"
#include "AttackStateEnum.generated.h"

UENUM(BlueprintType)
enum class EAttackState: uint8
{
	EAS_NotAttacking UMETA(DisplayName="Not Attacking"),
	EAS_LightAttack UMETA(DisplayName="Light Attack"),
	EAS_HeavyAttack UMETA(DisplayName = "HeavyAttack"),
	EAS_SuperChargedAttack UMETA(DisplayName ="SuperChargedAttack"),
	EAS_NULL UMETA(DisplayName="NULL")
};