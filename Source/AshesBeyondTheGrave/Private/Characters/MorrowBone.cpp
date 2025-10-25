


#include "Characters/MorrowBone.h"
#include "Components/SkeletalMeshComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Animation/AnimInstance.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Characters/InputConfigDataAsset.h"
#include "Components/MorrowBoneInputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameplayTags/MorrowBoneGameplayTags.h"

AMorrowBone::AMorrowBone()
{
 	
	PrimaryActorTick.bCanEverTick = true;
	Capsule = GetCapsuleComponent();
	Skeleton = GetMesh();
	StartingMontageEnded = false;


	//first stop the rotation of the character
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;
	
	// set character orient to movement
	GetCharacterMovement()->bOrientRotationToMovement= true;
	GetCharacterMovement()->RotationRate=FRotator(0.f,450.f,0.f);
	//create the objects of camera and spring arm

	SpringArm=CreateDefaultSubobject<USpringArmComponent>( TEXT("SpringArm"));
	SpringArm->SetupAttachment(GetRootComponent());
	SpringArm->TargetArmLength= 300.f;
	SpringArm->bUsePawnControlRotation =true;

	//camera is attached to spring Arm
	Camera= CreateDefaultSubobject<UCameraComponent>( TEXT("CameraComponent"));
	Camera->SetupAttachment(SpringArm,USpringArmComponent::SocketName);
	//we should not allow camera to use rotation
	Camera->bUsePawnControlRotation = false;
}


void AMorrowBone::BeginPlay()
{
	Super::BeginPlay();
	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	if (PlayerController)
	{
		UEnhancedInputLocalPlayerSubsystem* SubSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
		if (SubSystem)
		{
			SubSystem->AddMappingContext(InputConfigData->InputMappingContext, 0);
		}
	}
	StartMontage();
	StartingMontageEnded= true;
}

void AMorrowBone::StartMontage()
{
	TObjectPtr<UAnimInstance> AnimInstance=GetMesh()->GetAnimInstance();
	if (IsValid(AnimInstance) && IsValid(StartAnimationMontage))
	{
		AnimInstance->Montage_Play(StartAnimationMontage);
	}
}

void AMorrowBone::Moving(const FInputActionValue& value)
{

	
	if (IsValid(Controller) &&  StartingMontageEnded)
	{
		const FVector2D MovementVector = value.Get<FVector2D>();
		const FRotator Rotation = Controller->GetControlRotation();

		FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

		const FVector ForwardVector = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(ForwardVector, MovementVector.Y);
		const FVector RightVector = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(RightVector, MovementVector.X);
	}
}

void AMorrowBone::Looking(const FInputActionValue& value)
{
	if (IsValid(Controller) && StartingMontageEnded)
	{
		const FVector2D Rotation = value.Get<FVector2D>();
		AddControllerYawInput(Rotation.X);
		AddControllerPitchInput(Rotation.Y);
	}
}

void AMorrowBone::StartSprinting(const FInputActionValue& value)
{
	Movement = ECharacterMoving::ECM_Sprinting;
}

void AMorrowBone::RunSprinting(const FInputActionValue& value)
{
	Movement = ECharacterMoving::ECM_Sprinting;
}

void AMorrowBone::EndSprinting(const FInputActionValue& value)
{
	Movement = ECharacterMoving::ECM_Moving;
}

void AMorrowBone::LightAttacks()
{
	if (AttackState==EAttackState::EAS_NotAttacking && StartingMontageEnded)
	{
		TObjectPtr<UAnimInstance> AnimInstance=GetMesh()->GetAnimInstance();
		if (IsValid(AnimInstance) && !LightAttackMontage.IsEmpty())
		{
			int32 Montage_Number= FMath::RandRange(0,LightAttackMontage.Num()-1);

			AnimInstance->Montage_Play(LightAttackMontage[Montage_Number]);
		}
		AttackState=EAttackState::EAS_LightAttack;
	}
	
	
}

void AMorrowBone::HeavyAttacks()
{
	if (HeavyAttackState==EAttackState::EAS_HeavyAttack)
	{
		TObjectPtr<UAnimInstance> AnimInstance=GetMesh()->GetAnimInstance();
		if (IsValid(AnimInstance) && !HeavyAttackMontage.IsEmpty())
		{
			int32 Montage_Number= FMath::RandRange(0,HeavyAttackMontage.Num()-1);

			AnimInstance->Montage_Play(HeavyAttackMontage[Montage_Number]);
		}
		// No Attacks should work
		HeavyAttackState=EAttackState::EAS_NotAttacking;
		AttackState=EAttackState::EAS_LightAttack;
	}
}

