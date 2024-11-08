// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSRL/Characters/Player/PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "FPSRL/Characters/Player/FPSRLPlayerControllerBase.h"
#include "FPSRL/Components/GunArm.h"
#include "FPSRL/Upgrades/GunUpgradeModule.h"
#include "FPSRL/UI/PlayerHUD.h"
#include "Blueprint/UserWidget.h"

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
void APlayerCharacter::Interact()
{
	FVector start = _camera->GetComponentLocation();
	FVector end = start + _camera->GetForwardVector() * 500.0f;

	FHitResult hit;
	FCollisionQueryParams params;
	params.AddIgnoredActor(this);
	DrawDebugLine(GetWorld(), start, end, FColor::Green, true);
	if (GetWorld()->LineTraceSingleByChannel(hit, start, end, ECollisionChannel::ECC_GameTraceChannel1, params))
	{
		
		if (hit.GetActor() == nullptr)
		{
			return;
		}

		GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Red, FString::Printf(TEXT("Interact Target: %s"), *hit.GetActor()->GetName()));

		if (IInteractable* interact = Cast<IInteractable>(hit.GetActor()))
		{
			
			interact->Interact(this);
		}
	}
}
void APlayerCharacter::ApplyGunUpgrade(AGunUpgradeModule* upgrade)
{
	_gunArm->ApplyUpgrade(upgrade);
}
void APlayerCharacter::UpdateChargeBar(float charge)
{
	_playerHUD->SetGunCharge(charge);
}
// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (_playerHUDDefault == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Player HUD not found"));
		return;
	}

	_playerHUD = CreateWidget<UPlayerHUD>(GetController<AFPSRLPlayerControllerBase>(), _playerHUDDefault);
	checkf(_playerHUD, TEXT("Failed to Create HUD"));
	_playerHUD->AddToPlayerScreen();

	_gunArm = GetComponentByClass<UGunArm>();
	checkf(_gunArm, TEXT("Gun arm not found"));
	_gunArm->BindOnChargeUpdated(_playerHUD);

	_playerHUD->SetGunMaxCharge(_gunArm->Gun_MaxCharge);
}

void APlayerCharacter::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	_playerHUD->RemoveFromParent();
	_playerHUD = nullptr;

	Super::EndPlay(EndPlayReason);
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

