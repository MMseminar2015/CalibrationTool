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
std::vector<int> lgoodindex;
std::vector<int> rgoodindex;
std::vector<int> goodindex;
StereoMatching stereo;
System::Void FindChessboardThread();
int imgcount = 0;
double rms = 0;
bool finishcalib = false;
bool foundLeft = false;
bool foundRight = false;
double prerms = 10000;

int state = 0;

void CalibrationTool::MainForm::ReloadPicture()
{
	throw gcnew System::NotImplementedException();
}

System::Void CalibrationTool::MainForm::RecordThread()
{
	recflg = true;

	cv::Size size;
	int a = MainForm::conf.chess_width;
	stereo = StereoMatching(MainForm::conf.chess_width, MainForm::conf.chess_height, MainForm::conf.chess_size);
	

	FlyCap fly = FlyCap(FlyCapture2::VideoMode::VIDEOMODE_640x480YUV422, FlyCapture2::FrameRate::FRAMERATE_30, 30);
	
	int count = 0;
	int index = 0;

	////表示window
	//namedWindow("1", CV_WINDOW_AUTOSIZE);
	//namedWindow("2", CV_WINDOW_AUTOSIZE);

	while (1) {
		//RecordCamera rec;
		//Thread::Sleep(100);
		//rec.Recording(pic);
		fly.GetImages(pic);

		//if(!finishcalib)
		//{
		//	foundLeft = stereo.DetectAllPoints(pic[0]);
		//	foundRight = stereo.DetectAllPoints(pic[1]);
		//}
		//if(foundLeft && foundRight&&!(imgcount > 10)) recflg = true;

		

		if (CalibrationTool::MainForm::recflg)
		{
			//if (count > fps * 30)
			if (count > fps * 30)// && foundLeft && foundRight)
			{
				leftvec.push_back(pic[0].clone());

				rightvec.push_back(pic[1].clone());
				if (size != pic[0].size()) {
					size = pic[0].size();
					stereo.SetImageSize(pic[0]);
				}
				

				//Thread^ th = gcnew Thread(gcnew ParameterizedThreadStart(this, &MainForm::FindChessboardThread));//チェスボード検出
				//th->IsBackground = true;
				//th->Start(index);

				//スレッドプールの利用
				WaitCallback^ waitCallback = gcnew WaitCallback(this,&MainForm::FindChessboardThread);
				ThreadPool::QueueUserWorkItem(waitCallback, index);

				

				finishcalib = false;

				count = 0;
				index++;
			}

			if (imgcount != 0 && imgcount % 20 == 0) {
				Thread^ calbt = gcnew Thread(gcnew ThreadStart(this, &MainForm::CalcReprojectionThread));
				calbt->IsBackground = true;
				calbt->Start();
			}
			
			//30枚撮ったら終了
			if(imgcount > 100)
			{
				recflg = false;
				//MainForm::progressBar1->Visible = true;
				Thread^ calbt = gcnew Thread(gcnew ThreadStart(this, &MainForm::CalibrateThread));
				calbt->IsBackground = true;
				calbt->Start();
			}
			
		}
		else { 
			if (finishcalib)
			{
				stereo.StereoRectify(pic[0], pic[1], rectified[0], rectified[1]);
				//cv::imshow("1", pic[0]);
				//cv::imshow("2", pic[1]);
				//cv::waitKey(1);
				if (viewResultToolStripMenuItem->Checked) {
					Mat disp8;
					if(rectifiedToolStripMenuItem->Checked)
						StereoMatching::Matching(rectified[0], rectified[1], disp8);
					else
						StereoMatching::Matching(pic[0], pic[1], disp8);
					imshow("disparity", disp8);
					waitKey(1);
				}
			}
		}
		count++;

		// 画面を更新
		BeginInvoke(gcnew DisplayDelegate(this, &MainForm::Display));
		//Display();
	}
}

