#include "stdafx.h"
#include "ColorFilter.h"

ColorFilter::ColorFilter()
{
}

ColorFilter::~ColorFilter()
{
}

void on_trackbar(int, void*) 
{
};

void ColorFilter::createTrackbars()
{
	namedWindow(TrackBarwindowName, 0);
	char TrackBarName[50];
	sprintf_s(TrackBarName, "Hue-min", min_hue);
	sprintf_s(TrackBarName, "Hue-max", max_hue);
	sprintf_s(TrackBarName, "Saturation-min", min_saturation);
	sprintf_s(TrackBarName, "Saturation-max", max_saturation);
	sprintf_s(TrackBarName, "Value-min", min_value);
	sprintf_s(TrackBarName, "Value-max", max_value);


	createTrackbar("Hue-min", TrackBarwindowName, &min_hue, max_hue, on_trackbar);
	createTrackbar("Hue-max", TrackBarwindowName, &max_hue, max_hue, on_trackbar);
	createTrackbar("Saturation-min", TrackBarwindowName, &min_saturation, max_saturation, on_trackbar);
	createTrackbar("Saturation-max", TrackBarwindowName, &max_saturation, max_saturation, on_trackbar);
	createTrackbar("Value-min", TrackBarwindowName, &min_value, max_value, on_trackbar);
	createTrackbar("Value-max", TrackBarwindowName, &max_value, max_value, on_trackbar);
}

void ColorFilter::MorphologicalOp(Mat &threshold)
{
	Mat Erode = getStructuringElement(MORPH_RECT, Size(3, 3));
	Mat Dilate = getStructuringElement(MORPH_RECT, Size(8, 8));

	erode(threshold, threshold, Erode);
	erode(threshold, threshold, Erode);

	dilate(threshold, threshold, Dilate);
	dilate(threshold, threshold, Dilate);
}

string ColorFilter::intToString(int number)
{
	stringstream ss;
	ss << number;
	return ss.str();
}

void ColorFilter::DrawObject(int x, int y, Mat &frame)
{

	circle(frame, Point(x, y), 20, Scalar(0, 255, 0), 2);
	if (y - 25 > 0)
		line(frame, Point(x, y), Point(x, y - 25), Scalar(0, 255, 0), 2);
	else  line(frame, Point(x, y), Point(x, 0), Scalar(0, 255, 0), 2);
	if (y + 25 < windowHeight)
		line(frame, Point(x, y), Point(x, y + 25), Scalar(0, 255, 0), 2);
	else line(frame, Point(x, y), Point(x, windowHeight), Scalar(0, 255, 0), 2);
	if (x - 25 > 0)
		line(frame, Point(x, y), Point(x - 25, y), Scalar(0, 255, 0), 2);
	else line(frame, Point(x, y), Point(0, y), Scalar(0, 255, 0), 2);
	if (x + 25 < windowWidth)
		line(frame, Point(x, y), Point(x + 25, y), Scalar(0, 255, 0), 2);
	else line(frame, Point(x, y), Point(windowWidth, y), Scalar(0, 255, 0), 2);

	putText(frame, intToString(x) + "," + intToString(y), Point(x, y + 30), 1, 1, Scalar(0, 255, 0), 2);
}

void ColorFilter::TrackObject(int &x, int &y, Mat threshold, Mat &RGB)
{
	Mat temp;
	threshold.copyTo(temp);
	vector<vector<Point>> contour; 
	vector<Vec4i> hierarchy;
	findContours(temp, contour, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE);
	double refArea = 0;
	bool objectFound = false;
	if (hierarchy.size() > 0)
	{
		int numObjects = hierarchy.size();
		if (numObjects < numDetectObjects)
		{
			for (int index = 0; index >= 0; index = hierarchy[index][0])
			{
				Moments moment = moments((cv::Mat)contour[index]);
				double area = moment.m00;
				if (area > minObjectArea && area < maxObjectArea && area > refArea)
				{
					x = moment.m10 / area;
					y = moment.m01 / area;
					objectFound = true;
					refArea = area;
				}
				else objectFound = false;
			}
			if (objectFound == true)
			{
				putText(RGB, "Tracking Object", Point(0, 50), 2, 1, Scalar(0, 255, 0), 2);
				DrawObject(x,y,RGB);
			}
		}
		else putText(RGB, "TOO MUCH NOISE! ADJUST FILTER", Point(0, 50), 1, 2, Scalar(0, 0, 255), 2);
	}
}

int ColorFilter::VideoCapture()
{
	int x = 0 , y = 0;
	capture.open(0); // open stram from WEb-cam (1), laptop's Web-cam (0)
	capture.set(CV_CAP_PROP_FRAME_WIDTH, windowWidth); 
	capture.set(CV_CAP_PROP_FRAME_HEIGHT, windowHeight);
	createTrackbars();
	while (1)
	{	

		if (!capture.isOpened()) // checking of capturing
		{
			cout << "Capturing error" << endl;
			return -1;
		}

		bool bSuccess = capture.read(RGB); // read the capturing frame into Matrix
		if (!bSuccess) // checking if reading was successully done
		{
			cout << "ERROR READING FRAME CAMERA FEED" << endl;
		}

		cvtColor(RGB, HSV, COLOR_BGR2HSV); // convert RGB into HSV
		inRange(HSV, Scalar(min_hue, min_saturation, min_value), Scalar(max_hue, max_saturation, max_value), threshold);

		if (switchMorphOp)
		{
			MorphologicalOp(threshold);
		}

		if (trackObjects)
		{
			TrackObject(x, y, threshold, RGB);
		}

		if (switchTreshold)
		{
			imshow(ThresholdwindowName, threshold);
		} else { destroyWindow(ThresholdwindowName); }

		putText(RGB, "(1)C to Treshold", Point(windowWidth - 150, 12), 1, 1, Scalar(0, 0, 255));
		putText(RGB, "(2)ESC to Exit", Point(windowWidth - 150, 24), 1, 1, Scalar(0, 0, 255));
		putText(RGB, "(3)Z to HSV", Point(windowWidth - 150, 36), 1, 1, Scalar(0, 0, 255));
		putText(RGB, "(4)V to Morph.Op.", Point(windowWidth - 150, 48), 1, 1, Scalar(0, 0, 255));
		putText(RGB, "(5)X to Track obj.", Point(windowWidth - 150, 60), 1, 1, Scalar(0, 0, 255));

		imshow(RGBwindowName, RGB); // open original RGB video stream;
		
		if (switchHSV) // if button pressed we close/open window HSV
		{
			imshow(HSVwindowName, HSV); // open HSV video stream;
		} else { destroyWindow(HSVwindowName); }


		switch (waitKey(30)) 
		{
			case 27: // ESC
				return 0;
			case 122: //Z
				switchHSV = !switchHSV;
				break;
			case 120: //X
				trackObjects = !trackObjects;
				break;
			case 99: // C
				switchTreshold = !switchTreshold;
				break;
			case 118:
				switchMorphOp = !switchMorphOp;
				break;
		}
	}
}