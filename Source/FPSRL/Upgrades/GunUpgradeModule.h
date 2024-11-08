// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FPSRL/Interfaces/GunUpgrade.h"
#include "FPSRL/Interfaces/Interactable.h"
#include "GunUpgradeModule.generated.h"

class APlayerCharacter;
class UGunStats;
class UStaticMeshComponent;
class UBoxComponent;

UCLASS()
class FPSRL_API AGunUpgradeModule : public AActor, public IGunUpgrade, public IInteractable 
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGunUpgradeModule();

	UGunStats* GetModuleStats();

	virtual void Tick(float DeltaTime) override;
	virtual void Interact(APlayerCharacter* player) override;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
	UGunStats* _moduleStats;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* _staticMesh;
	//UPROPERTY(EditAnywhere)
	//UBoxComponent* _collisionMesh;

};
