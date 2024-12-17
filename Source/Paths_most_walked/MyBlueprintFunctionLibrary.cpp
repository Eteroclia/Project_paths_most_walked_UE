// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBlueprintFunctionLibrary.h"

#include "MyObjectImage.h"

void UMyBlueprintFunctionLibrary::moveActor(AActor* actor, UMyObjectImage* img)
{
	if (!IsValid(actor))
		return;

	actor->SetActorLocation(actor->GetActorLocation() + FVector(0,0,img->tadam));
}