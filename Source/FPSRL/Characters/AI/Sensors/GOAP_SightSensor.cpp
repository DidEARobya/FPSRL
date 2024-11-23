// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSRL/Characters/AI/Sensors/GOAP_SightSensor.h"
#include "FPSRL/Characters/AI/GOAP_Agent.h"

// Sets default values for this component's properties
UGOAP_SightSensor::UGOAP_SightSensor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UGOAP_SightSensor::Init(TObjectPtr<UGOAP_Agent> agent)
{
	_agent = agent;
}

void UGOAP_SightSensor::SetTarget(TObjectPtr<AActor> target)
{
	_target = target;
}


// Called when the game starts
void UGOAP_SightSensor::BeginPlay()
{
	Super::BeginPlay();

	_timer = _scanInterval;
}

void UGOAP_SightSensor::Scan()
{
	FVector dir = _target->GetActorLocation() - _agent->GetActorLocation();

	if (dir.Length() > _distance)
	{
		_agent->_hasLineOfSight = false;
		return;
	}

	dir.Normalize();

	FVector forward = _agent->GetForwardVector();

	if (forward.Dot(dir) < (1 - _fov))
	{
		_agent->_hasLineOfSight = false;
		return;
	}

	FHitResult hit;
	FCollisionQueryParams params;
	params.AddIgnoredActor(GetOwner());

	DrawDebugLine(GetWorld(), _agent->GetActorLocation(), _target->GetActorLocation(), FColor::Green, true);

	if (GetWorld()->LineTraceSingleByChannel(hit, _agent->GetActorLocation(), _target->GetActorLocation(), ECC_Visibility, params))
	{
		GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Red, FString::Printf(TEXT("Sight: %s"), hit.GetActor() ? *hit.GetActor()->GetName() : TEXT("Nothing")));

		if (hit.GetActor() == nullptr || hit.GetActor() != _target)
		{
			_agent->_hasLineOfSight = false;
			return;
		}

		_agent->_hasLineOfSight = true;
	}
}


// Called every frame
void UGOAP_SightSensor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (_target == nullptr)
	{
		return;
	}

	_timer += DeltaTime;

	if (_timer >= _scanInterval)
	{
		Scan();
		_timer = 0;
	}
}

