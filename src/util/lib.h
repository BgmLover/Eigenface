#include<opencv2\opencv.hpp>
#include<iostream>
using namespace std;
using namespace cv;


void  myRGB2GRAY(Mat src, Mat &out);			//彩色图转灰度图
void Histogram_equalization(Mat src, Mat &out); //直方图均衡化
string int_to_string(int num);					//把一个int数字转为string
Mat mat_row_nto1(Mat src);						//把一个n*m矩阵变成1*(n*m)的矩阵
Mat mat_row_1ton(Mat src,int n);				//把一个1*(n*m)的矩阵变成n*m的矩阵
Mat map_to_0_255(Mat src);						//把一个矩阵的每个元素伸缩映射到0--255值域上
double distance_of_two_matrix(Mat m1, Mat m2);	//求两个矩阵的欧式距离
