#include"lib.h"

Mat map_to_0_255(Mat src)
{
	src.convertTo(src, CV_64FC1);

		double min = 1000;
		double max = -1000;

		for (int j = 0; j < src.cols; j++)
		{
			min = src.at<double>(0, j) < min ? src.at<double>(0, j) : min;
			max = src.at<double>(0, j) > max ? src.at<double>(0, j) : max;
		}
		double y = 255 / (max - min);
		Mat eigenface = src.clone();
		

		for (int j = 0; j < eigenface.cols; j++)
		{
			eigenface.at<double>(0, j) = (eigenface.at<double>(0, j) - min)*y;
		}
		Mat tmp;
		eigenface.convertTo(tmp, CV_8UC1);
		return tmp;
	
}
void  myRGB2GRAY(Mat src, Mat &out)
{
	int row = src.rows;
	int col = src.cols;
	out = Mat(row, col, CV_8UC1, Scalar(0));

	for (int i = 0; i < row; i++)
		for (int j = 0; j < col; j++)
		{
			int temp = src.at<cv::Vec3b>(i, j)[0] * 0.114 + src.at<cv::Vec3b>(i, j)[1] * 0.587 + src.at<cv::Vec3b>(i, j)[2] * 0.299;
			out.at<unsigned char>(i, j) = temp<0 ? 0 : (temp>255 ? 255 : temp);
		}
}
void Histogram_equalization(Mat src, Mat &out)
{
	src.copyTo(out);
	int nk[256];
	double sk[256];
	int i, j;
	for (i = 0; i < 256; i++)
		nk[i] = 0;
	for (i = 0; i<src.rows; i++)
		for (j = 0; j < src.cols; j++)
			nk[src.at<unsigned char>(i, j)] = nk[src.at<unsigned char>(i, j)] + 1;

	int n = src.rows*src.cols;
	sk[0] = nk[0] * 255 / n;
	for (i = 1; i < 256; i++)
		sk[i] = sk[i - 1] + 255 * nk[i] * 1.0 / n;
	for (i = 0; i<src.rows; i++)
		for (j = 0; j < src.cols; j++)
			out.at<unsigned char>(i, j) = sk[src.at<unsigned char>(i, j)];
}
string int_to_string(int num)
{
	stringstream tmp;
	tmp << num;
	string out;
	tmp >> out;
	return out;
}
Mat mat_row_nto1(Mat src) {
	Mat out = src.row(0);
	for (int i = 1; i < src.rows; i++)
		hconcat(out, src.row(i),out);
	return out;
}
Mat mat_row_1ton(Mat src,int n)
{
	int cols = src.cols / n;
	Mat out = src.colRange(0, cols);
	for (int i = 1; i < n; i++)
		vconcat(out, src.colRange(cols*i, cols*i + cols),out);
	return out;
}

double distance_of_two_matrix(Mat m1, Mat m2)
{
	double res = 0;
	m1.convertTo(m1, CV_64FC1);
	m2.convertTo(m2, CV_64FC1);
	for (int j = 0; j < m1.cols; j++)
	{
		res += (m1.at<double>(0, j) - m2.at<double>(0, j))*(m1.at<double>(0, j) - m2.at<double>(0, j));
	}
	return sqrt(res);
}