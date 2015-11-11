#include "MainForm.h"
#include "FlyCap.h"
#include "opencv2\opencv.hpp"
#include <Windows.h>

cv::Mat pic[2];


void CalibrationTool::MainForm::ReloadPicture()
{
	throw gcnew System::NotImplementedException();
}

System::Void CalibrationTool::MainForm::RecordThread()
{
	FlyCap fly;
	while (CalibrationTool::MainForm::recflg) {

		//cv::Mat pic[2];
		//RecordCamera rec;
		//Thread::Sleep(100);
		//rec.Recording(pic);
		fly.GetImages(pic);
		for (int i = 0; i < 2; i++) {
			// 画面を更新
			BeginInvoke(gcnew DisplayDelegate(this, &MainForm::Display));
		}

	}
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
}

System::Void CalibrationTool::MainForm::CalibrateThread()
{
	
	for (int i = 0; i < 100; i++) {
		Thread::Sleep(100);
		// 進捗状況として画面を更新
		BeginInvoke(gcnew ProgressDelegate(this, &MainForm::Progress),i);
	}
}

System::Void CalibrationTool::MainForm::Progress(int num)
{
	MainForm::progressBar1->Value = num;
}


