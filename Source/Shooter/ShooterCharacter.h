// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ShooterCharacter.generated.h"

class UAnimMontage;
class UCameraComponent;
class UParticleSystem;
class USpringArmComponent;
class USoundCue;

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

	/** Is Player pressing keys for movement */
	FORCEINLINE bool IsReceivingMoveInput() { return bReceivingMoveInput; }

	FORCEINLINE bool GetAiming() const { return bAiming; }

protected:
	FORCEINLINE UCameraComponent* GetFollowCamera() { return FollowCamera; }

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

	/**
	 * Rotate controller based on mouse Y movement
	 * @param Value The input value from mouse movement
	 */
	void Turn(float Value);

	/**
	 * Rotate controller based on mouse X movement
	 * @param Value The input value from mouse movement
	 */
	void LookUp(float Value);

	/** Called when Fire button is pressed */
	void FireWeapon();

	bool GetBeamEndLocation(const FVector& MuzzleSocketLocation, FVector& OutBeamEndLocation);

	/** Set bAiming to true or false with button press */
	void AimingButtonPressed();
	void AimingButtonReleased();

	void CameraInterpZoom(float DeltaTime);

	/** Set BaseTurnRates and BaseLookUpRates based on aiming */
	void SetLookRates();

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

	/** Turn rate when not aiming */
	UPROPERTY(Category = "Camera", EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float HipTurnRate;

	/** Look up rate when not aiming */
	UPROPERTY(Category = "Camera", EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float HipLookUpRate;

	/** Turn rate when aiming */
	UPROPERTY(Category = "Camera", EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float AimingTurnRate;

	/** Look up rate when aiming */
	UPROPERTY(Category = "Camera", EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float AimingLookUpRate;

	/** Scale factor for mouse look sensitivity. Turn rate when not aiming */
	UPROPERTY(Category = "Camera", EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))
	float MouseHipTurnRate;

	/** Scale factor for mouse look sensitivity. Look up rate when not aiming */
	UPROPERTY(Category = "Camera", EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))
	float MouseHipLookUpRate;

	/** Scale factor for mouse look sensitivity. Turn rate when aiming */
	UPROPERTY(Category = "Camera", EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))
	float MouseAimingTurnRate;

	/** Scale factor for mouse look sensitivity. Look up rate when aiming */
	UPROPERTY(Category = "Camera", EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))
	float MouseAimingLookUpRate;

	/** Player is pressing keys for movement */
	UPROPERTY(Category = "Movement", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	bool bReceivingMoveInput;

	/** Randomized gunshot sound cue */
	UPROPERTY(Category = "Combat", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	USoundCue* FireSound;

	/** Flash spawned at BarrelSocket */
	UPROPERTY(Category = "Combat", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UParticleSystem* MuzzleFlash;

	/** Montage for firing the weapon */
	UPROPERTY(Category = "Combat", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UAnimMontage* HipFireMontage;

	/** Particles spawned upon bullets impact */
	UPROPERTY(Category = "Combat", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UParticleSystem* ImpactParticles;

	/** Smoke trail for bullets */
	UPROPERTY(Category = "Combat", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UParticleSystem* BeamParticles;

	/** True when aiming */
	UPROPERTY(Category = "Combat", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	bool bAiming;

	/** Default camera field of view value */
	float CameraDefaultFOV;

	/** Field of view value for when zoomed in */
	float CameraZoomedFOV;

	/** Current field of view this frame */
	float CameraCurrentFOV;

	/** Interp speed for zooming when aiming */
	UPROPERTY(Category = "Combat", EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float ZoomInterpSpeed;
};
