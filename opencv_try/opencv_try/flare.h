#include <stdio.h>
#include <opencv2\opencv.hpp>
#include <string>
#include <iostream>
#include "image_test.h"

#pragma once
using namespace cv;
using namespace std;

// flare header class 
// flare class delcare
class flare: public image_test {
// declare public members
public:
	// Constructors
	flare(Mat img, string);
	flare() = default;

	void read_spe(string); // Ū��spec�ɮ�
	void testing();        // ���դ�k
	void record();         // �������G
	
	double img_sd(Mat src);// �p��Ϥ����G�׼зǮt
	string check(double);  // �ˬd�ƭȬO�_�W�Lthreshold

// declare private members
private:
	int i;
	int threshold = 85;
	double lu_result, lt_result, ld_result, ru_result, rt_result, rd_result, up_result, md_result, dn_result;
	string ans;
	vector<string> item_name = { "left-up", "left", "left-down", "right-up","right", "right-down" ,"up" ,"mid" ,"down" }, item_score, item_result;
};