void AMorrowBone::SuperChargedAttacks()
{
	if (HeavyAttackState==EAttackState::EAS_SuperChargedAttack)
	{
		TObjectPtr<UAnimInstance> AnimInstance=GetMesh()->GetAnimInstance();
		if (IsValid(AnimInstance) && !SuperChargedAttackMontage.IsEmpty())
		{
			int32 Montage_Number= FMath::RandRange(0,SuperChargedAttackMontage.Num()-1);

			AnimInstance->Montage_Play(SuperChargedAttackMontage[Montage_Number]);
		}
		HeavyAttackState=EAttackState::EAS_NotAttacking;
		AttackState=EAttackState::EAS_NotAttacking;
	}
}

void AMorrowBone::StaticCameraStopped()
{
	//
	SpringArm->bUsePawnControlRotation = true;
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	GetCharacterMovement()->bOrientRotationToMovement =true;
	
}

void AMorrowBone::StaticCameraStarted()
{
	SpringArm->bUsePawnControlRotation = false;
	bUseControllerRotationPitch = true;
	bUseControllerRotationYaw = true;
	bUseControllerRotationRoll = true;
	GetCharacterMovement()->bOrientRotationToMovement =false;
	
}


void AMorrowBone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMorrowBone::LightAttackEnd()
{
	AttackState=EAttackState::EAS_NotAttacking;
     LightAttackCounter++;
	if (LightAttackCounter==6)
	{
		LightAttackCounter=0;
		//set so that u can perform heavy attack
		HeavyAttackState=EAttackState::EAS_HeavyAttack;
	}
	else
	{
		HeavyAttackState=EAttackState::EAS_LightAttack;
	}
  
}

void AMorrowBone::HeavyAttackEnd()
{
	//now reset the light attack counter
	LightAttackCounter=0;
	//as the heavy attack has ended
	HeavyAttackCounter++;
	if (HeavyAttackCounter==2)
	{
		HeavyAttackCounter=0;
		HeavyAttackState=EAttackState::EAS_SuperChargedAttack;
		AttackState=EAttackState::EAS_SuperChargedAttack;
	}
	else
	{
		HeavyAttackState=EAttackState::EAS_LightAttack;
		AttackState=EAttackState::EAS_NotAttacking;
	}
	
}

void AMorrowBone::SuperChargedAttackEnd()
{
	//a consequence of using supercharged attack
	//now leave every thing in no Attacking state
	LightAttackCounter=0;
	HeavyAttackCounter=0;
	HeavyAttackState=EAttackState::EAS_NotAttacking;
	AttackState=EAttackState::EAS_NotAttacking;
}


void AMorrowBone::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	UMorrowBoneInputComponent* PlayerComponent = CastChecked<UMorrowBoneInputComponent>(PlayerInputComponent);
	if (PlayerComponent)
	{
		PlayerComponent->BindingInputs(InputConfigData,MorrowBoneGameplayTags::Input_Move,ETriggerEvent::Triggered,this, &AMorrowBone::Moving);
		PlayerComponent->BindingInputs(InputConfigData,MorrowBoneGameplayTags::Input_Look,ETriggerEvent::Triggered,this,&AMorrowBone::Looking);
		PlayerComponent->BindingInputs(InputConfigData,MorrowBoneGameplayTags::Input_Sprint,ETriggerEvent::Started,this,&AMorrowBone::StartSprinting);
		PlayerComponent->BindingInputs(InputConfigData,MorrowBoneGameplayTags::Input_Sprint,ETriggerEvent::Completed,this,&AMorrowBone::EndSprinting);
		PlayerComponent->BindingInputs(InputConfigData,MorrowBoneGameplayTags::Input_Sprint,ETriggerEvent::Triggered,this,&AMorrowBone::RunSprinting);
			PlayerComponent->BindingInputs(InputConfigData,MorrowBoneGameplayTags::Input_Jump,ETriggerEvent::Triggered,this,&ACharacter::Jump);
		    PlayerComponent->BindingInputs(InputConfigData,MorrowBoneGameplayTags::Input_LightAttack,ETriggerEvent::Started,this,&AMorrowBone::LightAttacks);
		    PlayerComponent->BindingInputs(InputConfigData,MorrowBoneGameplayTags::Input_HeavyAttack,ETriggerEvent::Started,this,&AMorrowBone::HeavyAttacks);
		PlayerComponent->BindingInputs(InputConfigData,MorrowBoneGameplayTags::Input_SuperChargedAttack,ETriggerEvent::Started,this,&AMorrowBone::SuperChargedAttacks);
		PlayerComponent->BindingInputs(InputConfigData,MorrowBoneGameplayTags::Input_FreeCamera,ETriggerEvent::Triggered,this,&AMorrowBone::StaticCameraStarted);
		PlayerComponent->BindingInputs(InputConfigData,MorrowBoneGameplayTags::Input_FreeCamera,ETriggerEvent::Completed,this,&AMorrowBone::StaticCameraStopped);
	}

}

