#include"mytest.h"
#include"../mytrain/mytrain.h"
#include"../util/lib.h"
#include<fstream>
void Test::show_model() {
	for (int i = 0; i < model.rows; i++)
	{
		Mat eigenface = map_to_0_255(model.row(i));
		Mat show = mat_row_1ton(eigenface,row);
		string name = int_to_string(i);
		name = "eigenface" + name;
		name += ".jpg";
		imshow(name, show);
	}
}
void Test::cal_verification(int n) {
	Mat tmp = model(Range(0, n), Range(0, model.cols));
	this->verification = raw_mat*tmp.t();
}
int  Test::test_one(string filename, int no ,double threshold,int n)
{
	Mat test_src = imread(filename, 0);
	cv::resize(test_src, test_src, Size(0, 0), size, size);
	Mat show1 = test_src.clone();
	//imshow("src", test_src);
	test_src=mat_row_nto1(test_src);	
	test_src.convertTo(test_src, CV_64FC1);

	Mat tmodel = model(Range(0, n), Range(0, model.cols));
	Mat test_tran = test_src * tmodel.t();

	vector<double>distance;
	for (int i = 0; i < verification.rows; i++)
	{
		double d = distance_of_two_matrix(test_tran, verification.row(i));
		distance.push_back(d);
	}

	if (testmode == 0)//1 vs 1
	{
		bool verify = false;
		for (int i = (no-1) * 9; (i<135&&i < (no-1) * 9 + 9)||(i==135); i++)
		{
			if (distance.at(i) < threshold)
				verify = true;
		}
		int fontface = 3;
		double scale = 0.5;
		int thickness = 2;
		Point org(show1.cols*1.1, show1.rows / 2);
		Scalar color=Scalar(0, 0, 0);
		Mat show2(show1.rows, show1.cols * 2, CV_8UC1, Scalar::all(255));
		show1.copyTo(show2(Range(0, show2.rows), Range(0, show1.cols)));
		string text;
		if (verify)
			text = "True";
		else
			text = "False";
		Size s = getTextSize(text, fontface, scale, thickness,0);
		putText(show2, text, org, fontface, scale, color, thickness);
		imshow("1_vs_1", show2);

		imwrite("resource/test_data/"+int_to_string(no)+".bmp", show2);
		return 0;
	}
	else if (testmode == 1)   //1 vs n
	{
		double min = distance.at(0);
		int index = 0;
		for (int i = 0; i < distance.size(); i++)
		{
			if (distance.at(i) < min)
			{
				index = i;
				min = distance.at(i);
			}
		}
		//cout << "index: " << index / 9 + 1 << "/s" << index % 9 + 1 << endl;
		//cout << "min distance:" << min << endl;
		Mat show;
		raw_mat.row(index).convertTo(show, CV_8UC1);
		show = mat_row_1ton(show, row);
		imshow("similar", show);
		return index / 9 + 1;
	}
}
void Test::set_raw_mat(Mat src)
{
	src.copyTo(this->raw_mat);
}
void Test::do_test1()
{
	testmode = 1;
	string path = "resource/face/yale/";
	ofstream out("resource/test_data/1_vs_n.txt");
	out << "PCs " << "right rate" << endl << endl;
	for (int n = 1; n <= 100; n = n + 1) {
		cal_verification(n);
		int right = 0, wrong = 0;
		for (int i = 1; i <= 16; i++)
		{
			string filepfix = path + int_to_string(i) + "/";
			if (i < 16)
			{
				for (int j = 10; j <= 11; j++)
				{
					string filename = filepfix + "s" + int_to_string(j) + ".bmp";
					int res=test_one(filename, i, threshold, n);
					if (i == res)
						right++;
					else {
						wrong++;
						//cout <<"wrong index:"<< i <<"  to index:"<<res<<"j="<<j<< endl;
					}
				}
			}
			else
			{
				for (int j = 2; j <= 2; j++)
				{
					string filename = filepfix + "s" + int_to_string(j) + ".bmp";
					int res = test_one(filename, i, threshold, n);
					if (i == res)
						right++;
					else
						wrong++;
				}
			}
		}
		out << n << "   " << 1.0*right / 31 << endl;
		//cout << "n:" << n << "  " << "right rate:" << 1.0*right/31 << "  wrong:" << wrong << endl;
	}
	out.close();
}
void Test::do_test2()
{
	testmode = 0;
	threshold = 2000;
	int num_PCs = 50;
	string path = "resource/face/yale/";
	cal_verification(num_PCs);

	int id;
	string filename;

	id = 1;
	filename = "1/s10.bmp";
	test_one(path + filename, id, threshold, num_PCs);
	
	id = 2;
	filename= "1/s10.bmp";
	test_one(path + filename, id, threshold, num_PCs);

	id = 3;
	filename = "3/s10.bmp";
	test_one(path + filename, id, threshold, num_PCs);

	id = 16;
	filename = "16/s2.bmp";
	test_one(path + filename, id, threshold, num_PCs);

}