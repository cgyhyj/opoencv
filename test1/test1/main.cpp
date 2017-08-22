#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <opencv2\objdetect\objdetect.hpp>
#include <opencv2\video\video.hpp>

using namespace std;
using namespace cv;

bool dispose(Mat&);
CascadeClassifier face_eye;
Mat dst;
Mat frame;
int i = 1;
int main()
{
	VideoCapture voide(0);
	if (!voide.isOpened())
	{
		printf("打开摄像头失败\n");
		getchar();
		return -1;
	}
	if (!face_eye.load("haarcascade_eye_tree_eyeglasses.xml"))
	{
		printf("打开文件失败\n");
		getchar();
		return -1;
	}
	
	namedWindow("摄像头");
	bool stop = false;
	while(!stop)
	{
		voide>>frame;
		//blur(frame,dst,Size(i,i),Point(-1,-1));
		//GaussianBlur(frame,dst,Size(i,i),0,0);
		//medianBlur(frame,dst,i);
		//bilateralFilter(frame,dst,i,i*2,i/2);
		i+=2;
		if (i >= 30)
			i = 1;
		dispose(dst);
		imshow("摄像头",dst);
		if (waitKey(10)>0)
		{
			stop = true;
		}
	}
	return 0;
}

bool dispose(Mat& photo)
{
	std::vector<Rect> faces;
	face_eye.detectMultiScale(photo,faces,1.1,2,0|CASCADE_SCALE_IMAGE,Size(30,30));
	for ( size_t i = 0; i < faces.size(); i++ )
	{
		Point center( faces[i].x + faces[i].width/2, faces[i].y + faces[i].height/2 );
		ellipse( photo, center, Size( faces[i].width/2, faces[i].height/2 ), 0, 0, 360, Scalar( 0, 0, 255 ), 1, 8, 0 );
	}
	return true;
} 