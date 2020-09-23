#include <stdio.h>
#include <opencv2\opencv.hpp>
#include <iostream>
#pragma once
using namespace cv;

// shading 類別的標頭檔
// 僅有 shading 類別的宣告
class shading {
	// 宣告 public 的成員
	public:
		// 建構函數
		shading(Mat img);

		void set_maxpt();
		void set_shading();
		void show_img();
		void show_shading();
		double bright_mean(int, int);
		
	// 宣告 private 的成員
	private:
		double Y1_score, Y2_score, Y3_score, Y4_score, Yc_score, diff;
		int width;
		int height;
		cv::Mat img;
		cv::Mat Ycrcb;
		int max_x, max_y;
		double yscore[4];
};