#pragma once
#include<opencv2\opencv.hpp>
#include<vector>
#include"../util/lib.h"


typedef struct  {
	Point eyes[2];
	int flag;
	int num;
	Mat pic;
} params;

class Face {

public:
	string imgdir;
	string save_path;
	string gary_path;
	string gray_save_path;
	int width;
	int height;
	vector<Mat>src;
	Mat mean;
	double fx, fy, t;//第一个眼睛在图像中的位置比例；两只眼睛的距离占比
	Face() {
		this->imgdir = "resource/faces/";
		this->save_path = "resource/face/";
		this->gary_path = "resource/face/gray/";
		this->gray_save_path = "resource/face/gray_4/";
		this->width = 80;
		this->height = 100;
		this->fx = 0.25;
		this->fy = 0.2;
		this->t = 0.5;
		cap.flag = 0;
		cap.num = 0;
	}

	void capture( string path, int width, int height, double fx, double fy, double t);
	void nornalization();
private:
	params cap;
	
};