// Fill out your copyright notice in the Description page of Project Settings.


#include "ChickenCharacter_BA.h"
#include "SkeletalMeshComponentBudgeted.h"

// Sets default values
AChickenCharacter_BA::AChickenCharacter_BA(const class FObjectInitializer& ObjectInitializer) :
    Super(ObjectInitializer.SetDefaultSubobjectClass<USkeletalMeshComponentBudgeted>(AChickenCharacter_BA::MeshComponentName))
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AChickenCharacter_BA::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AChickenCharacter_BA::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AChickenCharacter_BA::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

