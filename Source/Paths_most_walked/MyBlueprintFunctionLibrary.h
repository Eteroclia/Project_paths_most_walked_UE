// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "MyBlueprintFunctionLibrary.generated.h"


class UMyObjectImage;

/**
 * 
 */
UCLASS()
class PATHS_MOST_WALKED_API UMyBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	public:

		UFUNCTION(BlueprintCallable)
			static void moveActor(AActor* actor, UMyObjectImage* img);
};
