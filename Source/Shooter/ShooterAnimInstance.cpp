// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAnimInstance.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "PrintStrings.h"
#include "ShooterCharacter.h"

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
}
