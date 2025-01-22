// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ChickenCharacter_BA.generated.h"

UCLASS()
class M2PW15_API AChickenCharacter_BA : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AChickenCharacter_BA(const FObjectInitializer& ObjectInitializer);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
