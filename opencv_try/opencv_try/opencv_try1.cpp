#include <stdio.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;
using namespace std;

int main() {

	//�����v��
	VideoCapture cap(0);
	//���ն}����v��
	if (!cap.isOpened()) return -1;

	//�ίx�}����������C�iframe
	Mat frame;
	//�إߤ@�ӵ���,�W�٬�camera
	namedWindow("camera", 1);
	for (;;)
	{
		//����o���v����m��x�}��
		cap >> frame;
		//���frame��camera�W�٪�����
		imshow("frame", frame);
		if (waitKey(30) >= 0) break;
	}
	system("PAUSE");
	return 0;
}