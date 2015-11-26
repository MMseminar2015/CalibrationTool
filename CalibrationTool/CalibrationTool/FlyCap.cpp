#include "FlyCap.h"
#include "FlyCapture2.h"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include <sstream>
#include <direct.h>

using namespace FlyCapture2;
using namespace std;
using namespace cv;


FlyCapture2::Camera** ppCams;
FlyCapture2::Image cam_image[2], rgb_image[2];
cv::Mat cv_image[2];
FlyCapture2::Error fcerror;



FlyCap::FlyCap(FlyCapture2::VideoMode vm, FlyCapture2::FrameRate fr, float fps)
{
	//カメラの入れ物
	ppCams = new FlyCapture2::Camera*[numCams];
	FlyCapture2::Camera();

	//取得する動画サイズ(モード)とフレームレート設定
	FlyCapture2::VideoMode vMode = vm;
	FlyCapture2::FrameRate fRate = fr;

	FlyCapture2::BusManager busMgr;

	//カメラ認識
	fcerror = busMgr.GetNumOfCameras(&numCams);
	if (fcerror != PGRERROR_OK || numCams < 1) exit(1);
	cout << "Number of cameras detected: " << numCams << endl;

	for (unsigned int i = 0; i < numCams; i++)
	{
		ppCams[i] = new FlyCapture2::Camera();
		FlyCapture2::PGRGuid guid;
		//カメラとコネクションを結ぶ
		fcerror = busMgr.GetCameraFromIndex(i, &guid);
		if (fcerror != PGRERROR_OK) exit(1);
		fcerror = ppCams[i]->Connect(&guid);
		if (fcerror != PGRERROR_OK) exit(1);
		//動画サイズ(モード)とフレームレート(Max値？)設定
		fcerror = ppCams[i]->SetVideoModeAndFrameRate(vMode, fRate);
		if (fcerror != PGRERROR_OK) exit(1);
		//fps設定
		FlyCapture2::Property prop;
		prop.type = FlyCapture2::PropertyType::FRAME_RATE;
		prop.absControl = true;
		prop.onePush = false;
		prop.onOff = true;
		prop.autoManualMode = false;
		prop.absValue = fps;
		ppCams[i]->SetProperty(&prop);
		//shutter speed設定
		prop.type = FlyCapture2::PropertyType::SHUTTER;
		prop.absControl = true;
		prop.onePush = false;
		prop.onOff = false;
		prop.autoManualMode = false;
		prop.absValue = 10;
		ppCams[i]->SetProperty(&prop);
	}

	//カメラから画像の転送を開始
	fcerror = Camera::StartSyncCapture(numCams, (const Camera**)ppCams);
	if (fcerror != PGRERROR_OK) exit(1);

	//バッファ内の最新データを取り出すように設定(start後でないと反映されない)
	for (unsigned int i = 0; i < numCams; i++)
	{
		FC2Config conf;
		//conf.grabMode = GrabMode::BUFFER_FRAMES;
		conf.grabMode = GrabMode::DROP_FRAMES;
		ppCams[i]->SetConfiguration(&conf);
	}
}



FlyCap::~FlyCap()
{
	for (unsigned int i = 0; i < numCams; i++)
	{
		ppCams[i]->StopCapture();
		ppCams[i]->Disconnect();
		delete ppCams[i];
	}
	delete[] ppCams;
}




void FlyCap::GetImages(cv::Mat *images)
{
	//frame取得
	for (unsigned int i = 0; i < numCams; i++)
	{
		fcerror = ppCams[i]->RetrieveBuffer(&cam_image[i]);
		if (fcerror != PGRERROR_OK) exit(1);
	}
	//rgbに変換→Matに変換
	for (unsigned int i = 0; i < numCams; i++)
	{
		fcerror = cam_image[i].Convert(FlyCapture2::PixelFormat::PIXEL_FORMAT_BGR, &rgb_image[i]);
		if (fcerror != PGRERROR_OK) exit(1);
		images[i] = cv::Mat(rgb_image[i].GetRows(), rgb_image[i].GetCols(), CV_8UC3, rgb_image[i].GetData());
	}
}


