#pragma once
#include<iostream>
#include<opencv2\opencv.hpp>
using namespace cv;
using namespace std;

class Reconstruct {
public:
	Reconstruct() { row = 50; col = 50; size = 0.5; }
	Mat model;
	void do_reconstruct(string filename);
private:
	int row;
	int col;
	double size;
	Mat src;
	vector<Mat> reconstruct;
};
