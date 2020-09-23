#include <stdio.h>
#include <opencv2\opencv.hpp>
#include <iostream>
#include <vector>
#include "shading.h"

using namespace std;

// mat參數的建構函數
shading::shading(cv::Mat src, string file_name) {
	// setting img, width & height
	img = src;
	width = src.rows;
	height = src.cols;
	filename = file_name;
	// setting ycrcb
	cvtColor(img, Ycrcb, COLOR_BGR2YCrCb);
	// setting max point location
	set_maxpt();
	read_spe(spec_file);
}

// 讀取spec檔並獲得有關shading的參數
void shading::read_spe(string spec_file) {
	ifstream inFile(spec_file);
	string line;
	while (getline(inFile, line))
	{
		size_t pos = line.find("=");
		if (pos < 30) {
			if (line.find("PassLevel_Up =") == 0) {
				string str3 = line.substr(pos + 2);     // get "PassLevel_Up" from spec
				PassLevel_Up = stoi(str3);
			}
			else if (line.find("PassLevel =") == 0) {
				string str3 = line.substr(pos + 2);     // get "PassLevel" from spec
				PassLevel = stoi(str3);
			}
			else if (line.find("Diff =") == 0) {
				string str3 = line.substr(pos + 2);     // get "Diff" from spec
				Diff = stoi(str3);
			}
			else if (line.find("Center_Up =") == 0) {
				string str3 = line.substr(pos + 2);     // get "Center_Up" from spec
				Center_Up = stoi(str3);
			}
			else if (line.find("Center_Low =") == 0) {
				string str3 = line.substr(pos + 2);     // get "Center_Low" from spec
				Center_Low = stoi(str3);
			}
		}
	}
	inFile.close();
}

// 找出區域內最亮區域的座標點
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
}

// 測試主項
void shading::testing() {
	method = "Shading";

	// Define the left-up,left-down,right-up,right-down,center roi
	Rect lu_roi(0, 0, height / 10, width / 10);
	Rect ld_roi(0, 9 * width / 10, height / 10, width / 10);
	Rect ru_roi(9 * height / 10, 0, height / 10, width / 10);
	Rect rd_roi(9 * height / 10, 9 * width / 10, height / 10, width / 10);
	Rect Yc_roi(max_x + height / 4, max_y + width / 4, height / 10, width / 10);

	// bright count
	double Y1_bright = bright_mean(0, 0);
	double Y2_bright = bright_mean(9 * height / 10, 0);
	double Y3_bright = bright_mean(0, 9 * width / 10);
	double Y4_bright = bright_mean(9 * height / 10, 9 * width / 10);
	Yc_score = bright_mean(max_x + height / 4, max_y + width / 4);
	
	// score count
	Y1_score = 100 * Y1_bright/ Yc_score;
	Y2_score = 100 * Y2_bright / Yc_score;
	Y3_score = 100 * Y3_bright / Yc_score;
	Y4_score = 100 * Y4_bright / Yc_score;
	diff = minmax(Y1_score, Y2_score, Y3_score, Y4_score);

	// image crop plot
	rectangle(img, lu_roi, Scalar(255, 0, 0), 1, LINE_8, 0);
	putText(img, "Y1", Point(0, width / 10 -20), FONT_HERSHEY_COMPLEX, 1, Scalar(255, 0, 0), 5);

	rectangle(img, ru_roi, Scalar(255, 255, 0), 1, LINE_8, 0);
	putText(img, "Y2", Point(9 * height / 10, width / 10 - 20), FONT_HERSHEY_COMPLEX, 1, Scalar(255, 255, 0), 5);

	rectangle(img, ld_roi, Scalar(0, 255, 255), 1, LINE_8, 0);
	putText(img, "Y3", Point(0, width - 20), FONT_HERSHEY_COMPLEX, 1, Scalar(0, 255, 255), 5);

	rectangle(img, rd_roi, Scalar(0, 255, 0), 1, LINE_8, 0);
	putText(img, "Y4", Point(9 * height / 10,width - 20), FONT_HERSHEY_COMPLEX, 1, Scalar(0, 255, 0), 5);

	rectangle(img, Yc_roi, Scalar(255, 0, 255), 1, LINE_8, 0);
	putText(img, "Yc", Point(max_x + height / 4, max_y + width*0.35 - 20), FONT_HERSHEY_COMPLEX, 1, Scalar(255, 0, 255), 5);

	// 判斷亮度是否落於區間內
	result_yc = intervel(Center_Up, Center_Low, Yc_score);
	result_y1 = intervel(PassLevel_Up, PassLevel, Y1_score);
	result_y2 = intervel(PassLevel_Up, PassLevel, Y2_score);
	result_y3 = intervel(PassLevel_Up, PassLevel, Y3_score);
	result_y4 = intervel(PassLevel_Up, PassLevel, Y4_score);
	result_diff = intervel(Diff, 0, diff);

	// 定義總測項是否合格
	if (result_diff == "PASS" && result_y1 == "PASS" && result_y2 == "PASS" && result_y3 == "PASS" && result_y4 == "PASS" && result_yc == "PASS") {
		result = "Pass";
	}
	else {
		result = "Fail";
	}
}

