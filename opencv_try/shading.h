#include <stdio.h>
#include <opencv2\opencv.hpp>
#include <iostream>
#pragma once
using namespace cv;

// shading ���O�����Y��
// �Ȧ� shading ���O���ŧi
class shading {
	// �ŧi public ������
	public:
		// �غc���
		shading(Mat img);

		void set_maxpt();
		void set_shading();
		void show_img();
		void show_shading();
		double bright_mean(int, int);
		
	// �ŧi private ������
	private:
		double Y1_score, Y2_score, Y3_score, Y4_score, Yc_score, diff;
		int width;
		int height;
		cv::Mat img;
		cv::Mat Ycrcb;
		int max_x, max_y;
		double yscore[4];
};