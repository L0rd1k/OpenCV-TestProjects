#pragma once
#include <iostream>
#include <stdio.h>
#include <sstream>
#include <string>
#include <opencv2\highgui.hpp>
#include <opencv2\core.hpp>
#include <opencv2\imgproc.hpp>
#include <opencv\cv.h>


using namespace std;
using namespace cv;
/*RGB to HSV*/
class ColorFilter  
{
public:
	ColorFilter();
	~ColorFilter();
	Mat RGB;
	Mat HSV;
	Mat threshold;
	VideoCapture capture;
	virtual int VideoCapture();
public:
	void createTrackbars();
public:
	int x = 0, y = 0;
	int max_hue = 256;
	int min_hue = 0;
	int max_saturation = 256;
	int min_saturation = 0;
	int max_value = 256;
	int min_value = 0;
	int windowWidth = 640;
	int windowHeight = 380;
public:
	/* Making white spaces : Erodes(smaller) + Dilates(bigger)*/
	void MorphologicalOp(Mat &threshold);
	void TrackObject(int &x,int &y, Mat threshold, Mat &RGB);
	void DrawObject(int x, int y, Mat &frame);
	string intToString(int number);
	const int numDetectObjects = 50;
	const int minObjectArea = 20 * 20;
	const int maxObjectArea = windowHeight * windowWidth / 1.5;
protected:
	bool trackObjects = 0;
	bool switchMorphOp = 0;
	bool switchHSV = 0;
	bool switchTrackBar = 0;
	bool switchTreshold = 0;
	string RGBwindowName = "RGB Image";
	string HSVwindowName = "HSV Image";
	string TrackBarwindowName = "TrackBar";
	string ThresholdwindowName = "Threshold Image";
};

