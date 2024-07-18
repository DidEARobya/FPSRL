// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "FPSRLPlayerControllerBase.generated.h"

class UInputMappingContext;
class UEnhancedInputComponent;
class UInputAction;
class UCharacterMovementComponent;
class APlayerCharacter;

UCLASS(Abstract)

class FPSRL_API AFPSRLPlayerControllerBase : public APlayerController
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Input | Character Movement")
	TObjectPtr<UInputAction> actionMove;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Input | Character Movement")
	TObjectPtr<UInputAction> actionLook;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Input | Character Movement")
	TObjectPtr<UInputAction> actionJump;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Input | Character Movement")
	TObjectPtr<UInputMappingContext> inputMappingContext;

protected:
	void HandleLook(const struct FInputActionValue& value);
	void HandleMove(const struct FInputActionValue& value);
	void HandleJump();

	virtual void OnPossess(APawn* aPawn) override;
	virtual void OnUnPossess() override;

private:
	void BindActions(UEnhancedInputComponent* inputComponent);

private:
	UPROPERTY()
	TObjectPtr<UEnhancedInputComponent> m_enhancedInputComponent;

	UPROPERTY()
	TObjectPtr<APlayerCharacter> m_playerCharacter;

	UPROPERTY()
	TObjectPtr<UCharacterMovementComponent> m_movementComponent;
};
