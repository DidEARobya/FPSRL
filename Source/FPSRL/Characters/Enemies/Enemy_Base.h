// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FPSRL/Interfaces/Health.h"
#include "Enemy_Base.generated.h"

class AAIController;
class UStaticMeshComponent;
class UHealthComponent;
class UCharacterMovementComponent;
class APlayerCharacter;
class UCapsuleComponent;

UCLASS()
class FPSRL_API AEnemy_Base : public ACharacter, public IHealth
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AEnemy_Base();
	virtual void Die() override;
	void SetTarget(AActor* target);
	// Called every frame
	virtual void Tick(float DeltaTime) override;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

protected:

	UPROPERTY(EditAnywhere)
	AAIController* _controller;
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* _staticMesh;
	UCapsuleComponent* _collisionMesh;

	UCharacterMovementComponent* _movementComponent;
	AActor* _target;
	APlayerCharacter* _player;
private:
	UPROPERTY(EditAnywhere)
	int _baseMaxHealth;
	UPROPERTY(EditAnywhere)
	int _baseSpeed;
};
