#include "Health.h"
// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSRL/Interfaces/Health.h"
#include "FPSRL/Components/HealthComponent.h"

// Add default functionality here for any IHealth functions that are not pure virtual.
void IHealth::AdjustHealth(int toAdd)
{
	_healthComponent->AdjustHealth(toAdd);
	GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Red, FString::Printf(TEXT("Current Health: %i"), _healthComponent->GetHealth()));

	if (_healthComponent->GetHealth() <= 0)
	{
		Die();
	}
}

void IHealth::Die()
{
}
