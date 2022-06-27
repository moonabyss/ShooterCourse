// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "ShooterAnimInstance.generated.h"

class AShooterCharacter;

/**
 * 
 */
UCLASS()
class SHOOTER_API UShooterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeInitializeAnimation() override;

	/** Update parameters every frame */
	UFUNCTION(BlueprintCallable)
	void UpdateAnimationProperties(float DeltaTime);

private:
	UPROPERTY(Category = "Movement", BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	AShooterCharacter* ShooterCharacter;

	/** The speed of the Character */
	UPROPERTY(Category = "Movement", BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float Speed;

	/** Whether or not the character is in the air */
	UPROPERTY(Category = "Movement", BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	bool bInAir;

	/** Whether or not the character is moving */
	UPROPERTY(Category = "Movement", BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	bool bAccelerating;

	/** Offset yaw used for strafing */
	UPROPERTY(Category = "Movement", BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float MovementOffsetYaw;

	/** Offset yaw the frame before we stopped moving */
	UPROPERTY(Category = "Movement", BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float LastMovementOffsetYaw;

	/** Speed before we stopped movement */
	UPROPERTY(Category = "Movement", BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float LastSpeed;
};
