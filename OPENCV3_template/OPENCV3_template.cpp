//// OPENCV3_template.cpp: определяет точку входа для консольного приложения.
////
//
#include "stdafx.h"
#include "VideoWriting.h"
using namespace std;
using namespace cv;

int main (int argc, char* argv[] )
{
	VideoWriting vidWrite;
	vidWrite.VideoPlaying();
	return 0;
}
//string intToString(int number)
//{
//	std::stringstream ss;
//	ss << number;
//	return ss.str();
//}

//int main (int argc, char* argv[] )
//{
//	int videoNumber = 0;
//	bool recording = false;
//	bool startNewRecording = false;
//	bool firstRun = true;
//	VideoCapture cap(0); // open cv camera - default - no - zero(0)
//
//	cv::VideoWriter writer;
//
//	if (!cap.isOpened()) // if unsuccessful - programm exit
//	{
//		cout << "ERROR INITIALIZING VIDEO CAPTURE" << endl;
//		return -1;
//	}
//
//	namedWindow("Webcam feed", CV_WINDOW_AUTOSIZE); // name for window and it size
//	
//	int fcc = CV_FOURCC('D', 'I', 'V', '3'); // fourcc - format of video
//	int fps = 10; // frame per seconds
//	cv:Size frameSize(cap.get(CV_CAP_PROP_FRAME_WIDTH), cap.get(CV_CAP_PROP_FRAME_HEIGHT)); // frame size
//	
//	Mat frame;
//	
//
//	while (1)
//	{
//		//if (startNewRecording == true)
//		//{
//		//	startNewRecording = false;
//		//	recording = true;
//		//	videoNumber++;
//		//	string filename = "D:\\myVideo" + intToString(videoNumber)+ ".avi"; // filename
//		//	writer = VideoWriter(filename, fcc, fps, frameSize);
//		//	if (!writer.isOpened())
//		//	{
//		//		cout << "ERROR OPENING FILE FOR WRITE" << endl;
//		//		getchar();
//		//		return -1;
//		//	}
//		//}
//	
//		bool bSuccess = cap.read(frame); // checking for  0 or 1
//		if (!bSuccess) // validation - is frame successfuly read?
//		{
//			cout << "ERROR READING FRAME CAMERA FEED" << endl;
//			break;
//		}
//
//		if (recording == true)
//		{
//			writer.write(frame);
//			putText(frame, "REC", Point(0, 60),2,2,Scalar(0,0,255));
//		}
//
//		imshow("Webcam feed", frame); // show a rame in my video windows
//
//		switch (waitKey(10)) // listem for 10ms for a key to be pressed
//		{
//		case 27:  // ESC
//			return 0;   // exit
//		case 114: //r
//			recording = !recording;
//			if (recording == true)
//			{
//				cout << "Begin Recording" << endl;
//			}
//			else
//			{
//				cout << "Recording Paused" << endl;
//			}
//
//			if (firstRun) 
//			{
//				string filename = "D:\\myVideo0.avi"; // filename
//				writer = VideoWriter(filename, fcc, fps, frameSize);
//				if (!writer.isOpened())
//				{
//					cout << "ERROR OPENING FILE FOR WRITE" << endl;
//					getchar();
//					return -1;
//				}
//			}
//
//			break;
//		case 110://n
//			startNewRecording = true;
//			cout << "New recording started" << endl;
//			if (firstRun == true)firstRun = false;
//			break;
//		}
//	}
//	system("pause");
//	return 0;
//}