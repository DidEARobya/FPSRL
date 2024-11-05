// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSRL/Characters/Player/PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "FPSRL/Components/GunArm.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	_camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Player Camera"));
	checkf(_camera, TEXT("PLAYER_CAMERA is an invalid value"));

    _camera->SetupAttachment(RootComponent);
	_camera->bUsePawnControlRotation = true;
}
void APlayerCharacter::Shoot()
{
	_gunArm->Fire(_camera->GetForwardVector());
}
// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	_gunArm = GetComponentByClass<UGunArm>();
	checkf(_gunArm, TEXT("Gun arm not found"));
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

