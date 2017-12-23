#pragma once
#include<iostream>
#include<opencv2\opencv.hpp>
using namespace cv;
using namespace std;


class Train {

public:
	Train(int num) { this->number = num; this->num_pic = 1 + 9 * (number - 1); }
	void load_face(string dirpath);	//根据路径来读取人脸数据
	void get_meanface();//求平均脸以及协方差
	void get_eigen();//求特征值和特征向量
	void get_eigenface(int n);//获得特征脸
	void save_model(int n);//保存训练模型数据PCs
	void load_model(int n,Mat &out);//读取模型数据PCs
	void mytest();//debug用到的测试
	Mat get_raw_mat();//获得原始图片集 矩阵
private:
	Mat raw_mat;//获得原始图片集 矩阵
	Mat cov_mat;//协方差矩阵
	Mat t;
	Mat mean_mat;//均值矩阵
	Mat value;//特征值
	Mat vector;//特征向量
	int row;
	int col;
	int number;
	int num_pic;
	double size;
};
