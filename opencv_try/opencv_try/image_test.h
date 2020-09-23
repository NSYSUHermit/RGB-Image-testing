#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <opencv2\opencv.hpp>
#include <string>
#include <iostream>
#include <ctime>
#include <vector>

#pragma once
using namespace cv;
using namespace std;

// image_test header class 
// image_test class delcare
class image_test {
	// declare public members
public:
	// �x�s���絲�G��struct
	struct note {
		string item, status, value, ucl, lcl, result, spec_name, date_time, obj_name, comment, others;
	};

	cv::Mat img;
	int width, height; 	 
	
	string spec_file = "DataSet\\DITCameraTestApp\\CameraSpec.spe", ini_file = "DataSet\\DITCameraTestApp\\ASUS_Camera_SerialNum.ini";
	string result, method, path, image_name, cwd,filename, report_version = "Report_Version:1.0.9.4", project_name = "Project_Name : DIT_NewMember_Demo_version", serialnum;
	vector<string> testing_result;
	vector<struct note> svec;

	virtual void read_spe(string) = 0; // �w�qŪ��spec�ɤ����Ѽ�
	virtual void testing() = 0;        // �w�q�U���դ�k
	virtual void record() = 0;         // �w�q�������G

	string zero_padding(int);          // �N�Ӧ�Ʀr��0
	string date_time(string);          // ��ܮɶ�
	
	void text_matrix(string);          // ��r�I�x�}
	void read_ini();                   // ���.ini�ɮפ��s��
	void path_setting();               // �]�w���|
	void result_img();                 // �x�s�Ϥ�
	void result_csv();                 // �x�scsv
	void show();                       // ��ܵ��G��T
};
