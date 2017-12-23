#include"getfaces.h"
#include<iostream>

using namespace cv;
using  namespace std;

void on_MouseHandle(int event, int x, int y, int flags, void* param);
void Face::capture(string path, int width, int height, double fx, double fy, double t)
{
	for (int i = 2; i <= 40; i++)
	{
		string name = int_to_string(i);
		name += ".jpg";
		string picurl = path + name;
		namedWindow(name, CV_WINDOW_AUTOSIZE);
		src[i] = imread(picurl);
		setMouseCallback(name, on_MouseHandle, (void*)&cap);
		imshow(name, src[i]);
	}
}
void Face::nornalization()
{
	Mat total = Mat::zeros(height, width, CV_32FC1);
	for (int i = 1; i <= 41; i++)
	{
		string name = int_to_string(i);
		name += ".jpg";
		string picurl = save_path + name;
		Mat src = imread(picurl);
		Mat out;
		src.copyTo(out);
		myRGB2GRAY(src, out);

		Histogram_equalization(out, out);
		
		Mat add;
		out.convertTo(add, CV_32FC1);
		cv::add(total, add, total);
		string grayurl = this->gary_path + name;
		imwrite(grayurl, out);
		cv::resize(out, out, Size(0, 0), 0.25, 0.25);
		string gray4url = this->gray_save_path + name;
		imwrite(gray4url, out);
	}
	total /= 41;
	Mat n;
	total.convertTo(n, CV_8UC1);
	imshow("total", n);
	waitKey(0);
}



void on_MouseHandle(int event, int x, int y, int flags, void* param)
{
	
	params *cap = (params*)param;
	
	switch (event)
	{
	case EVENT_LBUTTONDOWN:
	{
		if ((cap->flag)++ == 0)
			cap->eyes[0] = Point(x, y);
		else
		{
			cap->eyes[1] = Point(x, y);
			cap->flag = 0;
		}
		if (cap->flag == 0)
		{
			(cap->num)++;
			Mat ro, resize, out;
			cap->pic.copyTo(ro);
			int x = cap->eyes[1].x - cap->eyes[0].x;
			int y = cap->eyes[1].y - cap->eyes[0].y;
			double angle = cv::fastAtan2(y, x);
			Point2f center(cap->eyes[0].x, cap->eyes[0].y);
			Mat rot = getRotationMatrix2D(center, angle, 1);
			warpAffine(cap->pic, ro, rot, Size(ro.cols, ro.rows));
			double distance = sqrt((cap->eyes[1].x - cap->eyes[0].x)*(cap->eyes[1].x - cap->eyes[0].x) + (cap->eyes[1].y - cap->eyes[0].y)*(cap->eyes[1].y - cap->eyes[0].y));
			double t = 1.0* 80 / 2 / distance;
			//double ty = tx;
			cout << t << endl;
			cv::resize(ro, resize, Size(0, 0), t, t);
			cout << resize.rows << "  " << resize.cols << endl;
			//imshow("re",resize);
			//imshow("ro", ro);
			Point start;
			start.x = cap->eyes[0].x*t - 20;
			start.y = cap->eyes[1].y*t - 40;
			cout << start << endl;
			out = resize(Range(start.y, start.y + 100), Range(start.x, start.x + 80));
			cout << out.rows << "  " << out.cols;

			string picfix = "resource/face/";
			string name = int_to_string(cap->num);
			name += ".jpg";
			string picurl = picfix + name;
			imwrite(picurl, out);
			imshow("out", out);
		}
		break;
	}
	case EVENT_LBUTTONUP:
	{
		cout << cap->eyes[0] << endl;
		cout << cap->eyes[1] << endl;
		break;
	}
	}
}


