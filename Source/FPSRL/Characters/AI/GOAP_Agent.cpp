// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSRL/Characters/AI/GOAP_Agent.h"
#include "FPSRL/Characters/AI/BeliefFactory.h"
#include "FPSRL/Characters/AI/GOAP_Action.h"
#include "FPSRL/Characters/AI/GOAP_Goal.h"
#include "FPSRL/Characters/AI/GOAP_Planner.h"
#include "FPSRL/Characters/AI/GOAP_Plan.h"
#include "FPSRL/Characters/Enemies/Enemy_Base.h"
#include "FPSRL/Characters/AI/Strategies/ChaseStrategy.h"
#include "FPSRL/Characters/AI/Strategies/AttackStrategy.h"
#include "DrawDebugHelpers.h"

// Sets default values for this component's properties
UGOAP_Agent::UGOAP_Agent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UGOAP_Agent::SetupBeliefs()
{
	_beliefs = new TMap<FString, GOAP_Belief*>();

	BeliefFactory factory = BeliefFactory(_beliefs);

	factory.AddBelief(TEXT("Seek"), [] { return false; });
	factory.AddBelief(TEXT("Attack"), [&] { return !isInTargetRange; });
}

void UGOAP_Agent::SetupActions()
{
	_actions = new TArray<GOAP_Action*>();

	_actions->Add(GOAP_Action::Builder(TEXT("Seek")).WithStrategy(new ChaseStrategy(this)).AddEffect(_beliefs->FindChecked(TEXT("Seek"))).Build());
	_actions->Add(GOAP_Action::Builder(TEXT("Attack")).WithStrategy(new AttackStrategy(this)).AddEffect(_beliefs->FindChecked(TEXT("Attack"))).Build());
}

void UGOAP_Agent::SetupGoals()
{
	_goals = new TArray<GOAP_Goal*>();

	_goals->Add(GOAP_Goal::Builder(TEXT("Seek")).WithPriority(1).AddDesiredEffect(_beliefs->FindChecked(TEXT("Seek"))).Build());
	_goals->Add(GOAP_Goal::Builder(TEXT("Attack")).WithPriority(5).AddDesiredEffect(_beliefs->FindChecked(TEXT("Attack"))).Build());
}
void UGOAP_Agent::SetOwnerTarget(AActor* target)
{
	if (target == nullptr)
	{
		_owner->SetTarget(target);
		return;
	}

	_owner->SetTarget(target);
	_target = target;
}
void UGOAP_Agent::CalculateActionPlan()
{
	int priorityLevel = (_currentGoal != nullptr) ? _currentGoal->_priority : 0;

	TArray<GOAP_Goal*> goalsToCheck;

	if (_currentGoal != nullptr)
	{
		goalsToCheck = _goals->FilterByPredicate([&](const GOAP_Goal* index) { return index->_priority > priorityLevel; });
	}
	else
	{
		goalsToCheck = *_goals;
	}

	GOAP_Plan* potentialPlan = _planner->Plan(this, _goals, nullptr);

	if (potentialPlan != nullptr)
	{
		_plan = potentialPlan;
	}
}

 
// Called when the game starts
void UGOAP_Agent::BeginPlay()
{
	Super::BeginPlay();

	_owner = Cast<AEnemy_Base>(GetOwner());
	checkf(_owner, TEXT("GOAP_Agent Owner Not Found"));

	SetupBeliefs();
	SetupActions();
	SetupGoals();
	
	
	_planner = new GOAP_Planner();
}


// Called every frame
void UGOAP_Agent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (_currentAction == nullptr)
	{
		CalculateActionPlan();

		if (_plan != nullptr && _plan->actions->Num() > 0)
		{
			_currentGoal = _plan->goal;
			_currentAction = _plan->actions->Pop();

			GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Red, FString::Printf(TEXT("%s has started"), *_currentAction->_name));
			_currentAction->Start();
		}
	}

	if (_plan != nullptr && _currentAction != nullptr)
	{
		_currentAction->Update(DeltaTime);

		if (_currentAction->IsComplete() == true)
		{
			_currentAction->Stop();
			_currentAction = nullptr;

			if (_plan->actions->Num() == 0)
			{
				_lastGoal = _currentGoal;
				_currentGoal = nullptr;
			}
		}
	}
}

