#include <stdio.h>
#include <opencv2\opencv.hpp>
#include <iostream>
#include <vector>
#include <string>
#include "flare.h"

// Constructors
flare::flare(cv::Mat src, string file_name) {
	// setting img, width & height
	img = src;
	filename = file_name;
	width = src.rows;
	height = src.cols;
	read_spe(spec_file);
}

// 方法測試
void flare::testing() {
	method = "Flare";

	Rect lu_roi(0, 0, height / 3, width / 3);
	Rect lt_roi(0, width / 3, height / 3, width / 3);
	Rect ld_roi(0, 2 * width / 3, height / 3, width / 3);
	Rect ru_roi(2 * height / 3, 0, height / 3, width / 3);
	Rect rt_roi(2 * height / 3, width / 3, height / 3, width / 3);
	Rect rd_roi(2 * height / 3, 2 * width / 3, height / 3, width / 3);
	Rect up_roi(height / 3, 0, height / 3, width / 3);
	Rect md_roi(height / 3, width / 3, height / 3, width / 3);
	Rect dn_roi(height / 3, 2 * width / 3, height / 3, width / 3);

	lu_result = img_sd(img(lu_roi));
	lt_result = img_sd(img(lt_roi));
	ld_result = img_sd(img(ld_roi));
	ru_result = img_sd(img(ru_roi));
	rt_result = img_sd(img(rt_roi));
	rd_result = img_sd(img(rd_roi));
	up_result = img_sd(img(up_roi));
	md_result = img_sd(img(md_roi));
	dn_result = img_sd(img(dn_roi));

	// image crop plot
	rectangle(img, lu_roi, Scalar(255, 0, 0), 1, LINE_8, 0);
	putText(img, to_string(lu_result), Point(0, 50), FONT_HERSHEY_DUPLEX, 2, Scalar(255, 0, 0), 5);

	rectangle(img, lt_roi, Scalar(255, 255, 0), 1, LINE_8, 0);
	putText(img, to_string(lt_result), Point(0, width / 3 + 50), FONT_HERSHEY_COMPLEX, 2, Scalar(255, 255, 0), 5);

	rectangle(img, ld_roi, Scalar(0, 255, 255), 1, LINE_8, 0);
	putText(img, to_string(ld_result), Point(0, 2 * width / 3 + 50), FONT_HERSHEY_COMPLEX, 2, Scalar(0, 255, 255), 5);

	rectangle(img, ru_roi, Scalar(255, 0, 0), 1, LINE_8, 0);
	putText(img, to_string(ru_result), Point(2 * height / 3, 50), FONT_HERSHEY_DUPLEX, 2, Scalar(255, 0, 0), 5);

	rectangle(img, rt_roi, Scalar(255, 255, 0), 1, LINE_8, 0);
	putText(img, to_string(rt_result), Point(2 * height / 3, width / 3 + 50), FONT_HERSHEY_COMPLEX, 2, Scalar(255, 255, 0), 5);

	rectangle(img, rd_roi, Scalar(0, 255, 255), 1, LINE_8, 0);
	putText(img, to_string(rd_result), Point(2 * height / 3, 2 * width / 3 + 50), FONT_HERSHEY_COMPLEX, 2, Scalar(0, 255, 255), 5);

	rectangle(img, up_roi, Scalar(255, 0, 0), 1, LINE_8, 0);
	putText(img, to_string(up_result), Point(1 * height / 3, 50), FONT_HERSHEY_DUPLEX, 2, Scalar(255, 0, 0), 5);

	rectangle(img, md_roi, Scalar(255, 255, 0), 1, LINE_8, 0);
	putText(img, to_string(md_result), Point(1 * height / 3, width / 3 + 50), FONT_HERSHEY_COMPLEX, 2, Scalar(255, 255, 0), 5);

	rectangle(img, dn_roi, Scalar(0, 255, 255), 1, LINE_8, 0);
	putText(img, to_string(dn_result), Point(1 * height / 3, 2 * width / 3 + 50), FONT_HERSHEY_COMPLEX, 2, Scalar(0, 255, 255), 5);

	if (check(lu_result) == "PASS" && check(ru_result) == "PASS" && check(ld_result) == "PASS" && check(rd_result) == "PASS"&& check(lt_result) == "PASS"&& check(rt_result) == "PASS"&& check(up_result) == "PASS"&& check(md_result) == "PASS"&& check(dn_result) == "PASS") {
		result = "Pass";
	}
	else {
		result = "Fail";
	}
}

//讀取spec檔案
void flare::read_spe(string spec_file) {
	ifstream inFile(spec_file);
	string line;
	while (getline(inFile, line)) // line中不包括每行的換行符
	{
		size_t pos = line.find("=");
		if (pos < 30) {
			if (line.find("threshold =") == 0) {
				string str = line.substr(pos + 2);     // get "threshold" from spec
				threshold = stoi(str);
			}
		}
	}
	inFile.close();
}

// 儲存各項計算紀錄
void flare::record() {
	//定義儲存項
	item_score = { to_string(lu_result),to_string(lt_result), to_string(ld_result), to_string(ru_result), to_string(rt_result),  to_string(rd_result) , to_string(up_result), to_string(md_result),  to_string(dn_result) };
	item_result = {check(lu_result),check(lt_result),check(ld_result),check(ru_result),check(rt_result),check(rd_result) ,check(up_result),check(md_result),check(dn_result)};
	string item_ucl = "0";
	string item_lcl = to_string(threshold);
	//儲存於vector內
	struct note n;
	n.item = report_version; n.status = project_name; svec.push_back(n);
	n.item = "ITEM"; n.status = "STATUS"; n.value = "VALUE"; n.ucl = "UCL"; n.lcl = "LCL"; n.result = "RESULT"; n.spec_name = "SPEC_NAME"; n.date_time = "DATE_NAME"; n.obj_name = "OBJ_NAME"; n.comment = "COMMENT"; n.others = "OTHERS"; svec.push_back(n);
	n.item = method; n.status = "1"; n.value = "0"; n.ucl = "0"; n.lcl = "0"; n.result = result; n.spec_name = spec_file; n.date_time = date_time("ymd-hms"); svec.push_back(n);
	for (int i = 0; i < 6; i++) {
		n.item = item_name[i]; n.status = "1"; n.value = item_score[i]; n.ucl = item_ucl; n.lcl = item_lcl; n.result = item_result[i]; n.spec_name = spec_file; n.date_time = date_time("ymd-hms"); n.obj_name = " "; n.comment = " "; n.others = " ";
		svec.push_back(n);
	}
	n.item = "Flare_FileName"; n.status = "0"; n.value = "0"; n.ucl = "0"; n.lcl = "0"; n.result = "PASS"; n.spec_name = ""; n.date_time = ""; n.obj_name = ""; n.comment = ""; n.others = cwd + "\\" + filename; svec.push_back(n);
	n.others = image_name; svec.push_back(n);
}

//計算圖片內亮度標準差
double flare::img_sd(Mat src) {
	int n = 0;
	double var, mean;
	double sum = 0.0, sum2 = 0.0, gray;
	for (int y = 0; y < src.rows; y++)
	{
		for (int x = 0; x < src.cols; x++)
		{
			gray = (src.at<Vec3b>(y, x)[0] + src.at<Vec3b>(y, x)[1] + src.at<Vec3b>(y, x)[2]) / 3;
			sum += gray;
			sum2 += gray * gray;
			n = n + 1;
		}
	}
	mean = sum / n;
	var = (sum2 / n) - (mean * mean);
	return(sqrt(var));
}

//檢查數值是否超過threshold
string flare::check(double sd) {
	if (sd < threshold) {
		return("FAIL");
	}
	else {
		return("PASS");
	}
}
