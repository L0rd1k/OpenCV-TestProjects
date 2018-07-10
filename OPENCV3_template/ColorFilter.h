#pragma once
#include <iostream>
#include <opencv2\highgui.hpp>
using namespace std;
using namespace cv;
/*RGB to HSV*/
class ColorFilter  
{
public:
	ColorFilter();
	~ColorFilter();
private:
	const int FRAME_WIDTH = 640;
	const int FRAME_HEIGHT = 380;
	const string RGBwindowName = "RGB Image";
	const string HSVwindowName = "HSV Image";
};