// 儲存紀錄於svec中
void shading::record() {
	// 儲存各項計算紀錄
	item_score = { to_string(Yc_score),to_string(Y1_score), to_string(Y2_score), to_string(Y3_score), to_string(Y4_score),  to_string(diff) };
	item_result = { result_yc,result_y1, result_y2, result_y3, result_y4, result_diff };
	item_ucl = { to_string(Center_Up),to_string(PassLevel_Up), to_string(PassLevel_Up), to_string(PassLevel_Up), to_string(PassLevel_Up),  to_string(Diff) };
	item_lcl = { to_string(Center_Low),to_string(PassLevel), to_string(PassLevel), to_string(PassLevel), to_string(PassLevel),  "0" };

	struct note n;
	n.item = report_version; n.status = project_name; svec.push_back(n);
	n.item = "ITEM"; n.status = "STATUS"; n.value = "VALUE";n.ucl = "UCL"; n.lcl = "LCL"; n.result = "RESULT"; n.spec_name = "SPEC_NAME"; n.date_time = "DATE_NAME";n.obj_name="OBJ_NAME";n.comment= "COMMENT";n.others = "OTHERS"; svec.push_back(n);
	n.item = method; n.status = "1"; n.value = "0"; n.ucl = "0"; n.lcl = "0"; n.result = result; n.spec_name = spec_file; n.date_time = date_time("ymd-hms"); svec.push_back(n);

	for (int i = 0; i < 6; i++) {
		n.item = item_name[i]; n.status = "1"; n.value = item_score[i];n.ucl = item_ucl[i]; n.lcl = item_lcl[i]; n.result = item_result[i]; n.spec_name = spec_file; n.date_time = date_time("ymd-hms"); n.obj_name = " "; n.comment = " "; n.others = " ";
		svec.push_back(n);
	}
	n.item = "Shading_FileName"; n.status = "0"; n.value = "0"; n.ucl = "0"; n.lcl = "0"; n.result = "PASS"; n.spec_name = ""; n.date_time = ""; n.obj_name = ""; n.comment = ""; n.others = cwd + "\\" + filename; svec.push_back(n);
	n.others = image_name; svec.push_back(n);
}

// 計算數列中最大數與最小數的差
double shading::minmax(int a, int b, int c, int d) {
	double nums[4] = {a,b,c,d};
	double min = 1000, max = 0;
	for (int i = 0; i < 4; i++) {
		if (nums[i] > max) {
			max = nums[i];
		}
		if (nums[i] < min) {
			min = nums[i];
		}
	}
	return max - min;
}

// 計算數字是否落於區間內
string shading::intervel(int upper, int lower, double num) {
	if (num <= upper && num >= lower) {
		return("PASS");
	}
	else {
		return("FAIL");
	}
}

// 計算區域內亮度平均
double shading::bright_mean(int point_x, int point_y) {
	// Define the rectangle
	Rect roi(point_x, point_y, img.cols / 10, img.rows / 10);
	// Crop
	Mat3b Crop = Ycrcb(roi);
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
	average = sum/n;
	return average;
}