// Fill out your copyright notice in the Description page of Project Settings.



#include "opencv2/opencv.hpp"
#include <opencv2/highgui/highgui.hpp>
#include "iostream"
#include <string>
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <stdio.h>
#include "opencv2/imgcodecs.hpp"
#include <iomanip>
#include "CVImage.h"
#include "DepthDetection.h"
#include "Calibration.h"
#include "OpenCVHelper.h"


int numDisparities = 8;
int blockSize = 5;
int preFilterType = 1;
int preFilterSize = 1;
int preFilterCap = 31;
int minDisparity = 0;
int textureThreshold = 10;
int uniquenessRatio = 15;
int speckleRange = 0;
int speckleWindowSize = 0;
int disp12MaxDiff = -1;
float M = 4.4075000000000003e+01;

float imageSizeThresh = 0.01;

// These parameters can vary according to the setup
float max_depth = 400.0; //maximum distance the setup can measure (in cm)
float min_depth = 50.0; //minimum distance the setup can measure (in cm)
float depth_thresh = 150.0; // Threshold for SAFE distance (in cm)

// Creating an object of StereoBM algorithm
cv::Ptr<cv::StereoBM> stereo = cv::StereoBM::create();


//Initialize variables to store the maps for stereo rectification
cv::Mat Left_Stereo_Map1, Left_Stereo_Map2;
cv::Mat Right_Stereo_Map1, Right_Stereo_Map2;

void UDepthDetection::updateStereo() {
    stereo->setNumDisparities(numDisparities);
    stereo->setBlockSize(blockSize);
    stereo->setPreFilterType(preFilterType);
    stereo->setPreFilterSize(preFilterSize);
    stereo->setPreFilterCap(preFilterCap);
    stereo->setTextureThreshold(textureThreshold);
    stereo->setUniquenessRatio(uniquenessRatio);
    stereo->setSpeckleRange(speckleRange);
    stereo->setSpeckleWindowSize(speckleWindowSize);
    stereo->setDisp12MaxDiff(disp12MaxDiff);
    stereo->setMinDisparity(minDisparity);
}

void UDepthDetection::retrieveMaps(UCalibration* calibrator){
    std::vector<cv::Mat> maps = calibrator->getMaps();
}

bool UDepthDetection::mapsStatus()
{
    if (Left_Stereo_Map1.empty() || Left_Stereo_Map2.empty()||Right_Stereo_Map1.empty()||Right_Stereo_Map2.empty())
        return false;
    else
        return true;
}

std::vector<std::vector<cv::Point>> getContours(cv::Mat depth_map) {
    cv::Mat imgL;
    cv::Mat imgR;
    cv::Mat imgL_gray;
    cv::Mat imgR_gray;
    cv::Mat disp, disparity;
    cv::Mat output_canvas;

    cv::Mat mask;
    cv::Mat mean;
    cv::Mat stddev;
    cv::Mat mask2;

    // Mask to segment regions with depth less than safe distance
    cv::inRange(depth_map, 10, depth_thresh, mask);
    double s = (cv::sum(mask)[0]) / 255.0;
    double img_area = double(mask.rows * mask.cols);

    std::vector<std::vector<cv::Point>> contours;
    std::vector<std::vector<cv::Point>> relevantContours;
    std::vector<cv::Vec4i> hierarchy;

    // Check if a significantly large obstacle is present and filter out smaller noisy regions
    if (s > imageSizeThresh * img_area) {
        // finding conoturs in the generated mask
        cv::findContours(mask, contours, hierarchy, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE);

        for (int i = 0;i < contours.size();i++) {
            std::vector<cv::Point> cnt = contours[i];
            // Check if detected contour is significantly large (to avoid multiple tiny regions)
            double cnt_area = fabs(cv::contourArea(cv::Mat(cnt)));
            if (cnt_area > imageSizeThresh * img_area)
            {
                relevantContours.push_back(cnt);
            }
        }
    }
    return relevantContours;
}

cv::Mat calcDepthMap(cv::Mat frameL, cv::Mat FrameR) {
    cv::Mat imgL_gray;
    cv::Mat imgR_gray;
    cv::Mat disp, disparity;
    // Converting images to grayscale
    cv::cvtColor(frameL, imgL_gray, cv::COLOR_BGR2GRAY);
    cv::cvtColor(FrameR, imgR_gray, cv::COLOR_BGR2GRAY);

    // Initialize matrix for rectified stereo images
    cv::Mat Left_nice;
    cv::Mat Right_nice;
    // Applying stereo image rectification on the left image
    cv::remap(imgL_gray,
        Left_nice,
        Left_Stereo_Map1,
        Left_Stereo_Map2,
        cv::INTER_LANCZOS4,
        cv::BORDER_CONSTANT,
        0);

    // Applying stereo image rectification on the right image
    cv::remap(imgR_gray,
        Right_nice,
        Right_Stereo_Map1,
        Right_Stereo_Map2,
        cv::INTER_LANCZOS4,
        cv::BORDER_CONSTANT,
        0);

    // Calculating disparith using the StereoBM algorithm
    stereo->compute(Left_nice, Right_nice, disp);

    // NOTE: compute returns a 16bit signed single channel image,
        // CV_16S containing a disparity map scaled by 16. Hence it 
    // is essential to convert it to CV_16S and scale it down 16 times.

    // Converting disparity values to CV_32F from CV_16S
    disp.convertTo(disparity, CV_32F, 1.0);

    // Scaling down the disparity values and normalizing them
    disparity = (disparity / 16.0f - (float)minDisparity) / ((float)numDisparities);

    // Calculating disparity to depth map using the following equation
    // ||    depth = M * (1/disparity)   ||
    cv::Mat depth_map = (float)M / disparity;
    
    return depth_map;
}


std::vector<cv::Rect> getBoundingBoxes(std::vector<std::vector<cv::Point>> contours) {
    std::vector<cv::Rect> boundingBoxes;
    for (int i = 0;i < contours.size();i++) {
        std::vector<cv::Point> cnt = contours[i];
        cv::Rect box;
        // Finding the bounding rectangle for the largest contour
        box = cv::boundingRect(cnt);
        boundingBoxes.push_back(box);
    }
    return boundingBoxes;
}