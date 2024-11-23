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
#include "FPSRL/Characters/AI/Strategies/PatrolStrategy.h"
#include "FPSRL/Characters/AI/Sensors/GOAP_TargetSensor.h"
#include "FPSRL/Characters/AI/Sensors/GOAP_SightSensor.h"
#include "FPSRL/Characters/Player/PlayerCharacter.h"
#include "Components/SphereComponent.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UGOAP_Agent::UGOAP_Agent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	_isInTargetRange = false;
	_hasLineOfSight = false;

	_playerSensor = CreateDefaultSubobject<UGOAP_TargetSensor>(TEXT("Player Sensor"));
	checkf(_playerSensor, TEXT("Failed to Create Target Sensor"));

	_sightSensor = CreateDefaultSubobject<UGOAP_SightSensor>(TEXT("Sight Sensor"));
	checkf(_sightSensor, TEXT("Failted to Create Sight Sensor"));
}

void UGOAP_Agent::Init()
{
	_owner = Cast<AEnemy_Base>(GetOwner());
	checkf(_owner, TEXT("GOAP_Agent Owner Not Found"));

	_playerSensor->_sensor->SetupAttachment(_owner->GetRootComponent());
}

void UGOAP_Agent::SetupBeliefs()
{
	_beliefs = new TMap<FString, GOAP_Belief*>();

	BeliefFactory factory = BeliefFactory(_beliefs);

	factory.AddBelief(TEXT("PATROL"), [&] { return _hasLineOfSight; });
	factory.AddBelief(TEXT("SEEK"), [&] { return !_hasLineOfSight; });
	factory.AddBelief(TEXT("ATTACK"), [&] { return !_isInTargetRange; });
}

void UGOAP_Agent::SetupActions()
{
	_actions = new TArray<GOAP_Action*>();

	_actions->Add(GOAP_Action::Builder(TEXT("PATROL")).WithStrategy(new PatrolStrategy(this)).AddEffect(_beliefs->FindChecked(TEXT("PATROL"))).Build());
	_actions->Add(GOAP_Action::Builder(TEXT("SEEK")).WithStrategy(new ChaseStrategy(this)).AddEffect(_beliefs->FindChecked(TEXT("SEEK"))).Build());
	_actions->Add(GOAP_Action::Builder(TEXT("ATTACK")).WithStrategy(new AttackStrategy(this)).AddEffect(_beliefs->FindChecked(TEXT("ATTACK"))).Build());
}

void UGOAP_Agent::SetupGoals()
{
	_goals = new TArray<GOAP_Goal*>();

	_goals->Add(GOAP_Goal::Builder(TEXT("PATROL")).WithPriority(1).AddDesiredEffect(_beliefs->FindChecked(TEXT("PATROL"))).Build());
	_goals->Add(GOAP_Goal::Builder(TEXT("SEEK")).WithPriority(3).AddDesiredEffect(_beliefs->FindChecked(TEXT("SEEK"))).Build());
	_goals->Add(GOAP_Goal::Builder(TEXT("ATTACK")).WithPriority(5).AddDesiredEffect(_beliefs->FindChecked(TEXT("ATTACK"))).Build());
}
void UGOAP_Agent::SetDestination(FVector destination)
{
	_owner->SetDestination(destination);
}
FVector UGOAP_Agent::GetActorLocation()
{
	return _owner->GetActorLocation();
}
FVector UGOAP_Agent::GetForwardVector()
{
	return _owner->GetActorForwardVector();
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

bool UGOAP_Agent::HasPath()
{
	return _owner->HasPath();
}

 
// Called when the game starts
void UGOAP_Agent::BeginPlay()
{
	Super::BeginPlay();
	_playerSensor->Init(attackRange, this);
	_sightSensor->Init(this);

	SetupBeliefs();
	SetupActions();
	SetupGoals();
	
	_planner = new GOAP_Planner();
	_player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerPawn(_owner->GetWorld(), 0));

	_playerSensor->SetTarget(_player);
	_sightSensor->SetTarget(_player);
}


// Called every frame
void UGOAP_Agent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	GEngine->AddOnScreenDebugMessage(0, 1, FColor::Red, FString::Printf(TEXT("Current Action: %s"), _currentAction ? *_currentAction->_name : TEXT("NONE")));
	GEngine->AddOnScreenDebugMessage(1, 1, FColor::Red, FString::Printf(TEXT("TargetInRange: %s "), _isInTargetRange ? TEXT("TRUE") : TEXT("FALSE")));
	GEngine->AddOnScreenDebugMessage(2, 1, FColor::Red, FString::Printf(TEXT("LineOfSight: %s"), _hasLineOfSight ? TEXT("TRUE") : TEXT("FALSE")));
	GEngine->AddOnScreenDebugMessage(3, 1, FColor::Red, FString::Printf(TEXT("IsAttacking: %s"), _isAttacking ? TEXT("TRUE") : TEXT("FALSE")));

	if (_currentAction == nullptr)
	{
		CalculateActionPlan();

		if (_plan != nullptr && _plan->actions->Num() > 0)
		{
			_currentGoal = _plan->goal;
			_currentAction = _plan->actions->Pop();


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

