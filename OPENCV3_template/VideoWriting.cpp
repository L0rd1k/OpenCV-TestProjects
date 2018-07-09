#include "stdafx.h"
#include "VideoWriting.h"


VideoWriting::VideoWriting()
{
}
VideoWriting::~VideoWriting()
{
}
string VideoWriting::intToString(int number)
{
	std::stringstream ss;
	ss << number;
	return ss.str();
}

int VideoWriting::CaptureValidation()
{
	if (!cap.isOpened())
	{
		cout << "ERROR INITIALIZING VIDEO CAPTURE" << endl;
		return -1;
	}
	else
	{
		cout << "Initialization is going successfully" << endl;
		namedWindow("Webcam feed", CV_WINDOW_AUTOSIZE);
	}
}

int VideoWriting::VideoWriteValidation()
{
	cv::Size frameSize(cap.get(CV_CAP_PROP_FRAME_WIDTH), cap.get(CV_CAP_PROP_FRAME_HEIGHT));
	writer = VideoWriter(filename, fcc, fps, frameSize);

	if (!writer.isOpened())
	{
		cout << "ERROR OPENING FILE FOR WRITE" << endl;
		getchar();
		return -1;
	}
}

int VideoWriting::VideoPlaying()
{
	CaptureValidation();
	VideoWriteValidation(); 
	while (1)
	{
		bool bSuccess = cap.read(frame);
		if (!bSuccess)
		{
			cout << "ERROR READING FRAME CAMERA FEED" << endl;
			break;
		}
		putText(frame, "REC*", Point(0, 30), 2, 1, Scalar(0, 0, 255));
		putText(frame, "ESC to Exit", Point(450, 30), 2, 1, Scalar(0, 0, 255));
		putText(frame, "Save file to: " + filename, Point(0, 450), 1, 1, Scalar(0, 0, 255));
		writer.write(frame);
		imshow("Webcam feed", frame);
		switch (waitKey(10)) {
		case 27:
			return 0;

		}
	}
}
