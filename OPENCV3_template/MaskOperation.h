#pragma once
#include <opencv2\imgcodecs.hpp>
#include <opencv2\highgui.hpp>
#include <opencv2\imgproc.hpp>
#include <iostream>

using namespace std;
using namespace cv;

class MaskOperation
{
public:
	MaskOperation();
	~MaskOperation();
	int Mask(int argc, int argv[]);
	const char* filename;
};

