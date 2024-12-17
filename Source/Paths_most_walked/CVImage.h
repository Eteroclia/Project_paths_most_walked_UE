// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "opencv2/opencv.hpp"

/*
#include <opencv2/highgui/highgui.hpp>
#include "iostream"
#include <string>
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <stdio.h>
#include "opencv2/imgcodecs.hpp"
#include <iomanip>
*/
#include "CVImage.generated.h"

/**
 * 
 */
UCLASS()
class PATHS_MOST_WALKED_API UCVImage : public UObject
{
	GENERATED_BODY()
	public:
		cv::Mat image;
};
