#pragma once
#include "ColorFilter.h"


class ColorDetector:public ColorFilter
{
public:
	ColorDetector();
	~ColorDetector();
	int VideoCapture();
	void clickAndDrag(int event, int x, int y, int flags, void* param);
	void recordHSV(Mat frame, Mat hsv_frame);
public:
	bool calibrationMode;
	bool mouseIsDragging;
	bool mouseMove;
	bool rectangleSelected;
	Point initialClickPoint;
	Point currentMousePoint;
	Rect rectangleROI; 
	vector<int> hueROI, saturationROI, valueROI; 

};

