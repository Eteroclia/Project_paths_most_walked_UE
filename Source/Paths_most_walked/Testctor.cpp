// Fill out your copyright notice in the Description page of Project Settings.


#include "Testctor.h"

// Sets default values
ATestctor::ATestctor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATestctor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATestctor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Some debug message!"));

}

