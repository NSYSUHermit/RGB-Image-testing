#include <stdio.h>
#include <opencv2\opencv.hpp>
#include <iostream>
#include <vector>
#include "shading.h"

using namespace std;

// 兩個參數的建構函數
shading::shading(cv::Mat src) {
	// setting img, width & height
	img = src;
	width = src.rows;
	height = src.cols;
	// setting ycrcb
	cvtColor(img, Ycrcb, COLOR_BGR2YCrCb);
}

// setting區域內最亮的pixel點座標
void shading::set_maxpt() {
	Rect ct_roi(height / 4, width / 4, height / 2.5, width / 2.5);
	double bright, max = 0.0;
	for (int y = 0; y < img(ct_roi).rows; y++)
	{
		for (int x = 0; x < img(ct_roi).cols; x++)
		{
			bright = shading::bright_mean(x + img.cols / 4, y + img.rows / 4);
			if (bright > max) {
				max = bright;
				max_x = x;
				max_y = y;
			}
		}
	}
	cout << "maxpt" << max << endl;
}

// setter 與 getter 成員函數
void shading::set_shading() {
	// Define the left-up,left-down,right-up,right-down,center roi
	Rect lu_roi(0, 0, height / 10, width / 10);
	Rect ld_roi(0, 9 * width / 10, height / 10, width / 10);
	Rect ru_roi(9 * height / 10, 0, height / 10, width / 10);
	Rect rd_roi(9 * height / 10, 9 * width / 10, height / 10, width / 10);
	Rect Yc_roi(max_x + height / 4, max_y + width / 4, height / 10, width / 10);

	// bright count
	Y1_score = bright_mean(0, 0);
	Y2_score = bright_mean(9 * height / 10, 0);
	Y3_score = bright_mean(0, 9 * width / 10);
	Y4_score = bright_mean(9 * height / 10, 9 * width / 10);
	Yc_score = bright_mean(max_x, max_y);
	//yscore[4] = {Y1_score,Y2_score,Y3_score,Y4_score};
	//diff = minmax(yscore);

	// image crop plot
	rectangle(img, lu_roi, Scalar(255, 0, 0), 1, LINE_8, 0);
	rectangle(img, ru_roi, Scalar(255, 255, 0), 1, LINE_8, 0);
	rectangle(img, ld_roi, Scalar(0, 255, 255), 1, LINE_8, 0);
	rectangle(img, rd_roi, Scalar(0, 255, 0), 1, LINE_8, 0);
	rectangle(img, Yc_roi, Scalar(255, 0, 255), 1, LINE_8, 0);

	namedWindow("image aaaaa plot", 0);//建全視窗,0
	imshow("image aaaaa plot", img);
	waitKey(0);
}

/*int shading::show_shading() {
	int PassLevel_Up = 110;
	int PassLevel = 74;
	int Diff  = 20;
	int	Center_Up  = 220;
	int	Center_Low = 100;
	// Qualified condition (名稱、數值、上限、下限、PASS / FAIL)
	// Yc
	cout << "Yc," << Yc_score << "," << Center_Up << "," << Center_Low << "," << intervel(Center_Up, Center_Low, Yc_score) << endl
		// Y1
		<< "Y1," << Y1_score << "," << PassLevel_Up << "," << PassLevel << "," << intervel(PassLevel_Up, PassLevel, Y1_score) << endl
		// Y2
		<< "Y2," << Y2_score << "," << PassLevel_Up << "," << PassLevel << "," << intervel(PassLevel_Up, PassLevel, Y2_score) << endl
		// Y3
		<< "Y3," << Y3_score << "," << PassLevel_Up << "," << PassLevel << "," << intervel(PassLevel_Up, PassLevel, Y3_score) << endl
		// Y4
		<< "Y4," << Y4_score << "," << PassLevel_Up << "," << PassLevel << "," << intervel(PassLevel_Up, PassLevel, Y4_score) << endl
		// Diff
		<< "Diff," << diff << "," << Diff << "," << 0 << "," << intervel(Diff, 0, diff) << endl;
}*/

// 計算區域內亮度平均
double shading::bright_mean(int point_x, int point_y) {
	// Define the rectangle
	Rect roi(point_x, point_y, img.cols / 10, img.rows / 10);
	// Crop
	Mat3b Crop = Ycrcb(roi);
	cout << "rows:" << img(ct_roi).rows << ",cols:" << img(ct_roi).cols << endl;
	int n = 0;
	double sum = 0.0, average;
	for (int y = 0; y < Crop.rows; y++)
	{
		for (int x = 0; x < Crop.cols; x++)
		{
			int bright = Crop.at<Vec3b>(y, x)[0];
			sum = sum + bright;
			n = n + 1;
		}
	}
	average = n;
	cout << average << endl;
	return average;
}

void shading::show_img() {
	namedWindow("image fxxx", 0);//建全視窗,0
	imshow("image fxxx", img);
	waitKey(0);
}