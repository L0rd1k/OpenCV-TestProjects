#include "stdafx.h"
#include "ColorDetector.h"


ColorDetector::ColorDetector()
{
}


ColorDetector::~ColorDetector()
{
}

void ColorDetector::clickAndDrag(int event, int x, int y, int flags, void* param)
{
	if (calibrationMode == true)
	{
		Mat* videoFeed = (Mat*)param;
		if (event == CV_EVENT_LBUTTONDOWN && mouseIsDragging == false) // left mouse button was pressed
		{
			initialClickPoint = Point(x, y); 
			mouseIsDragging = true;
		}
		if (event == CV_EVENT_MOUSEMOVE && mouseIsDragging == true) // dragging the mouse
		{
			currentMousePoint = Point(x, y);
			mouseMove = true;
		}
		if (event == CV_EVENT_LBUTTONUP && mouseIsDragging == true) // left mouse button was released
		{
			rectangleROI = Rect(initialClickPoint, currentMousePoint);
			mouseIsDragging = false;
			mouseMove = false;
			rectangleSelected = true;
		}
		if (event == CV_EVENT_RBUTTONDOWN) //right mouse button was clicked
		{
			int max_hue = 256;
			int min_hue = 0;
			int max_saturation = 256;
			int min_saturation = 0;
			int max_value = 256;
			int min_value = 0;
		}
	}
}

void ColorDetector::recordHSV(Mat frame, Mat hsv_frame)
{
	if (mouseMove == false && rectangleSelected == true)
	{
		if(hueROI.size() > 0) 
		{ hueROI.clear(); }
		if(saturationROI.size() > 0)
		{ saturationROI.clear(); }
		if(valueROI.size() > 0)
		{ valueROI.clear(); }

		if (rectangleROI.width < 1 || rectangleROI.height < 1)
		{
			cout << "Please drag a rectangle, not a line." << endl;
		} 
		else
		{
			for (int i = rectangleROI.x; i < rectangleROI.x + rectangleROI.width; i++)
			{
				for (int j = rectangleROI.y; j < rectangleROI.y + rectangleROI.height; j++)
				{
					hueROI.push_back((int)hsv_frame.at<Vec3b>(j, i)[0]);
					saturationROI.push_back((int)hsv_frame.at<Vec3b>(j, i)[1]);
					valueROI.push_back((int)hsv_frame.at<Vec3b>(j, i)[2]);
				}
			}
		}
		rectangleSelected = false;
		if (hueROI.size() > 0)
		{
			min_hue = *min_element(hueROI.begin(), hueROI.end());
			max_hue = *max_element(hueROI.begin(), hueROI.end());
			cout << "Minimal Hue Value: " << min_hue << endl;
			cout << "Maximal Hue Value: " << max_hue << endl;
		}
		if (saturationROI.size() > 0)
		{
			min_saturation = *min_element(saturationROI.begin(), saturationROI.end());
			max_saturation = *max_element(saturationROI.begin(), saturationROI.end());
			cout << "Minimal Saturation Value: " << min_saturation << endl;
			cout << "Maximal Saturation Value: " << max_saturation << endl;
		}
		if (valueROI.size() > 0)
		{
			min_value = *min_element(valueROI.begin(), valueROI.end());
			max_value = *max_element(valueROI.begin(), valueROI.end());
			cout << "Minimal Value Value: " << min_saturation << endl;
			cout << "Maximal Value Value: " << max_saturation << endl;
		}
	}

	if (mouseMove == true)
	{
		rectangle(frame, initialClickPoint, Point(currentMousePoint.x, currentMousePoint.y), Scalar(0, 255, 0), 1, 8, 0);
	}
}

int ColorDetector::VideoCapture()
{
	calibrationMode = true;
	capture.open(0);
	capture.set(CV_CAP_PROP_FRAME_WIDTH, windowWidth);
	capture.set(CV_CAP_PROP_FRAME_HEIGHT, windowHeight);
	//setMouseCallback(RGBwindowName, clickAndDrag, &RGB);
	mouseIsDragging = false;
	mouseMove = false;
	rectangleSelected = false;
	//while(1)

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
		}
		else { destroyWindow(ThresholdwindowName); }

		putText(RGB, "(1)C to Treshold", Point(windowWidth - 150, 12), 1, 1, Scalar(0, 0, 255));
		putText(RGB, "(2)ESC to Exit", Point(windowWidth - 150, 24), 1, 1, Scalar(0, 0, 255));
		putText(RGB, "(3)Z to HSV", Point(windowWidth - 150, 36), 1, 1, Scalar(0, 0, 255));
		putText(RGB, "(4)V to Morph.Op.", Point(windowWidth - 150, 48), 1, 1, Scalar(0, 0, 255));
		putText(RGB, "(5)X to Track obj.", Point(windowWidth - 150, 60), 1, 1, Scalar(0, 0, 255));

		imshow(RGBwindowName, RGB); // open original RGB video stream;

		if (switchHSV) // if button pressed we close/open window HSV
		{
			imshow(HSVwindowName, HSV); // open HSV video stream;
		}
		else { destroyWindow(HSVwindowName); }


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