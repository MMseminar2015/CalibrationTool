#include <string>
#include <vector>
#include "RecordCamera.h"
#include "opencv2\opencv.hpp"
#include "FileUtility.h"


std::vector<std::string> files;
int count = 0;

RecordCamera::RecordCamera()
{
	files = FileUtility::GetFilesFromDirectory("C:\\Users\\Ohara Kazuya\\Desktop\\FlyCap_pic_1023", "*.bmp");
}

void RecordCamera::Recording(cv::Mat* pic)
{
	if (count > files.size() - 1)
		count = 0;
	*pic = cv::imread(files[count]);
	cv::Mat* tmp=pic+1;
	count++ ;
	if (count > files.size() - 1)
		count = 0;
	*tmp = cv::imread(files[count]);
	count++;
}
