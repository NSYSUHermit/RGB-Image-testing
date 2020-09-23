#include "blemish.h"
#include "flare.h"
#include "shading.h"
#include <stdio.h>
#include <opencv2\opencv.hpp>
#include <iostream>			
#include <vector>

using namespace cv;
using namespace std;

// run test main()
int main(int argc, char *argv[]) {
	if (argc < 1) {
		cout << "請輸入格式為(執行檔 -方法 圖片名稱)的格式" << endl;
	}
	// read jpg file
	string filename = argv[2];
	//cout << "請輸入檔名(包含副檔名):" << endl;
	//cin >> filename;
	Mat img = imread(filename);
	if (img.empty()) {
		cout << "無法讀取的圖片名稱，請輸入格式為(執行檔 -方法 圖片名稱)的格式" << endl;
		char item[][80]{""};
		cout << item[0];
		system("pause");
		return 0;
	}
// declare and bulid the obj t of image_test
	image_test *run_test = NULL;
	string input = argv[1];
	{
		//cout << "請選擇要執行的方法，Blemish(-BL)、Flare(-FL)、Shading(-LS):";
		//cin >> input;
		if (input == "-BL")
		{
			run_test = new blemish(img, filename);
		}
		else if (input == "-FL")
		{
			run_test = new flare(img, filename);
		}
		else if (input == "-LS")
		{
			run_test = new shading(img, filename);
		}
		else
		{
			cout << "請輸入格式為(執行檔 -方法 圖片名稱)的格式" << endl;
			system("pause");
			return 0;
		}
		// 先測試圖片，接著設定儲存路徑、儲存圖片、紀錄數值資料、寫出CSV、顯示數值結果與圖片
		run_test-> testing();
		run_test-> path_setting();
		run_test-> result_img();
		run_test-> record();
		run_test-> result_csv();
		run_test-> show();
		delete run_test;
		cout << endl;
	}
	system("pause");
	return 0;
}
