// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSRL/Characters/AI/Sensors/GOAP_TargetSensor.h"
#include "FPSRL/Characters/AI/GOAP_Agent.h"
#include "Components/SphereComponent.h"

// Sets default values for this component's properties
UGOAP_TargetSensor::UGOAP_TargetSensor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	_sensor = CreateDefaultSubobject<USphereComponent>(TEXT("Sensor"));
	checkf(_sensor, TEXT("Failed to create Sensor Collider"));
}

void UGOAP_TargetSensor::Init(float radius, TObjectPtr<UGOAP_Agent> agent)
{
	_sensor->SetSphereRadius(radius);

	_agent = agent;
	_radius = radius;
}

void UGOAP_TargetSensor::SetTarget(TObjectPtr<AActor> target)
{
	_target = target;
}

void UGOAP_TargetSensor::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == _target)
	{
		_agent->_isInTargetRange = true;
	}
}

void UGOAP_TargetSensor::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor == _target)
	{
		_agent->_isInTargetRange = false;
	}
}

// Called when the game starts
void UGOAP_TargetSensor::BeginPlay()
{
	Super::BeginPlay();

	_sensor->OnComponentBeginOverlap.AddDynamic(this, &UGOAP_TargetSensor::BeginOverlap);
	_sensor->OnComponentEndOverlap.AddDynamic(this, &UGOAP_TargetSensor::EndOverlap);
}

void UGOAP_TargetSensor::Scan()
{
}

// Called every frame
void UGOAP_TargetSensor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

