#include<opencv2\opencv.hpp>
#include<iostream>
using namespace std;
using namespace cv;


void  myRGB2GRAY(Mat src, Mat &out);			//��ɫͼת�Ҷ�ͼ
void Histogram_equalization(Mat src, Mat &out); //ֱ��ͼ���⻯
string int_to_string(int num);					//��һ��int����תΪstring
Mat mat_row_nto1(Mat src);						//��һ��n*m������1*(n*m)�ľ���
Mat mat_row_1ton(Mat src,int n);				//��һ��1*(n*m)�ľ�����n*m�ľ���
Mat map_to_0_255(Mat src);						//��һ�������ÿ��Ԫ������ӳ�䵽0--255ֵ����
double distance_of_two_matrix(Mat m1, Mat m2);	//�����������ŷʽ����
