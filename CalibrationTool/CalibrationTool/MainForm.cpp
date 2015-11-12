#include "MainForm.h"
#include "FlyCap.h"
#include "FlyCapture2.h"
#include "StereoMatching.h"
#include "opencv2\opencv.hpp"
#include <Windows.h>
#include <memory.h>
#include <vector>
//#include <thread>

cv::Mat pic[2];
cv::Mat rectified[2];
std::vector<cv::Mat> leftvec;
std::vector<cv::Mat> rightvec;
StereoMatching stereo;
System::Void FindChessboardThread();
int imgcount = 0;
double rms = 0;
bool finishcalib = false;

void CalibrationTool::MainForm::ReloadPicture()
{
	throw gcnew System::NotImplementedException();
}

System::Void CalibrationTool::MainForm::RecordThread()
{
	cv::Size size;
	int a = MainForm::conf.chess_width;
	stereo = StereoMatching(MainForm::conf.chess_width, MainForm::conf.chess_height, MainForm::conf.chess_size);
	

	FlyCap fly = FlyCap(FlyCapture2::VideoMode::VIDEOMODE_640x480YUV422, FlyCapture2::FrameRate::FRAMERATE_30);
	
	int count = 0;

	////表示window
	//namedWindow("Camera_0", CV_WINDOW_AUTOSIZE);
	//namedWindow("Camera_1", CV_WINDOW_AUTOSIZE);

	while (1) {

		//cv::Mat pic[2];
		//RecordCamera rec;
		//Thread::Sleep(100);
		//rec.Recording(pic);
		fly.GetImages(pic);
		// 画面を更新
		BeginInvoke(gcnew DisplayDelegate(this, &MainForm::Display));
		//Display();

		count++;

		if (CalibrationTool::MainForm::recflg)
		{
			if (count > fps * 30) 
			{
				leftvec.push_back(pic[0].clone());
				rightvec.push_back(pic[1].clone());
				//if (size != pic[0].size()) {
				//	size = pic[0].size();
				//	stereo.SetImageSize(pic[0]);
				//}
				//Thread^ th = gcnew Thread(gcnew ThreadStart(this, &MainForm::FindChessboardThread));
				//th->IsBackground = true;
				//th->Start();
				count = 0; imgcount++;
				//CalibrationTool::MainForm::FindChessboardThread();
				finishcalib = false;
			}
		}
		else { 
			if (finishcalib) 
			{
				stereo.StereoRectify(pic[0], pic[1], rectified[0], rectified[1]);
			}
			
			count = 0; 
		}
	}
}

System::Void CalibrationTool::MainForm::FindChessboardThread() 
{
	bool find=stereo.DetectObjectPointsForStereoCamera(pic);
	if (find)
		imgcount++;
}

System::Void CalibrationTool::MainForm::Display()
{
	if (!finishcalib) {
		{
			//Graphics^g = Graphics::FromImage(pictureBox1->Image);
			Bitmap^ bmp = gcnew Bitmap(pic[0].cols, pic[0].rows, pic[0].step,
				System::Drawing::Imaging::PixelFormat::Format24bppRgb, IntPtr(pic[0].data));
			//g->DrawImage(bmp, 0, 0, pic[0].cols, pic[0].rows);
			//pictureBox1->Refresh();
			//delete g;
			pictureBox1->Image = bmp;
			pictureBox1->Refresh();
		}
		{
			Bitmap^ bmp = gcnew Bitmap(pic[1].cols, pic[1].rows, pic[1].step,
				System::Drawing::Imaging::PixelFormat::Format24bppRgb, IntPtr(pic[1].data));
			pictureBox2->Image = bmp;
			pictureBox2->Refresh();
		}
	}
	else {
		{
			Bitmap^ bmp = gcnew Bitmap(rectified[0].cols, rectified[0].rows, rectified[0].step,
				System::Drawing::Imaging::PixelFormat::Format24bppRgb, IntPtr(rectified[0].data));
			pictureBox1->Image = bmp;
			pictureBox1->Refresh();
		}
		{
			Bitmap^ bmp = gcnew Bitmap(rectified[1].cols, rectified[1].rows, rectified[1].step,
				System::Drawing::Imaging::PixelFormat::Format24bppRgb, IntPtr(rectified[1].data));
			pictureBox2->Image = bmp;
			pictureBox2->Refresh();
		}

	}
	MessageLabel->Text = imgcount.ToString();
}

System::Void CalibrationTool::MainForm::CalibrateThread()
{
	rms =stereo.StereoCalibrate_byOhara(leftvec,rightvec);
	finishcalib = true;
	//for (int i = 0; i < 100; i++) {
	//	Thread::Sleep(100);
	//	// 進捗状況として画面を更新
	//	BeginInvoke(gcnew ProgressDelegate(this, &MainForm::Progress),i);
	//}
	BeginInvoke(gcnew ProgressDelegate(this, &MainForm::Progress), 100);
}

System::Void CalibrationTool::MainForm::Progress(int num)
{
	MainForm::progressBar1->Value = num;
	MessageLabel->Text = "RSM="+ rms.ToString();
}

void CalibrationTool::MainForm::WriteImages() {
	std::string dir = "";
	for (int i = 0; i < leftvec.size(); i++) {
		std::string file = std::to_string(i) + "_left.bmp";
		cv::imwrite(file, leftvec[i]);
	}
	for (int i = 0; i < rightvec.size(); i++) {
		std::string file = std::to_string(i) + "_right.bmp";
		cv::imwrite(file, rightvec[i]);
	}
}
