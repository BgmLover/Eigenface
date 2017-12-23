#pragma once
#include<iostream>
#include<opencv2\opencv.hpp>
using namespace cv;
using namespace std;


class Train {

public:
	Train(int num) { this->number = num; this->num_pic = 1 + 9 * (number - 1); }
	void load_face(string dirpath);
	void get_meanface();
	void get_eigen();
	void get_eigenface(int n);
	void save_model(int n);
	void load_model(int n,Mat &out);
	void mytest();
	Mat get_raw_mat();
private:
	Mat raw_mat;
	Mat cov_mat;
	Mat t;
	Mat mean_mat;
	Mat value;
	Mat vector;
	int row;
	int col;
	int number;
	int num_pic;
	double size;
};
