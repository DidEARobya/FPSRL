// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSRL/Characters/Player/FPSRLPlayerControllerBase.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "FPSRL/Characters/Player/PlayerCharacter.h"

void AFPSRLPlayerControllerBase::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);

	m_playerCharacter = Cast<APlayerCharacter>(aPawn);
	checkf(m_playerCharacter, TEXT("PLAYER_CHARACTER is an invalid value"));

	m_movementComponent = m_playerCharacter->GetCharacterMovement();
	checkf(m_movementComponent, TEXT("MOVEMENT_COMPONENT is an invalid value"));

	m_enhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
	checkf(m_enhancedInputComponent, TEXT("ENHANCED_INPUT_COMPONENT is an invalid value"));

	UEnhancedInputLocalPlayerSubsystem* inputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	checkf(inputSubsystem, TEXT("INPUT_SUBSYSTEM is an invalid value"));

	checkf(inputMappingContext, TEXT("INPUT_MAPPING_CONTEXT is an invalid value"));
	inputSubsystem->ClearAllMappings();
	inputSubsystem->AddMappingContext(inputMappingContext, 0);

	BindActions(m_enhancedInputComponent);
}

void AFPSRLPlayerControllerBase::OnUnPossess()
{
	m_enhancedInputComponent->ClearActionBindings();

	Super::OnUnPossess();
}

void AFPSRLPlayerControllerBase::HandleLook(const struct FInputActionValue& value)
{
	const FVector2D lookAxisVector = value.Get<FVector2D>();

	AddYawInput(lookAxisVector.X);
	AddPitchInput(lookAxisVector.Y);
}

void AFPSRLPlayerControllerBase::HandleMove(const struct FInputActionValue& value)
{
	const FVector movementVector = value.Get<FVector>();

	m_playerCharacter->AddMovementInput(m_playerCharacter->GetActorForwardVector(), movementVector.Y);
	m_playerCharacter->AddMovementInput(m_playerCharacter->GetActorRightVector(), movementVector.X);
}

void AFPSRLPlayerControllerBase::HandleJump()
{
	m_playerCharacter->UnCrouch();
	m_playerCharacter->Jump();
}

void AFPSRLPlayerControllerBase::BindActions(UEnhancedInputComponent* inputComponent)
{
	if (actionMove != nullptr)
	{
		inputComponent->BindAction(actionMove, ETriggerEvent::Triggered, this, &AFPSRLPlayerControllerBase::HandleMove);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No Move Action"));
	}

	if (actionLook != nullptr)
	{
		inputComponent->BindAction(actionLook, ETriggerEvent::Triggered, this, &AFPSRLPlayerControllerBase::HandleLook);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No Look Action"));
	}

	if (actionJump != nullptr)
	{
		inputComponent->BindAction(actionJump, ETriggerEvent::Triggered, this, &AFPSRLPlayerControllerBase::HandleJump);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No Jump Action"));
	}
}

