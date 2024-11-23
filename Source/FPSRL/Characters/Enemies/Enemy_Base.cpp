// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSRL/Characters/Enemies/Enemy_Base.h"
#include "FPSRL/Characters/AI/GOAP_Action.h"
#include "FPSRL/Characters/AI/GOAP_Agent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "FPSRL/Components/HealthComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "AIController.h"
#include "Navigation/PathFollowingComponent.h"

// Sets default values
AEnemy_Base::AEnemy_Base()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	_staticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	checkf(_staticMesh, TEXT("No Static Mesh on Upgrade Module"));
	_staticMesh->SetCollisionProfileName(FName("NoCollision"));
	_staticMesh->SetupAttachment(RootComponent);

	_healthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health Component"));
	checkf(_healthComponent, TEXT("Player Health component is in an invalid value"));

	_collisionMesh = GetCapsuleComponent();
	checkf(_collisionMesh, TEXT("Collision Mesh is in invalid value"));
	_collisionMesh->SetCollisionProfileName(FName("Enemy"));

	_agent = CreateDefaultSubobject<UGOAP_Agent>(TEXT("GOAP_Agent"));
	checkf(_agent, TEXT("Failed to Create GOAP_Agent"));
	_agent->Init();

}

void AEnemy_Base::Die()
{
	Destroy();
}

void AEnemy_Base::SetDestination(FVector destination)
{
	FAIMoveRequest moveTo;
	moveTo.SetAcceptanceRadius(10);
	moveTo.SetGoalLocation(destination);

	_controller->MoveTo(moveTo);
}

bool AEnemy_Base::HasPath()
{
	return 	_controller->IsFollowingAPath();
}

// Called when the game starts or when spawned
void AEnemy_Base::BeginPlay()
{
	Super::BeginPlay();

	_healthComponent->Init(_baseMaxHealth);
	_controller = Cast<AAIController>(GetController());
	_movementComponent = Cast<UCharacterMovementComponent>(GetMovementComponent());
	_movementComponent->MaxWalkSpeed = _baseSpeed;
}

// Called every frame
void AEnemy_Base::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

