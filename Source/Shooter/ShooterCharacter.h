// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ShooterCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;

UCLASS()
class SHOOTER_API AShooterCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AShooterCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:

protected:
	/** Called for forwards/backwards inputs */
	void MoveForward(float Value);

	/** Called for side to side inputs */
	void MoveRight(float Value);

	/**
	 * Called via input to turn at a given rate
	 * @param Rate This is a normalized rate, 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to look up/down at a given rate
	 * @param Rate This is a normalized rate, 1.0 means 100% of desired look up/down rate
	 */
	void LookUpAtRate(float Rate);

	/** Called when Fire button is pressed */
	void FireWeapon();

private:
	// COMPONENTS
	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Camera that follows the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;

	// VARIABLES
	/** Base turn rate in deg/s. Other scaling may affect final turn rate */
	UPROPERTY(Category = "Camera", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float BaseTurnRate;

	/** Base look up/down rate in deg/s. Other scaling may affect final turn rate */
	UPROPERTY(Category = "Camera", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float BaseLookUpRate;
};
