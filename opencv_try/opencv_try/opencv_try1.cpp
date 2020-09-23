#include <stdio.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;
using namespace std;

int main() {

	//抓取攝影機
	VideoCapture cap(0);
	//嘗試開啟攝影機
	if (!cap.isOpened()) return -1;

	//用矩陣紀錄抓取的每張frame
	Mat frame;
	//建立一個視窗,名稱為camera
	namedWindow("camera", 1);
	for (;;)
	{
		//把取得的影像放置到矩陣中
		cap >> frame;
		//顯示frame到camera名稱的視窗
		imshow("frame", frame);
		if (waitKey(30) >= 0) break;
	}
	system("PAUSE");
	return 0;
}