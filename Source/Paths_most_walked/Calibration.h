// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "CVImage.h"
#include "Calibration.generated.h"


/**
 * 
 */
UCLASS(BlueprintType)
class PATHS_MOST_WALKED_API UCalibration : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	public:
		UFUNCTION(BlueprintCallable)
			void storeImg(UTexture2D* imageL, UTexture2D* imageR);
		UFUNCTION(BlueprintCallable)
			void getStereoMatrixes();
	public:
		std::vector<cv::Mat> getMaps();


	
};
