// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSRL/Components/HealthComponent.h"
#include "FPSRL/UI/PlayerHUD.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

void UHealthComponent::Init(int baseMaxHealth)
{
	_baseMaxHealth = baseMaxHealth;
	_maxHealth = _baseMaxHealth;
	_health = _maxHealth;
}

void UHealthComponent::BindOnHealthUpdated(UPlayerHUD* playerHUD)
{
	onHealthUpdated.BindUObject(playerHUD, &UPlayerHUD::SetHealth);
}

int UHealthComponent::GetHealth()
{
	return _health;
}

void UHealthComponent::AdjustHealth(int toAdd)
{
	_health = FMath::Clamp(_health + toAdd, 0, _maxHealth);
	onHealthUpdated.ExecuteIfBound(_health, _maxHealth);
}

int UHealthComponent::GetMaxHealth()
{
	return _maxHealth;
}

void UHealthComponent::AdjustMaxHealth(int toAdd)
{
	_maxHealth += toAdd;
	onHealthUpdated.ExecuteIfBound(_health, _maxHealth);
}


/*
// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}*/








/*
// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}*/

