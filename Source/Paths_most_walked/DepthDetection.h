// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"

#include "Calibration.h"
#include "DepthDetection.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class PATHS_MOST_WALKED_API UDepthDetection : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	public:
		UFUNCTION(BlueprintCallable)
			void updateStereo();
		UFUNCTION(BlueprintCallable)
			void retrieveMaps(UCalibration* calibrator);
		UFUNCTION(BlueprintCallable)
			bool mapsStatus();
	
};
