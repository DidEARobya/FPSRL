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
class UCapsuleComponent;
class UGOAP_Agent;

UCLASS()
class FPSRL_API AEnemy_Base : public ACharacter, public IHealth
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AEnemy_Base();

	virtual void Die() override;
	void SetDestination(FVector destination);
	bool HasPath();

	// Called every frame
	virtual void Tick(float DeltaTime) override;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditAnywhere)
	TObjectPtr<UGOAP_Agent> _agent;
	UPROPERTY(EditAnywhere)
	TObjectPtr<AAIController> _controller;
	UPROPERTY(EditAnywhere)
	TObjectPtr<UStaticMeshComponent> _staticMesh;
	TObjectPtr<UCapsuleComponent> _collisionMesh;

	TObjectPtr<UCharacterMovementComponent> _movementComponent;
private:
	UPROPERTY(EditAnywhere)
	int _baseMaxHealth;
	UPROPERTY(EditAnywhere)
	int _baseSpeed;
};
