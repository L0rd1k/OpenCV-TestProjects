#pragma once

#include <iostream>
#include <sstream>
#include <string>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;

class VideoWriting
{
public:
	VideoWriting();
	~VideoWriting();
	string intToString(int number);
	int VideoPlaying();
	int CaptureValidation();
	int VideoWriteValidation();
public:
	VideoCapture cap = 0;
	Mat frame;
	VideoWriter writer;
private:
	string filename = "D:\\myVideo.avi";
	int fcc = CV_FOURCC('D', 'I', 'V', '3');
	int fps = 10;
private:
	
};

