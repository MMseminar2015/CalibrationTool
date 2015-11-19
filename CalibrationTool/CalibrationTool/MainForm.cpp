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
	

	//FlyCap fly = FlyCap(FlyCapture2::VideoMode::VIDEOMODE_640x480YUV422, FlyCapture2::FrameRate::FRAMERATE_30, 30);
	
	int count = 0;

	////�\��window
	//namedWindow("1", CV_WINDOW_AUTOSIZE);
	//namedWindow("2", CV_WINDOW_AUTOSIZE);

	while (1) {


		//cv::Mat pic[2];
		RecordCamera rec;
		Thread::Sleep(100);
		rec.Recording(pic);
		//fly.GetImages(pic);


		count++;

		if (CalibrationTool::MainForm::recflg)
		{
			//if (count > fps * 30) 
			{
				leftvec.push_back(pic[0].clone());
				//cv::imshow("Camera_0", pic[0]);
				//cv::waitKey(1);
				rightvec.push_back(pic[1].clone());
				if (size != pic[0].size()) {
					size = pic[0].size();
					stereo.SetImageSize(pic[0]);
				}
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
				//cv::imshow("1", pic[0]);
				//cv::imshow("2", pic[1]);
				//cv::waitKey(1);
			}

			count = 0; 
		}

		// ��ʂ��X�V
		BeginInvoke(gcnew DisplayDelegate(this, &MainForm::Display));
		//Display();
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
	if (!refreshflg)//��ʂ��X�V���Ȃ�
		return;

	int linenum = 20;
	if (!finishcalib || !rectifiedToolStripMenuItem->Checked)
	{
		{
			PictureBox^ pb = pictureBox1;

			Bitmap^ bmp = gcnew Bitmap(pic[0].cols, pic[0].rows, pic[0].step,
				System::Drawing::Imaging::PixelFormat::Format24bppRgb, IntPtr(pic[0].data));

			if (lineToolStripMenuItem->Checked)
			{
				Graphics^g = Graphics::FromImage(bmp);
				SolidBrush^ brush = gcnew SolidBrush(Color::Lime);
				Pen^ pen = gcnew Pen(brush, 1);
				for (int y = 0; y < bmp->Height; y += bmp->Height / linenum) {
					g->DrawLine(pen, 0, y, bmp->Width, y);//���C���̕`��
				}
			}

			pb->Image = bmp;
			pb->Refresh();
		}
		{

			PictureBox^ pb = pictureBox2;

			Bitmap^ bmp = gcnew Bitmap(pic[1].cols, pic[1].rows, pic[1].step,
				System::Drawing::Imaging::PixelFormat::Format24bppRgb, IntPtr(pic[1].data));

			if (lineToolStripMenuItem->Checked)
			{
				Graphics^g = Graphics::FromImage(bmp);
				SolidBrush^ brush = gcnew SolidBrush(Color::Lime);
				Pen^ pen = gcnew Pen(brush, 1);
				for (int y = 0; y < bmp->Height; y += bmp->Height / linenum) {
					g->DrawLine(pen, 0, y, bmp->Width, y);
				}
			}

			pb->Image = bmp;
			pb->Refresh();
		}

	}
	else {

		{
			PictureBox^ pb = pictureBox1;

			Bitmap^ bmp = gcnew Bitmap(rectified[0].cols, rectified[0].rows, rectified[0].step,
				System::Drawing::Imaging::PixelFormat::Format24bppRgb, IntPtr(rectified[0].data));

			if (lineToolStripMenuItem->Checked)
			{
				Graphics^g = Graphics::FromImage(bmp);
				SolidBrush^ brush = gcnew SolidBrush(Color::Lime);
				Pen^ pen = gcnew Pen(brush, 1);
				for (int y = 0; y < bmp->Height; y += bmp->Height / linenum) {
					g->DrawLine(pen, 0, y, bmp->Width, y);
				}
			}

			pb->Image = bmp;
			pb->Refresh();
		}
		{
			PictureBox^ pb = pictureBox2;


			Bitmap^ bmp = gcnew Bitmap(rectified[1].cols, rectified[1].rows, rectified[1].step,
				System::Drawing::Imaging::PixelFormat::Format24bppRgb, IntPtr(rectified[1].data));

			if (lineToolStripMenuItem->Checked)
			{
				Graphics^g = Graphics::FromImage(bmp);
				SolidBrush^ brush = gcnew SolidBrush(Color::Lime);
				Pen^ pen = gcnew Pen(brush, 1);
				for (int y = 0; y < bmp->Height; y += bmp->Height / linenum) {
					g->DrawLine(pen, 0, y, bmp->Width, y);
				}
			}

			pb->Image = bmp;
			pb->Refresh();
		}
	}
	if (!finishcalib)
		MessageLabel->Text = imgcount.ToString();
	else
		MessageLabel->Text = "Reprojection Error=" + rms.ToString();


}

System::Void CalibrationTool::MainForm::CalibrateThread()
{
	Thread^ th = gcnew Thread(gcnew ThreadStart(this, &MainForm::ProgressThread));
	th->IsBackground = true;
	th->Start();

	rms =stereo.StereoCalibrate_byOhara(leftvec,rightvec);
	finishcalib = true;
	//for (int i = 0; i < 100; i++) {
	//	Thread::Sleep(100);
	//	// �i���󋵂Ƃ��ĉ�ʂ��X�V
	//	BeginInvoke(gcnew ProgressDelegate(this, &MainForm::Progress),i);
	//}
	BeginInvoke(gcnew ProgressDelegate(this, &MainForm::Progress), 100);
}

System::Void CalibrationTool::MainForm::Progress(int num)
{
	MainForm::progressBar1->Value = num;
}

System::Void CalibrationTool::MainForm::ProgressEnd(int num)
{
	MainForm::progressBar1->Value = 100;
	MainForm::progressBar1->Visible = false;
}

System::Void CalibrationTool::MainForm::ProgressThread() {

	while(1) {
		Thread::Sleep(1000);
		// �i���󋵂Ƃ��ĉ�ʂ��X�V
		BeginInvoke(gcnew ProgressDelegate(this, &MainForm::Progress),stereo.progress);
		if (finishcalib) {
			BeginInvoke(gcnew ProgressDelegate(this, &MainForm::ProgressEnd), 0);
			break;
		}
	}

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

bool CalibrationTool::MainForm::Stop() {
	{
		int number = 30;
		if (leftvec.size() >= number&&rightvec.size() >= number)
			return true;
		return false;
	}

	{




	}

}