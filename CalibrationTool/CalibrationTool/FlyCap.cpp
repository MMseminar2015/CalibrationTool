// FlyCapOpenCV.cpp : コンソール アプリケーションのエントリ ポイントを定義します。
//

#include "FlyCapture2.h"
#include "FlyCap.h"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include <sstream>

using namespace FlyCapture2;
using namespace cv;
using namespace std;

unsigned int numCams;
//カメラの入れ物
FlyCapture2::Camera** ppCams = new FlyCapture2::Camera*[numCams];

FlyCap::FlyCap() {
	//取得する動画サイズ(モード)とフレームレート設定
	FlyCapture2::VideoMode vMode = VIDEOMODE_320x240YUV422;
	FlyCapture2::FrameRate fRate = FRAMERATE_30;

	FlyCapture2::BusManager busMgr;
	FlyCapture2::Error error;

	//カメラ認識
	error = busMgr.GetNumOfCameras(&numCams);
	//if (error != PGRERROR_OK || numCams < 1) return -1;
	//cout << "Number of cameras detected: " << numCams << endl;

	for (int i = 0; i < numCams; i++)
	{
		ppCams[i] = new FlyCapture2::Camera();
		FlyCapture2::PGRGuid guid;
		//カメラとコネクションを結ぶ
		error = busMgr.GetCameraFromIndex(i, &guid);
		//if (error != PGRERROR_OK) return -1;
		error = ppCams[i]->Connect(&guid);
		//if (error != PGRERROR_OK) return -1;
		//動画サイズ(モード)とフレームレート設定
		error = ppCams[i]->SetVideoModeAndFrameRate(vMode, fRate);
		//if (error != PGRERROR_OK) return -1;
	}

	//カメラから画像の転送を開始
	error = Camera::StartSyncCapture(numCams, (const Camera**)ppCams);
	//if (error != PGRERROR_OK) return -1;


}
FlyCap::~FlyCap() {
	for (int i = 0; i < numCams; i++)
	{
		ppCams[i]->StopCapture();
		ppCams[i]->Disconnect();
		delete ppCams[i];
	}
	delete[] ppCams;
}


int FlyCap::GetImages(cv::Mat *images)
{
		cv::Mat cv_image;
		FlyCapture2::Image cam_image, rgb_image;
		FlyCapture2::Error error;
		for (int i = 0; i < numCams; i++)
		{
			//frame取得
			error = ppCams[i]->RetrieveBuffer(&cam_image);
			if (error != PGRERROR_OK) return -1;

			//rgbに変換
			error = cam_image.Convert(FlyCapture2::PixelFormat::PIXEL_FORMAT_BGR, &rgb_image);
			if (error != PGRERROR_OK) return -1;
			cv_image = cv::Mat(rgb_image.GetRows(), rgb_image.GetCols(), CV_8UC3, rgb_image.GetData());
			images[i] = cv_image;
			//string window_name = "Camera_" + to_string(i);
			//cv::imshow(window_name, cv_image);
		}
		//int key = cv::waitKey(15);
	return 0;
}

