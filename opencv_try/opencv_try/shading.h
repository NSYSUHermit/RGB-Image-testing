#include <stdio.h>
#include <opencv2\opencv.hpp>
#include <string>
#include <iostream>
#include "image_test.h"
#pragma once
using namespace cv;
using namespace std;

// shading ���O�����Y��
// �Ȧ� shading ���O���ŧi
class shading :public image_test {
	// �ŧi public ������
public:
	cv::Mat Ycrcb;
	// �غc���
	shading(Mat img, string);
	shading() = default;

	void read_spe(string);            // Ū��spec
	void set_maxpt();                 // ��M�̫G�I
	void testing();                   // ���դ�k
	void record();                    // �������G
	double bright_mean(int, int);     // �p��y���I�U(1/10,1/10)���n�����G��
	double minmax(int, int, int, int);// ��^�̤j�̤p��
	string intervel(int, int, double);// �ˬd�ĤT�ӼƭȬO�_�b�Ĥ@�ĤG�϶���

	// �ŧi private ������
private:
	int max_x, max_y;
	int PassLevel_Up = 110, PassLevel = 74, Diff = 20, Center_Up = 220, Center_Low = 100;
	double Y1_score, Y2_score, Y3_score, Y4_score, Yc_score, diff;
	string result_y1, result_y2, result_y3, result_y4, result_yc, result_diff;
	vector<string> item_name = { "Yc", "Y1", "Y2", "Y3","Y4", "Diff"}, item_score, item_result, item_ucl, item_lcl;
};