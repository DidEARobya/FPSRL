// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSRL/Characters/Player/PlayerCharacter.h"
#include "Camera/CameraComponent.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Player Camera"));
	checkf(m_camera, TEXT("PLAYER_CAMERA is an invalid value"));

	m_camera->SetupAttachment(RootComponent);
	m_camera->bUsePawnControlRotation = true;
}
// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
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

