#include"myreconstruct.h"
#include<opencv2\opencv.hpp>
#include"../util/lib.h"
void Reconstruct::do_reconstruct(string filename) {
	src = imread(filename, 0);
	cv::resize(src, src, Size(0, 0), size, size);
	string path = "resource/reconstruct_data/";
	imwrite(path + "src.bmp", src);
	Mat tmp = mat_row_nto1(src);
	tmp.convertTo(tmp, CV_64FC1);

	for (int i = 0; i < 4; i++) {
		Mat use;
		switch (i) {
		case 0:use = model(Range(0, 10), Range(0, model.cols)); break;  //10 PCs
		case 1:use = model(Range(0, 25), Range(0, model.cols)); break;	//25 PCs
		case 2:use = model(Range(0, 50), Range(0, model.cols)); break;	//50 PCs
		case 3:use = model(Range(0, 100), Range(0, model.cols)); break;	//100 PCs
		}
		Mat cal = tmp * use.t();
		Mat res = cal*use;
		res.convertTo(res, CV_8UC1);
		Mat show = mat_row_1ton(res, row);
		imshow(int_to_string(i), show);
		int no = i == 0 ? 10 : i == 1 ? 25 : i == 2 ? 50 : 100;
		string name = "reconstruct_" + int_to_string(no)+".bmp";
		imwrite(path+name, show);
	}



}