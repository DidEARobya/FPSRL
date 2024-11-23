// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GOAP_TargetSensor.generated.h"

class USphereComponent;
class UGOAP_Agent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FPSRL_API UGOAP_TargetSensor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGOAP_TargetSensor();

	void Init(float radius, TObjectPtr<UGOAP_Agent> agent);
	void SetTarget(TObjectPtr<AActor> target);

	UFUNCTION()
	void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void Scan();
public:
	UPROPERTY(EditAnywhere)
	TObjectPtr<USphereComponent> _sensor;

	TObjectPtr<AActor> _target;
	TObjectPtr<UGOAP_Agent> _agent;
	float _radius;
};
