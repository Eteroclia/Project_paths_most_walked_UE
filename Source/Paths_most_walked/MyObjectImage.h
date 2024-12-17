// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "MyObjectImage.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class PATHS_MOST_WALKED_API UMyObjectImage : public UObject
{
	GENERATED_BODY()
	public:
		UPROPERTY(BlueprintReadWrite)
			int tadam;

		//cv::Mat img;
};
