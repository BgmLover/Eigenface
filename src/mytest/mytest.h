#pragma once
#include<iostream>
#include<opencv2\opencv.hpp>
using namespace cv;
using namespace std;

class Test {
public:
	Test() { row = 50; col = 50; size = 0.5; }
	Mat model;
	void show_model();
	int test_one(string filename,int no,double threshold,int n);//��������˵ı����ݣ�������в����жϣ�ͬʱ��������ӽ���������ʾ����
	void set_raw_mat(Mat src);
	void cal_verification(int n);
	void do_test1();
	void do_test2();
	int testmode;
	double threshold;
private:
	int row;
	int col;
	double size;
	Mat raw_mat;
	Mat verification;
	
};
