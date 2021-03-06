#pragma once
#pragma once

#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/contrib/contrib.hpp"
//#include "opencv2/imgcodecs.hpp"

#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <iterator>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

using namespace cv;
using namespace std;

class StereoMatching
{
public:
	enum { STEREO_BM = 0, STEREO_SGBM = 1, STEREO_HH = 2, STEREO_VAR = 3 };

	Mat CameraMatrix[2], DistCoeffs[2];
	Mat R, T, F, E;
	Mat R1, R2, P1, P2, Q;
	Rect ValidRoi[2];
	Mat Rmap[2][2]; // イメージ変換の行列

	Size ImageSize;

	Size BoardSize;
	float SquareSize;

	vector<vector<Point3f>> ObjectPoints;
	vector<vector<Point2f>> ImagePoints[2];
	//vector<vector<Point2f>> ImagePoints[2];
	//vector<vector<Point3f>> ObjectPoints[2];

	vector<vector<Point3f>> MonoObjectPoints[2];
	vector<vector<Point2f>> MonoImagePoints[2];

	int progress;

	StereoMatching();
	~StereoMatching();
	StereoMatching::StereoMatching(int boardwidth, int boardheight, float squaresize);


	int Matching(
		string img1_filepatth, string imd2_filepath,
		char* algorithm = "bm",
		int maxdisp_opt = 0,
		int blocksize_opt = 0,
		float scale_opt = 1.f,
		bool nodisplay = false,
		char* intrinsicfilename = 0,
		char* extrinsicfilename = 0,
		char* disparityfilename = 0,
		char* pointcloud_filename = 0);

	static int Matching(
		Mat &img1, Mat &img2, Mat &disp8, int alg);

	static void StereoCalibrate(
		const vector<string>& imagelist,
		Size boardSize,
		bool displayCorners = false,
		bool useCalibrated = true,
		bool showRectified = true);


	bool DetectObjectPoints(
		Mat img,
		Size imgSize,
		Size boardSize,		// チェッカーボードのサイズ
		float squareSize,	// チェッカーボードのスクエアサイズ
		vector<Point3f>& objectPoint,
		vector<Point2f>& corners);

	bool DetectObjectPointsForStereoCamera2(
		Mat img1, Mat img2,
		Size imgSize,
		Size boardSize,		// チェッカーボードのサイズ
		float squareSize,	// チェッカーボードのスクエアサイズ
		vector<vector<Point3f>> ObjectPoints[2],
		vector<vector<Point2f>> ImagePoints[2]);
	bool DetectObjectPointsForStereoCamera(Mat *img);
	bool CalibrateStereoCamera(vector<Mat*> imgs, vector<Mat*>& RimgPairList);

	int MonoCalibrate(
		vector<vector<Point3f>> objectPoints,
		vector<vector<Point2f>> imagePoints,
		Size imageSize,
		Mat& cameraMatrix, Mat& distCoeffs,
		vector<Mat>& rvecs, vector<Mat>& tvecs);

	int StereoCalibrate2();
	double StereoCalibrate();

	double StereoCalibrate_byOhara(std::vector<cv::Mat> leftvec, std::vector<cv::Mat> rightvec);

	double StereoCalibrate_byOhara_Fast(std::vector<cv::Mat> leftvec, std::vector<cv::Mat> rightvec);
	int MonoCalibrate(std::vector<cv::Mat> leftvec, std::vector<cv::Mat> rightvec);

	int StereoRectify(Mat img1, Mat img2, Mat& rimg1, Mat& rimg2);

	int SetImageSize(Mat img);
	int SetBoardSize(int boardwidth, int boardheight);

	bool OutputExtrinsicParameter(std::string outputfile);
	bool OutputIntrinsicParameter(std::string outputfile);
	bool OutputRectifyParameter(std::string outputfile);
	bool InputExtrinsicParameter(std::string inputfile);
	bool InputIntrinsicParameter(std::string inputfile);
	bool InputRectifyParameter(std::string inputfile);

	bool DetectAllPoints(cv::Mat img);
};