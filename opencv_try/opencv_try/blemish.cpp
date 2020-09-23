#include <stdio.h>
#include <opencv2\opencv.hpp>
#include <iostream>
#include <vector>
#include <string>
#include "blemish.h"

// Constructors
blemish::blemish(cv::Mat src,string file_name) {
	// setting img, width & height
	img = src;
	width = src.rows;
	height = src.cols;
	filename = file_name;
	read_spe(spec_file);

	// setting binary
	GaussianBlur(src, out, Size(3, 3), 0, 0);// Gaussian Blur
	cvtColor(out, gray, COLOR_BGR2GRAY);
	threshold(gray, binary, 0, 255, THRESH_BINARY_INV | THRESH_OTSU);
	set_morphology();
}

// 讀取spec檔
void blemish::read_spe(string spec_file) {
	ifstream inFile(spec_file);
	string line;
	while (getline(inFile, line))
	{
		size_t pos = line.find("=");
		if (pos < 30) {
			if (line.find("min_area =") == 0) {
				string str3 = line.substr(pos + 2);     // get "min_area" from spec
				min_area = stoi(str3);
			}
		}
		else if (pos < 30) {
			if (line.find("max_area =") == 0) {
				string str3 = line.substr(pos + 2);     // get "max_area" from  spec
				max_area = stoi(str3);
			}
		}
	}
	inFile.close();
}

// image Morphology
void blemish::set_morphology() {
	Mat di;
	Mat se = getStructuringElement(MORPH_RECT, Size(3, 3));
	Mat element(7, 7, CV_8U, Scalar(1));
	erode(binary, di, element);//侵蝕
	morphologyEx(di, di, MORPH_OPEN, se);
}

//測試方法
void blemish::testing() {
	method = "Blemish";
	// contour
	vector<Vec4i> hierarchy;
	findContours(binary, contours, hierarchy, RETR_LIST, CHAIN_APPROX_SIMPLE);
	vector<Moments> mu(contours.size());
	i = 0;
	for (size_t t = 0; t < contours.size(); t++) {
		double area = contourArea(contours[t], false); //  Find the area of contour
		if (area > min_area && area < max_area) { // Limit the bound of contour
			Rect rect = boundingRect(contours[t]);
			double area = contourArea(contours[t]);
			if (rect.height > (height / 2)) {
				continue;
			}
			if (area < 150) {
				continue;
			}
			// 繪製外接矩形
			rectangle(img, rect, Scalar(0, 0, 255), 2);
			// 繪製輪廓
			drawContours(img, contours, t, Scalar(0, 255, 0), 2);
			i = i + 1;
		}
	}
	putText(img, "Total blemish:" + to_string(i), Point(height / 10, width / 10), FONT_HERSHEY_COMPLEX, 3, Scalar(205, 235, 255), 5);
	if (i > 0) { result = "Fail"; }
	else { result = "Pass"; }
}

//紀錄結果
void blemish::record() {
	struct note n;
	n.item = report_version; n.status = project_name; svec.push_back(n);
	n.item = "ITEM"; n.status = "STATUS"; n.value = "VALUE"; n.ucl = "UCL"; n.lcl = "LCL"; n.result = "RESULT"; n.spec_name = "SPEC_NAME"; n.date_time = "DATE_NAME"; n.obj_name = "OBJ_NAME"; n.comment = "COMMENT"; n.others = "OTHERS"; svec.push_back(n);
	n.item = method; n.status = "1"; n.value = "0"; n.ucl = "0"; n.lcl = "0"; n.result = result; n.spec_name = spec_file; n.date_time = date_time("ymd-hms"); svec.push_back(n);

	int num = 1;
	for (size_t t = 0; t < contours.size(); t++) {
		string result_item = "FAIL";
		double area = contourArea(contours[t], false); //  Find the area of contour
		if (area > min_area && area < max_area) { // Limit the bound of contour
			result_item = "PASS";
			n.item = "contourArea" + to_string(num); n.status = "1"; n.value = to_string(int(area)); n.ucl = to_string(max_area); n.lcl = to_string(min_area); n.result = result; n.spec_name = spec_file; n.date_time = date_time("ymd-hms"); n.obj_name = " "; n.comment = " "; n.others = " ";
			svec.push_back(n);
		}
		num = num + 1;
	}
	n.item = "Blemish_FileName"; n.status = "0"; n.value = "0"; n.ucl = "0"; n.lcl = "0"; n.result = "PASS"; n.spec_name = ""; n.date_time = ""; n.obj_name = ""; n.comment = ""; n.others = cwd + "\\" + filename; svec.push_back(n);
	n.others = image_name; svec.push_back(n);
}



