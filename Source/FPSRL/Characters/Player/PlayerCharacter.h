// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FPSRL/Interfaces/Health.h"
#include "PlayerCharacter.generated.h"

class UCameraComponent;
class UGunArm;
class AGunUpgradeModule;
class UPlayerHUD;
class UHealthComponent;

UCLASS()

class FPSRL_API APlayerCharacter : public ACharacter, public IHealth
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();
	virtual void Die() override;

	void Shoot();
	void Interact();
	void ApplyGunUpgrade(AGunUpgradeModule* upgrade);

	void UpdateHealthBar(int health, int maxHealth);
	void UpdateChargeBar(float charge, float maxCharge);

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
	UPROPERTY(EditAnywhere)
	int _baseMaxHealth;
	UPROPERTY(EditAnywhere)
	TObjectPtr<UCameraComponent> _camera;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UGunArm> _gunArm;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UPlayerHUD> _playerHUDDefault;

	UPlayerHUD* _playerHUD;
};
