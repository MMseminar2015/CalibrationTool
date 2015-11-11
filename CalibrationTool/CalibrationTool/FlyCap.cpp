// FlyCapOpenCV.cpp : �R���\�[�� �A�v���P�[�V�����̃G���g�� �|�C���g���`���܂��B
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
//�J�����̓��ꕨ
FlyCapture2::Camera** ppCams = new FlyCapture2::Camera*[numCams];

FlyCap::FlyCap() {
	//�擾���铮��T�C�Y(���[�h)�ƃt���[�����[�g�ݒ�
	FlyCapture2::VideoMode vMode = VIDEOMODE_320x240YUV422;
	FlyCapture2::FrameRate fRate = FRAMERATE_30;

	FlyCapture2::BusManager busMgr;
	FlyCapture2::Error error;

	//�J�����F��
	error = busMgr.GetNumOfCameras(&numCams);
	//if (error != PGRERROR_OK || numCams < 1) return -1;
	//cout << "Number of cameras detected: " << numCams << endl;

	for (int i = 0; i < numCams; i++)
	{
		ppCams[i] = new FlyCapture2::Camera();
		FlyCapture2::PGRGuid guid;
		//�J�����ƃR�l�N�V����������
		error = busMgr.GetCameraFromIndex(i, &guid);
		//if (error != PGRERROR_OK) return -1;
		error = ppCams[i]->Connect(&guid);
		//if (error != PGRERROR_OK) return -1;
		//����T�C�Y(���[�h)�ƃt���[�����[�g�ݒ�
		error = ppCams[i]->SetVideoModeAndFrameRate(vMode, fRate);
		//if (error != PGRERROR_OK) return -1;
	}

	//�J��������摜�̓]�����J�n
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
			//frame�擾
			error = ppCams[i]->RetrieveBuffer(&cam_image);
			if (error != PGRERROR_OK) return -1;

			//rgb�ɕϊ�
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

