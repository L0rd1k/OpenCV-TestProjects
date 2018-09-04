#pragma once
#include <opencv2\highgui.hpp>
#include <opencv\cv.h>
using namespace std;
using namespace cv;


class ObjectTracking
{
public:
	const static int SENSITIVITY_VALUE = 20;
	const static int BLUR_SIZE = 10;
	int theObject[2] = { 0,0 };
	Rect objectBoundingRectangle = Rect(0, 0, 0, 0);
public:
	string intToString(int number);
	
	void searchForMovement(Mat thresholdImage, Mat &cameraFeed);
public:
	bool objectDetected = false;
	bool debugMode = false;
	bool trackingEnabled = false;
	bool pause = false;
public:
	Mat frame1, frame2;
	Mat greyImage1, greyImage2;
	Mat differenceImage;
	Mat thresholdImage;
	VideoCapture capture;
	ObjectTracking();
	~ObjectTracking();
};

