#include <stdio.h>
#include <opencv2\opencv.hpp>
#include <string>
#include <iostream>
#include "image_test.h"
#pragma once
using namespace cv;
using namespace std;

// blemish header class 
// blemish class delcare
class blemish: public image_test {
	// declare public members
public:
	// Constructors
	blemish(Mat img, string);
	blemish() = default;

	void read_spe(string);// Ū��spec��  
	void set_morphology();// �Ϥ��B�z
	void testing();       // ���դ�k
	void record();        // �������G

	// declare private members
private:
	cv::Mat out, gray, binary;
	int i;
	int min_area = 50000, max_area = 200000; // area threshold
	vector<vector<Point>> contours;
};
