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

	void read_spe(string); // 讀取spec檔案
	void testing();        // 測試方法
	void record();         // 紀錄結果
	
	double img_sd(Mat src);// 計算圖片內亮度標準差
	string check(double);  // 檢查數值是否超過threshold

// declare private members
private:
	int i;
	int threshold = 85;
	double lu_result, lt_result, ld_result, ru_result, rt_result, rd_result, up_result, md_result, dn_result;
	string ans;
	vector<string> item_name = { "left-up", "left", "left-down", "right-up","right", "right-down" ,"up" ,"mid" ,"down" }, item_score, item_result;
};
