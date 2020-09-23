#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <opencv2\opencv.hpp>
#include <iostream>
#include <vector>
#include <ctime>
#include <direct.h>
#include "image_test.h"

//將個位數字補0
string image_test::zero_padding(int num) { 
	if (num > 9) {
		return to_string(num);
	}
	else {
		return "0"+to_string(num);
	}
}

//顯示時間
string image_test::date_time(string tenet) { 
	time_t now = time(0);
	tm *ltm = localtime(&now);
	if (tenet == "ymd") {
		return(zero_padding(1900 + ltm->tm_year) + zero_padding(1 + ltm->tm_mon) + zero_padding(ltm->tm_mday));
	}
	else if(tenet == "ymdhms") {
		return(zero_padding(1900 + ltm->tm_year) + zero_padding(1 + ltm->tm_mon) + zero_padding(ltm->tm_mday)+ zero_padding(ltm->tm_hour) + zero_padding(ltm->tm_min) + zero_padding(ltm->tm_sec));
	}
	else if (tenet == "ymd-hms") {
		return(zero_padding(1900 + ltm->tm_year) + zero_padding(1 + ltm->tm_mon) + zero_padding(ltm->tm_mday) + " " + zero_padding(ltm->tm_hour) + zero_padding(ltm->tm_min) + zero_padding(ltm->tm_sec));
	}
}

//文字點矩陣
void image_test::text_matrix(string word) { 
	int i, j, k, bit, no;
	int bitmap[26][5] = {
	{6,9,15,9,9} , {14,9,14,9,14} ,{6,9,8,9,6}   ,
	{14,9,9,9,14}, {15,8,14,8,15} ,{15,8,14,8,8} ,
	{7,8,11,9,6} , {9,9,15,9,9}   ,{7,2,2,2,7}   ,
	{7,2,2,10,14}, {9,10,12,10,9} ,{8,8,8,9,15}  ,
	{9,15,9,9,9} , {9,13,11,9,9}  ,{6,9,9,9,6}   ,
	{14,9,14,8,8}, {15,9,13,11,15},{14,9,14,10,9},
	{7,8,6,1,14} , {15,2,2,2,2}   ,{9,9,9,9,15}  ,
	{9,9,9,9,6}  , {9,9,9,15,9}   ,{9,9,6,9,9}   ,
	{9,9,7,1,14} , {15,1,2,4,15} };
	cout << '\n';
	string line_map;
	for (i = 0; i < 5; ++i) {
		for (j = 0; j < word.size(); ++j) {
			no = word[j] - 'A';
			bit = bitmap[no][i];
			for (k = 0; k < 4; ++k) {
				line_map += (bit&(8 >> k) ? "*" : " ");
			}
			line_map += " ";
		}
		cout << line_map << endl;
		line_map = "";
	}
}

//抓取.ini檔案內編號
void image_test::read_ini() {
	ifstream inFile(ini_file);
	string line;
	while (getline(inFile, line))
	{
		size_t pos = line.find("=");
		if (pos < 30) {
			if (line.find("SerialNum =") == 0) {
				serialnum = line.substr(pos + 2);     // get "SerialNum" from .ini
			}
		}
	}
	inFile.close();
}

// 設定路徑
void image_test::path_setting() {
	char* buffer;
	// Get the current working directory:
	if ((buffer = _getcwd(NULL, 0)) == NULL)
		perror("_getcwd error");
	else
	{
		read_ini();
		time_t now = time(0);
		tm *ltm = localtime(&now);
		string command = "mkdir ";
		path = buffer;
		cwd = buffer;
		path += "\\ASUS_Camera_Reports_DLL\\";
		path += date_time("ymd") + "\\" + serialnum;
		command += path;
		system(command.c_str());
	}
}

//儲存圖片
void image_test::result_img() {
	time_t now = time(0);
	tm *ltm = localtime(&now);
	string jpg_name = serialnum, jpg = "-Debug.jpg";
	jpg_name += "-" + date_time("ymdhms");
	jpg_name += "-" + result + "-" + method+ jpg;
	path += "\\";
	image_name = path + jpg_name;
	imwrite(path + jpg_name, img);
}

//儲存csv
void image_test::result_csv() {
	string csv_name = "Report-", csv = ".csv";
	csv_name += serialnum;
	csv_name += "-" + date_time("ymdhms");
	csv_name += csv;
	path += "\\";

	// write the csv file
	ofstream csvfile;
	csvfile.open(path + csv_name);
	vector<struct note>::iterator iter = svec.begin();
	for (iter; iter != svec.end(); ++iter){
		csvfile << iter->item << "," << iter->status << "," << iter->value << "," << iter->ucl << "," << iter->lcl << "," << iter->result << "," << iter->spec_name << "," << iter->date_time << "," << iter->obj_name << "," << iter->comment << "," << iter->others << endl;
	}
	csvfile.close();
}

//顯示結果資訊
void image_test::show() {
	cout << "ATD Line：" << svec.size() - 4 << endl;
	vector<struct note>::iterator iter = svec.begin()+2;
	for (iter; iter != svec.end() - 2; ++iter)
		cout << iter->item << "," << iter->status << "," << iter->value << "," << iter->ucl << "," << iter->lcl << "," << iter->result << endl;
	if (result == "Pass") {
		text_matrix("PASS");
	}
	else {
		text_matrix("FAIL");
	}
	namedWindow("Result", 0);
	imshow("Result", img);
	waitKey(0);
}