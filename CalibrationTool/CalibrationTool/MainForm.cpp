#include "MainForm.h"
#include "FlyCap.h"
#include "StereoMatching.h"
#include "opencv2\opencv.hpp"
#include <Windows.h>
#include <memory.h>
#include <vector>
//#include <thread>

cv::Mat pic[2];
StereoMatching stereo;
System::Void FindChessboardThread();
int imgcount = 0;

void CalibrationTool::MainForm::ReloadPicture()
{
	throw gcnew System::NotImplementedException();
}

System::Void CalibrationTool::MainForm::RecordThread()
{
	cv::Size size;
	int a = MainForm::conf.chess_width;
	stereo=StereoMatching(MainForm::conf.chess_width, MainForm::conf.chess_height, MainForm::conf.chess_size);
	FlyCap fly;
	int count = 0;

	while (1) {

		//cv::Mat pic[2];
		//RecordCamera rec;
		//Thread::Sleep(100);
		//rec.Recording(pic);
		fly.GetImages(pic);
		for (int i = 0; i < 2; i++) {
			// 画面を更新
			BeginInvoke(gcnew DisplayDelegate(this, &MainForm::Display));
		}
		count++;

		if (CalibrationTool::MainForm::recflg)
		{
			//if (count > fps * 30) 
			{
				if (size != pic[0].size()) {
					size = pic[0].size();
					stereo.SetImageSize(pic[0]);
				}
				//Thread^ th = gcnew Thread(gcnew ThreadStart(this, &MainForm::FindChessboardThread));
				//th->IsBackground = true;
				//th->Start();
				count = 0;
				//CalibrationTool::MainForm::FindChessboardThread();
			}
		}
		else { count = 0; }
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
	{
		//Graphics^g = Graphics::FromImage(pictureBox1->Image);
		Bitmap^ bmp = gcnew Bitmap(pic[0].cols, pic[0].rows, pic[0].step,
			System::Drawing::Imaging::PixelFormat::Format24bppRgb, IntPtr(pic[0].data));
		//g->DrawImage(bmp, 0, 0, pic[0].cols, pic[0].rows);
		//pictureBox1->Refresh();
		//delete g;
		pictureBox1->Image = bmp;
	}
	{
		Bitmap^ bmp = gcnew Bitmap(pic[1].cols, pic[1].rows, pic[1].step,
			System::Drawing::Imaging::PixelFormat::Format24bppRgb, IntPtr(pic[1].data));
		pictureBox2->Image = bmp;
	}
	MessageLabel->Text = imgcount.ToString();
}

System::Void CalibrationTool::MainForm::CalibrateThread()
{
	stereo.StereoCalibrate();
	//for (int i = 0; i < 100; i++) {
	//	Thread::Sleep(100);
	//	// 進捗状況として画面を更新
	//	BeginInvoke(gcnew ProgressDelegate(this, &MainForm::Progress),i);
	//}
}

System::Void CalibrationTool::MainForm::Progress(int num)
{
	MainForm::progressBar1->Value = num;
}


