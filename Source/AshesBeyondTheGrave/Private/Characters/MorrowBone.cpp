


#include "Characters/MorrowBone.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Animation/AnimInstance.h"

AMorrowBone::AMorrowBone()
{
 	
	PrimaryActorTick.bCanEverTick = true;
	Capsule = GetCapsuleComponent();
	Skeleton = GetMesh();
	
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
			SubSystem->AddMappingContext(MappingContext, 0);
			
		}
	}
	StartMontage();
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

	
	if (Controller)
	{
		const FVector2D MovementVector = value.Get<FVector2D>();
		const FRotator Rotation = Controller->GetControlRotation();

		FRotator YawRotataion(0.f, Rotation.Yaw, 0.f);

		const FVector ForwardVector = FRotationMatrix(YawRotataion).GetUnitAxis(EAxis::X);
		AddMovementInput(ForwardVector, MovementVector.Y);
		const FVector RightVector = FRotationMatrix(YawRotataion).GetUnitAxis(EAxis::Y);
		AddMovementInput(RightVector, MovementVector.X);
	}
}

void AMorrowBone::Looking(const FInputActionValue& value)
{
	if (GetController())
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
	TObjectPtr<UAnimInstance> AnimInstance=GetMesh()->GetAnimInstance();
	if (IsValid(AnimInstance) && !LightAttackMontage.IsEmpty())
	{
		int32 Montage_Number= FMath::RandRange(0,LightAttackMontage.Num()-1);

		AnimInstance->Montage_Play(LightAttackMontage[Montage_Number]);
	}
	
}


void AMorrowBone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void AMorrowBone::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	UEnhancedInputComponent* PlayerComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);
	if (PlayerComponent)
	{
		PlayerComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMorrowBone::Moving);
			PlayerComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AMorrowBone::Looking);
			PlayerComponent->BindAction(SprintAction, ETriggerEvent::Started,this,&AMorrowBone::StartSprinting);
			PlayerComponent->BindAction(SprintAction, ETriggerEvent::Completed, this, &AMorrowBone::EndSprinting);
			PlayerComponent->BindAction(SprintAction, ETriggerEvent::Triggered, this, &AMorrowBone::RunSprinting);
			PlayerComponent->BindAction(JumpAction,ETriggerEvent::Triggered,this,&ACharacter::Jump);
		    PlayerComponent->BindAction(LightAttackAction,ETriggerEvent::Triggered,this,&AMorrowBone::LightAttacks);
	}

}

