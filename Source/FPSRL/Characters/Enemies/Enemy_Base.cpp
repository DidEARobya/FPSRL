// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSRL/Characters/Enemies/Enemy_Base.h"
#include "Components/StaticMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "FPSRL/Components/HealthComponent.h"
#include "FPSRL/Characters/Player/PlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
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

}

void AEnemy_Base::Die()
{
	Destroy();
}

// Called when the game starts or when spawned
void AEnemy_Base::BeginPlay()
{
	Super::BeginPlay();

	_healthComponent->Init(_baseMaxHealth);
	_controller = Cast<AAIController>(GetController());
	_player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	_movementComponent = Cast<UCharacterMovementComponent>(GetMovementComponent());
	_movementComponent->MaxWalkSpeed = _baseSpeed;
}

// Called every frame
void AEnemy_Base::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (_controller != nullptr && _player != nullptr)
	{
		FAIMoveRequest moveTo;
		moveTo.SetAcceptanceRadius(10);
		moveTo.SetGoalActor(_player);

		_controller->MoveTo(moveTo);
	}
}

