//// OPENCV3_template.cpp: определяет точку входа для консольного приложения.
////
//
#include "stdafx.h"
//#include <opencv2/opencv.hpp>
//#include <opencv2/highgui/highgui.hpp>
//#include <stdio.h>
//#include <io.h>
//#include <opencv/cv.h>
//#include <vlc\vlc.h>
//
//using namespace cv;
//using namespace std;
//
//struct VideoDataStruct 
//{
//	int param;
//	unsigned int videoBufferSize = 0;
//	uint8_t *videoBuffer = 0;
//	unsigned int dWidth = 0;
//	unsigned int dHeight = 0;
//};
//
//struct VlcParams
//{
//	libvlc_instance_t *inst;
//	libvlc_media_t *media;
//	libvlc_media_player_t *player;
//	libvlc_event_manager_t  *eventManager;
//};
//
//int done = 0;
//
//void cbVideoPrerender(void *p_video_data, uint8_t **pp_pixel_buffer, int size, char* strn) {
//	VideoDataStruct* data = (VideoDataStruct*)p_video_data;
//	if (size > data->videoBufferSize || !data->videoBuffer) {
//		printf("Reallocate raw video buffer\n");
//		free(data->videoBuffer);
//		data->videoBuffer = (uint8_t *)malloc(size);
//		data->videoBufferSize = size;
//	}
//	*pp_pixel_buffer = data->videoBuffer;
//}
//
//void cbVideoPostrender(void *p_video_data, uint8_t *p_pixel_buffer, int width, int height, int pixel_pitch, int size, int64_t pts) 
//{
//	VideoDataStruct* data = (VideoDataStruct*)p_video_data;
//	data->dWidth = width;
//	data->dHeight = height;
//	// Unlocking
//	//CloseHandle(hMutex);   
//}
//
//static void handleEvent(const libvlc_event_t* pEvt, void* pUserData)
//{
//	VlcParams* vlcParams = (VlcParams*)pUserData;
//	libvlc_time_t time;
//	switch (pEvt->type)
//	{
//	case libvlc_MediaPlayerTimeChanged:
//		time = libvlc_media_player_get_time(vlcParams->player);
//		printf("MediaPlayerTimeChanged %lld ms\n", (long long)time);
//		break;
//	case libvlc_MediaPlayerEndReached:
//		printf("MediaPlayerEndReached\n");
//		done = 1;
//		break;
//	default:
//		printf("%s\n", libvlc_event_type_name(pEvt->type));
//	}
//}
//
//int startStream(VlcParams& vlcParams, VideoDataStruct& dataStruct, std::string url)   //params for video rendering
//{
//	// VLC options
//	char smem_options[1000];
//	// RV24 
//	sprintf_s(smem_options
//		, "#transcode{vcodec=RV24}:smem{"
//		"video-prerender-callback=%lld,"
//		"video-postrender-callback=%lld,"
//		"video-data=%lld},"
//		//            "no-time-sync},"
//		, (long long int)(intptr_t)(void*)&cbVideoPrerender
//		, (long long int)(intptr_t)(void*)&cbVideoPostrender
//		, (long long int)(intptr_t)(void*)&dataStruct
//	);
//
//	const char * const vlc_args[] =
//	{
//		"-I", "dummy", // Don't use any interface
//		"--ignore-config", // Don't use VLC's config
//		"--sout", smem_options // Stream to memory
//	};
//	
//	vlcParams.inst = libvlc_new(sizeof(vlc_args) / sizeof(vlc_args[0]), vlc_args);
//	vlcParams.media = libvlc_media_new_location(vlcParams.inst, url.c_str());
//	vlcParams.player = libvlc_media_player_new_from_media(vlcParams.media);
//	vlcParams.eventManager = libvlc_media_player_event_manager(vlcParams.player);
//	libvlc_event_attach(vlcParams.eventManager, libvlc_MediaPlayerTimeChanged, handleEvent, &vlcParams);
//	libvlc_event_attach(vlcParams.eventManager, libvlc_MediaPlayerEndReached, handleEvent, &vlcParams);
//	libvlc_event_attach(vlcParams.eventManager, libvlc_MediaPlayerPositionChanged, handleEvent, &vlcParams);
//
//	//    libvlc_event_attach(vlcParams.eventManager, libvlc_MediaPlayerSnapshotTaken, handleEvent, &vlcParams);
//	//    libvlc_event_attach(vlcParams.eventManager, libvlc_MediaPlayerLengthChanged, handleEvent, &vlcParams);
//
//	/* play the media_player */
//	return libvlc_media_player_play(vlcParams.player);
//}
//
//void FramePerSecOutput(VideoDataStruct& VideoDataStruct, int windows)
//{
//	if (VideoDataStruct.videoBuffer && VideoDataStruct.dWidth > 0 && VideoDataStruct.dHeight >0)
//	{
//		printf("%d - %d\n", VideoDataStruct.dWidth, VideoDataStruct.dHeight);
//		Mat img = Mat(Size(VideoDataStruct.dWidth, VideoDataStruct.dHeight), CV_8UC3, VideoDataStruct.videoBuffer);
//		namedWindow("Display window " + to_string(windows), WINDOW_AUTOSIZE); // Create a window for display.
//		imshow("Display window " + to_string(windows), img); // Show our image inside it.
//		waitKey(1);
//	}
//}
//
//int main(int argc, char* argv[])
//{
//	VideoDataStruct dataStructIk, dataStructTv;
//	VlcParams vlcParamsIk, vlcParamsTv;
//	//startStream(vlcParamsTv, dataStructTv, "rtsp://root:0000@192.168.0.253:554/mjpeg1");
//	//startStream(vlcParamsIk, dataStructIk, "rtsp://192.168.0.111:554/onvif/media/PRF08.wxp");
//
//	startStream(vlcParamsTv, dataStructTv, "0");
//	startStream(vlcParamsIk, dataStructIk, "0");
//
//	//startStream(vlcParamsTv, dataStructTv, "file:///home/ilya/tmp/ir.avi");
//	//rtsp://192.168.0.111:554/onvif/media/PRF08.wxp
//
//	while (1) 
//	{
//		FramePerSecOutput(dataStructIk, 1);
//		FramePerSecOutput(dataStructTv, 2);
//	}
//	libvlc_release(vlcParamsTv.inst);
//	libvlc_release(vlcParamsIk.inst);
//}






#include "VideoWriting.h"
#include "ColorFilter.h"
#include <sstream>
#include <string>
#include <opencv2\highgui.hpp>
#include <opencv2\core.hpp>
#include <opencv2\imgproc.hpp>
#include <opencv\cv.h>

#include "Test.h"

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
