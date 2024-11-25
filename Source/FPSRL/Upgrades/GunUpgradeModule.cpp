// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSRL/Upgrades/GunUpgradeModule.h"
#include "FPSRL/Characters/Player/PlayerCharacter.h"
#include "FPSRL/Data/GunStats.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"

// Sets default values
AGunUpgradeModule::AGunUpgradeModule()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	_moduleStats = CreateDefaultSubobject<UGunStats>(TEXT("Module Stats"));

	_staticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	checkf(_staticMesh, TEXT("No Static Mesh on Upgrade Module"));
	_staticMesh->SetCollisionProfileName(FName("Interactable"));
	_staticMesh->SetupAttachment(RootComponent);
}

UGunStats* AGunUpgradeModule::GetModuleStats()
{
	return _moduleStats;
}

// Called when the game starts or when spawned
void AGunUpgradeModule::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGunUpgradeModule::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGunUpgradeModule::Interact(APlayerCharacter* interactedBy)
{
	interactedBy->ApplyGunUpgrade(this);
	Destroy();
}