System::Void CalibrationTool::MainForm::FindChessboardThread(Object^ o) 
{
	//左右のvectoy<Mat>のindex番目で検出
	int index = (int)o;
	bool foundLeft = stereo.DetectAllPoints(leftvec[index]);
	bool foundRight = stereo.DetectAllPoints(rightvec[index]);
	if (foundLeft&&foundRight) {
		goodindex.push_back(index);
		imgcount++;
	}
}

System::Void CalibrationTool::MainForm::StereoMatchingThread(Object^ o) {



}

System::Void CalibrationTool::MainForm::Display()
{
	if(foundLeft) textBox1->Text = "found";
	else textBox1->Text = "";
	if (foundRight) textBox2->Text = "found";
	else textBox2->Text = "";
	if(recflg) button_record->Text = "Stop";
	else button_record->Text = "Record";
	//if (!finishcalib) 
	//{
	//	/*{
	//		//Graphics^g = Graphics::FromImage(pictureBox1->Image);
	//		Bitmap^ bmp = gcnew Bitmap(pic[0].cols, pic[0].rows, pic[0].step,
	//			System::Drawing::Imaging::PixelFormat::Format24bppRgb, IntPtr(pic[0].data));
	//		//g->DrawImage(bmp, 0, 0, pic[0].cols, pic[0].rows);
	//		//pictureBox1->Refresh();
	//		//delete g;
	//		pictureBox1->Image = bmp;
	//		pictureBox1->Refresh();
	//	}
	//	{
	//		Bitmap^ bmp = gcnew Bitmap(pic[1].cols, pic[1].rows, pic[1].step,
	//			System::Drawing::Imaging::PixelFormat::Format24bppRgb, IntPtr(pic[1].data));
	//		pictureBox2->Image = bmp;
	//		pictureBox2->Refresh();
	//	}*/
	//	{
	//		cv::Mat img[2];
	//		img[0] = pic[0].clone();
	//		img[1] = pic[1].clone();
	//		for (unsigned int i = 0; i < img[0].rows; i+=50)
	//		{
	//			for (unsigned int j = 0; j < img[0].cols; j++)
	//			{
	//				img[0].at<cv::Vec3b>(i, j)[0] = 0;
	//				img[0].at<cv::Vec3b>(i, j)[1] = 0;
	//				img[0].at<cv::Vec3b>(i, j)[2] = 255;
	//				img[1].at<cv::Vec3b>(i, j)[0] = 0;
	//				img[1].at<cv::Vec3b>(i, j)[1] = 0;
	//				img[1].at<cv::Vec3b>(i, j)[2] = 255;
	//			}
	//		}
	//		Bitmap^ bmp0 = gcnew Bitmap(img[0].cols, img[0].rows, img[0].step,
	//			System::Drawing::Imaging::PixelFormat::Format24bppRgb, IntPtr(img[0].data));
	//		Bitmap^ bmp1 = gcnew Bitmap(img[1].cols, img[1].rows, img[1].step,
	//			System::Drawing::Imaging::PixelFormat::Format24bppRgb, IntPtr(img[1].data));
	//		pictureBox1->Image = bmp0;
	//		pictureBox2->Image = bmp1;
	//		pictureBox1->Refresh();
	//		pictureBox2->Refresh();
	//	}
	//	MessageLabel->Text = imgcount.ToString();
	//}
	//else {
	//	//{
	//	//	//cv::Mat img;
	//	//	//cvtColor(rectified[0], img, CV_GRAY2RGB);
	//	//	Bitmap^ bmp = gcnew Bitmap(rectified[0].cols, rectified[0].rows, rectified[0].step,
	//	//		System::Drawing::Imaging::PixelFormat::Format24bppRgb, IntPtr(rectified[0].data));
	//	//	pictureBox1->Image = bmp;
	//	//	pictureBox1->Refresh();
	//	//}
	//	//{
	//	//	Bitmap^ bmp = gcnew Bitmap(rectified[1].cols, rectified[1].rows, rectified[1].step,
	//	//		System::Drawing::Imaging::PixelFormat::Format24bppRgb, IntPtr(rectified[1].data));
	//	//	pictureBox2->Image = bmp;
	//	//	pictureBox2->Refresh();
	//	//}
	//	{
	//		cv::Mat img[2];
	//		img[0] = rectified[0].clone();
	//		img[1] = rectified[1].clone();
	//		for (unsigned int i = 0; i < img[0].rows; i += 50)
	//		{
	//			for (unsigned int j = 0; j < img[0].cols; j++)
	//			{
	//				img[0].at<cv::Vec3b>(i, j)[0] = 0;
	//				img[0].at<cv::Vec3b>(i, j)[1] = 0;
	//				img[0].at<cv::Vec3b>(i, j)[2] = 255;
	//				img[1].at<cv::Vec3b>(i, j)[0] = 0;
	//				img[1].at<cv::Vec3b>(i, j)[1] = 0;
	//				img[1].at<cv::Vec3b>(i, j)[2] = 255;
	//			}
	//		}
	//		Bitmap^ bmp0 = gcnew Bitmap(img[0].cols, img[0].rows, img[0].step,
	//			System::Drawing::Imaging::PixelFormat::Format24bppRgb, IntPtr(img[0].data));
	//		Bitmap^ bmp1 = gcnew Bitmap(img[1].cols, img[1].rows, img[1].step,
	//			System::Drawing::Imaging::PixelFormat::Format24bppRgb, IntPtr(img[1].data));
	//		pictureBox1->Image = bmp0;
	//		pictureBox2->Image = bmp1;
	//		pictureBox1->Refresh();
	//		pictureBox2->Refresh();
	//	}
	//	MessageLabel->Text = "RSM=" + rms.ToString();
	//}

	if (!refreshflg)//画面を更新しない
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
					g->DrawLine(pen, 0, y, bmp->Width, y);//ラインの描画
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
		MessageLabel->Text = "Recording... "+ imgcount.ToString() + "  rms=" + prerms.ToString();
	else
		MessageLabel->Text = "Reprojection Error=" + rms.ToString();

	
}

