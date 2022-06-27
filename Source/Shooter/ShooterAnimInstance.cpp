// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAnimInstance.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "PrintStrings.h"
#include "ShooterCharacter.h"

const float ANGLE_FLAP_LIMIT = 150.f;

void UShooterAnimInstance::NativeInitializeAnimation()
{
	ShooterCharacter = Cast<AShooterCharacter>(TryGetPawnOwner());
}

void UShooterAnimInstance::UpdateAnimationProperties(float DeltaTime)
{
	if (ShooterCharacter == nullptr)
	{
		ShooterCharacter = Cast<AShooterCharacter>(TryGetPawnOwner());
	}

	if (ShooterCharacter == nullptr) return;
	
	// Get the lateral speed of the character from velocity
	FVector Velocity{ ShooterCharacter->GetVelocity() };
	Velocity.Z = 0;
	Speed = Velocity.Size();

	// Is the character in the air?
	bInAir = ShooterCharacter->GetCharacterMovement()->IsFalling();

	// Is the character accelerating?
	bAccelerating = ShooterCharacter->GetCharacterMovement()->GetCurrentAcceleration().Size() > 0.f ? true : false;

	FRotator AimRotation = ShooterCharacter->GetBaseAimRotation();
	FRotator MovementRotation = UKismetMathLibrary::MakeRotFromX(ShooterCharacter->GetVelocity());

	float NewMovementOffsetYaw = UKismetMathLibrary::NormalizedDeltaRotator(MovementRotation, AimRotation).Yaw;
	MovementOffsetYaw = CheckOffsetFlap(LastMovementOffsetYaw, NewMovementOffsetYaw);
	
	/** Update only when received players input */
	if (ShooterCharacter->IsReceivingMoveInput())
	{
		LastMovementOffsetYaw = MovementOffsetYaw;
		LastSpeed = Speed;
	}
/*
	printf(1, "Base Aim Rotation: %f", AimRotation.Yaw);
	printf(2, "Movement Rotation: %f", MovementRotation.Yaw);
	printf(3, "Movement Offset: %f", MovementOffsetYaw);
	printf(4, "LastMovement Offset: %f", LastMovementOffsetYaw);
	printf(5, "Last Speed: %f", LastSpeed);
*/
}

float UShooterAnimInstance::CheckOffsetFlap(float LastMovementOffset, float NewMovementOffset)
{
	if ((LastMovementOffset < -ANGLE_FLAP_LIMIT && NewMovementOffset > 0.f)
		|| (LastMovementOffset > ANGLE_FLAP_LIMIT && NewMovementOffset < 0.f)
		)
	{
		return LastMovementOffset;
	}
	else
	{
		return NewMovementOffset;
	}
}
