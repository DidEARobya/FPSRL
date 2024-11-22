// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GOAP_Agent.generated.h"

class GOAP_Belief;
class GOAP_Goal;
class GOAP_Planner;
class GOAP_Action;
class GOAP_Plan;
class AEnemy_Base;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FPSRL_API UGOAP_Agent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGOAP_Agent();
	void SetupBeliefs();
	void SetupGoals();
	void SetupActions();
	
	void SetOwnerTarget(AActor* target);
	void CalculateActionPlan();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	AActor* _target;
	AEnemy_Base* _owner;
	
	TMap<FString, GOAP_Belief*>* _beliefs;

	GOAP_Goal* _currentGoal;
	GOAP_Goal* _lastGoal;

	GOAP_Plan* _plan;
	GOAP_Action* _currentAction;

	TArray<GOAP_Action*>* _actions;
	TArray<GOAP_Goal*>* _goals;

	GOAP_Planner* _planner;

	bool isInTargetRange;
};
