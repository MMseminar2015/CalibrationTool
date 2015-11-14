#pragma once

#include "FlyCapture2.h"
#include "opencv2/highgui/highgui.hpp"


class FlyCap
{
public:
	FlyCap(FlyCapture2::VideoMode vm = FlyCapture2::VideoMode::VIDEOMODE_640x480YUV422, FlyCapture2::FrameRate fr = FlyCapture2::FrameRate::FRAMERATE_30, float fps = 30.00);
	~FlyCap();

	void GetImages(cv::Mat *images);

	unsigned int numCams;
};

