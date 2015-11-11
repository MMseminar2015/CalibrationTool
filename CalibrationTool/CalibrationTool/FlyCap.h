#pragma once
#include "opencv2/highgui/highgui.hpp"

class FlyCap {
public:
	FlyCap();
	~FlyCap();

	int GetImages(cv::Mat *images);

};