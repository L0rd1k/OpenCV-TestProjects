//// OPENCV3_template.cpp: определяет точку входа для консольного приложения.
////
//
#include "stdafx.h"
#include "VideoWriting.h"
#include "ColorFilter.h"
#include <sstream>
#include <string>
#include <opencv2\highgui.hpp>
#include <opencv2\core.hpp>
#include <opencv2\imgproc.hpp>
#include <opencv\cv.h>
using namespace std;
using namespace cv;


int main (int argc, char* argv[] )
{
	//VideoWriting vidWrite;
	//vidWrite.VideoPlaying();



	ColorFilter clrFilter;
	clrFilter.VideoCapture();
	return 0;
}
//using namespace cv;
////initial min and max HSV filter values.
////these will be changed using trackbars
//int H_MIN = 0;
//int H_MAX = 256;
//int S_MIN = 0;
//int S_MAX = 256;
//int V_MIN = 0;
//int V_MAX = 256;
//
////default capture width and height
//const int FRAME_WIDTH = 640;
//const int FRAME_HEIGHT = 480;
//
////names that will appear at the top of each window
//const string windowName = "Original Image";
//const string windowName1 = "HSV Image";
//const string windowName2 = "Thresholded Image";
//const string trackbarWindowName = "Trackbars";
//void on_trackbar(int, void*)
//{//This function gets called whenever a
// // trackbar position is changed
//}
//
//void createTrackbars() {
//	//create window for trackbars
//
//
//	namedWindow(trackbarWindowName, 0);
//	//create memory to store trackbar name on window
//	char TrackbarName[50];
//	sprintf_s(TrackbarName, "H_MIN", H_MIN);
//	sprintf_s(TrackbarName, "H_MAX", H_MAX);
//	sprintf_s(TrackbarName, "S_MIN", S_MIN);
//	sprintf_s(TrackbarName, "S_MAX", S_MAX);
//	sprintf_s(TrackbarName, "V_MIN", V_MIN);
//	sprintf_s(TrackbarName, "V_MAX", V_MAX);
//	//create trackbars and insert them into window
//	//3 parameters are: the address of the variable that is changing when the trackbar is moved(eg.H_LOW),
//	//the max value the trackbar can move (eg. H_HIGH), 
//	//and the function that is called whenever the trackbar is moved(eg. on_trackbar)
//	//                                  ---->    ---->     ---->      
//	createTrackbar("H_MIN", trackbarWindowName, &H_MIN, H_MAX, on_trackbar);
//	createTrackbar("H_MAX", trackbarWindowName, &H_MAX, H_MAX, on_trackbar);
//	createTrackbar("S_MIN", trackbarWindowName, &S_MIN, S_MAX, on_trackbar);
//	createTrackbar("S_MAX", trackbarWindowName, &S_MAX, S_MAX, on_trackbar);
//	createTrackbar("V_MIN", trackbarWindowName, &V_MIN, V_MAX, on_trackbar);
//	createTrackbar("V_MAX", trackbarWindowName, &V_MAX, V_MAX, on_trackbar);
//
//
//}
//
//
//int main(int argc, char* argv[])
//{
//
//	//Matrix to store each frame of the webcam feed
//	Mat cameraFeed;
//	//matrix storage for HSV image
//	Mat HSV;
//	//matrix storage for binary threshold image
//	Mat threshold;
//
//	//create slider bars for HSV filtering
//	createTrackbars();
//	//video capture object to acquire webcam feed
//	VideoCapture capture;
//	//open capture object at location zero (default location for webcam)
//	capture.open(0);
//	//set height and width of capture frame
//	capture.set(CV_CAP_PROP_FRAME_WIDTH, FRAME_WIDTH);
//	capture.set(CV_CAP_PROP_FRAME_HEIGHT, FRAME_HEIGHT);
//	//start an infinite loop where webcam feed is copied to cameraFeed matrix
//	//all of our operations will be performed within this loop
//	while (1) {
//		//store image to matrix
//		capture.read(cameraFeed);
//		//convert frame from BGR to HSV colorspace
//		cvtColor(cameraFeed, HSV, COLOR_BGR2HSV);
//		//filter HSV image between values and store filtered image to
//		//threshold matrix
//		inRange(HSV, Scalar(H_MIN, S_MIN, V_MIN), Scalar(H_MAX, S_MAX, V_MAX), threshold);
//
//
//		//show frames 
//		imshow(windowName2, threshold);
//		imshow(windowName, cameraFeed);
//		imshow(windowName1, HSV);
//
//
//		//delay 30ms so that screen can refresh.
//		//image will not appear without this waitKey() command
//		waitKey(30);
//	}
//
//
//
//
//
//
//	return 0;
//}