System::Void CalibrationTool::MainForm::CalibrateThread()
{
	Thread^ th = gcnew Thread(gcnew ThreadStart(this, &MainForm::ProgressThread));
	th->IsBackground = true;
	th->Start();

	std::vector<cv::Mat> tmpleftvec;
	std::vector<cv::Mat> tmprightvec;
	//チェスボードが見つかったもののみ利用
	for (int i = 0; i < goodindex.size(); i++) {
		tmpleftvec.push_back(leftvec[goodindex[i]]);
		tmprightvec.push_back(rightvec[goodindex[i]]);
	}

	rms =stereo.StereoCalibrate_byOhara(tmpleftvec, tmprightvec);

	leftvec.clear();
	rightvec.clear();

	finishcalib = true;
	//for (int i = 0; i < 100; i++) {
	//	Thread::Sleep(100);
	//	// 進捗状況として画面を更新
	//	BeginInvoke(gcnew ProgressDelegate(this, &MainForm::Progress),i);
	//}
	BeginInvoke(gcnew ProgressDelegate(this, &MainForm::Progress), 100);


}

System::Void CalibrationTool::MainForm::CalcReprojectionThread() {
	std::vector<cv::Mat> tmpleftvec;
	std::vector<cv::Mat> tmprightvec;
	//チェスボードが見つかったもののみ利用
	for (int i = 0; i < goodindex.size(); i++) {
		tmpleftvec.push_back(leftvec[goodindex[i]]);
		tmprightvec.push_back(rightvec[goodindex[i]]);
	}
	if (state == 0) {
		state = 1;
		stereo.MonoCalibrate(tmpleftvec, tmprightvec);
		state = 2;
	}
	while(state==2)

	double rms=stereo.StereoCalibrate_byOhara_Fast(tmpleftvec, tmprightvec);
	prerms = rms;
}

System::Void CalibrationTool::MainForm::Progress(int num)
{
	MainForm::progressBar1->Visible = true;
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
		// 進捗状況として画面を更新
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
