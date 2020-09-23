#include <stdio.h>
#include <opencv2\opencv.hpp>
#include <string>
#include <iostream>
#include "image_test.h"
#pragma once
using namespace cv;
using namespace std;

// shading 類別的標頭檔
// 僅有 shading 類別的宣告
class shading :public image_test {
	// 宣告 public 的成員
public:
	cv::Mat Ycrcb;
	// 建構函數
	shading(Mat img, string);
	shading() = default;

	void read_spe(string);            // 讀取spec
	void set_maxpt();                 // 找尋最亮點
	void testing();                   // 測試方法
	void record();                    // 紀錄結果
	double bright_mean(int, int);     // 計算座標點下(1/10,1/10)面積平均亮度
	double minmax(int, int, int, int);// 返回最大最小值
	string intervel(int, int, double);// 檢查第三個數值是否在第一第二區間內

	// 宣告 private 的成員
private:
	int max_x, max_y;
	int PassLevel_Up = 110, PassLevel = 74, Diff = 20, Center_Up = 220, Center_Low = 100;
	double Y1_score, Y2_score, Y3_score, Y4_score, Yc_score, diff;
	string result_y1, result_y2, result_y3, result_y4, result_yc, result_diff;
	vector<string> item_name = { "Yc", "Y1", "Y2", "Y3","Y4", "Diff"}, item_score, item_result, item_ucl, item_lcl;
};