// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

class UPlayerHUD;

DECLARE_DELEGATE_TwoParams(FOnHealthUpdated, float, float);
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FPSRL_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();

	void Init(int baseMaxHealth);
	void BindOnHealthUpdated(UPlayerHUD* playerHUD);

	int GetHealth();
	void AdjustHealth(int toAdd);

	int GetMaxHealth();
	void AdjustMaxHealth(int toAdd);
	// Called every frame
	//virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
protected:
	// Called when the game starts
	//virtual void BeginPlay() override;

private: 
	FOnHealthUpdated onHealthUpdated;

	UPROPERTY(EditAnywhere)
	int _baseMaxHealth;
	int _maxHealth;

	int _health;
};
