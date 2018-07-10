//// OPENCV3_template.cpp: определяет точку входа для консольного приложения.
////
//
#include "stdafx.h"
#include "VideoWriting.h"
using namespace std;
using namespace cv;

int main (int argc, char* argv[] )
{
	//VideoWriting vidWrite;
	//vidWrite.VideoPlaying();
	const int FRAME_WIDTH = 320;
	const int FRAME_HEIGHT = 240;
	const string RGBwindowName = "RGB Image";
	const string HSVwindowName = "HSV Image";
	Mat cameraFeed;
	Mat HSV;
	VideoCapture capture;
	capture.open(0);
	capture.set(CV_CAP_PROP_FRAME_WIDTH, FRAME_WIDTH);
	capture.set(CV_CAP_PROP_FRAME_HEIGHT, FRAME_HEIGHT);
	while (1)
	{
		capture.read(cameraFeed);
		cvtColor(cameraFeed, HSV, CV_RGB2GRAY);
		imshow(RGBwindowName, cameraFeed);
		imshow(HSVwindowName, HSV);
		waitKey(30);
	}
	return 0;
}