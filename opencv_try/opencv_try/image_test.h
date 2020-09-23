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
	// 儲存測驗結果的struct
	struct note {
		string item, status, value, ucl, lcl, result, spec_name, date_time, obj_name, comment, others;
	};

	cv::Mat img;
	int width, height; 	 
	
	string spec_file = "DataSet\\DITCameraTestApp\\CameraSpec.spe", ini_file = "DataSet\\DITCameraTestApp\\ASUS_Camera_SerialNum.ini";
	string result, method, path, image_name, cwd,filename, report_version = "Report_Version:1.0.9.4", project_name = "Project_Name : DIT_NewMember_Demo_version", serialnum;
	vector<string> testing_result;
	vector<struct note> svec;

	virtual void read_spe(string) = 0; // 定義讀取spec檔中的參數
	virtual void testing() = 0;        // 定義各測試方法
	virtual void record() = 0;         // 定義紀錄結果

	string zero_padding(int);          // 將個位數字補0
	string date_time(string);          // 顯示時間
	
	void text_matrix(string);          // 文字點矩陣
	void read_ini();                   // 抓取.ini檔案內編號
	void path_setting();               // 設定路徑
	void result_img();                 // 儲存圖片
	void result_csv();                 // 儲存csv
	void show();                       // 顯示結果資訊
};
