#include<fstream>
#include"mytrain.h"
#include"../util/lib.h"

Mat Train::get_raw_mat()
{
	return raw_mat;
}
void Train::load_face(string dirpath)
{
	size = 0.5;
	Mat tmp = imread(dirpath + "1/"+"s1.bmp");

	this->col = tmp.cols*size;
	this->row = tmp.rows*size;
	raw_mat = Mat(num_pic, col*row, CV_64FC1);
	for (int i = 1; i <= number; i++)
	{
		string name = int_to_string(i);
		string path = dirpath + name + "/";
		if (i < number) {
			for (int j = 1; j < 10; j++)
			{
				string filename = path +'s'+ int_to_string(j) + ".BMP";
				Mat pic = imread(filename, 0);
				//imshow(name, pic);
				//Histogram_equalization(pic, pic);
				//imwrite(filename, pic);
				Mat pic1;
				resize(pic, pic1, Size(0, 0), size, size);
				Mat tmp = mat_row_nto1(pic1);
				tmp.convertTo(tmp, CV_64FC1);
				int the_row = 9 * (i - 1) + j - 1;
				tmp.copyTo(raw_mat.row(the_row));
			}
			
		}
		else {
			string filename = path + "s1.bmp";
			Mat pic = imread(filename, 0);
			//imshow(name, pic);
			Mat pic1;
			resize(pic, pic1, Size(0, 0), size, size);
			Mat tmp = mat_row_nto1(pic1);
			tmp.convertTo(tmp, CV_64FC1);
			int the_row = 9 * (i - 1);
			tmp.copyTo(raw_mat.row(the_row));
		}
	}
	
	//cout << raw_mat.cols << "  " << raw_mat.rows << endl;
	//cout << raw_mat;
}

void Train::get_meanface() {
	raw_mat.row(0).copyTo(mean_mat);
	
	for (int i = 1; i < num_pic; i++) {
		mean_mat += raw_mat.row(i);
		//cout << raw_mat.row(i);
	}
	//cout << mean_mat;
	mean_mat /= num_pic;
	//cout << mean_mat;
	Mat tmp = repeat(mean_mat, num_pic, 1);
	Mat data = raw_mat - tmp;
	cov_mat = data.t()*data / (data.rows);
	data.copyTo(t);
	Mat show = mat_row_1ton(mean_mat, row);
	show.convertTo(show, CV_8UC1);
	cout << show.cols << "  " << show.rows<<endl;
	cout << show;
	imshow("mean_face", show);
	imwrite("resource/train_data/mean_face.bmp", show);
}
void Train::get_eigen() {
	int mode = 0;
	if (mode == 0) {
		cv::eigen(cov_mat, value, vector);
		/*cout << value << endl << endl;
		cout << vector.rowRange(0,10) << endl;*/
	}
	else {
		Mat tmp = t*t.t() / t.rows;
		Mat tvalue, tvector;
		eigen(tmp, tvalue, tvector);
		vector = tvector*t;
	
	//cout << tvalue << endl;
	//cout << tvector << endl;
	}
}
void Train::get_eigenface(int n)
{
	Mat eigenvector = vector(Range(0, n), Range(0, vector.cols));
	string path = "resource/train_data/eigen_faces/";
	Mat total(2 * row, col * 5, CV_8UC1);
	for (int i = 0; i < n; i++)
	{
		Mat eigenface = map_to_0_255(eigenvector.row(i));
		Mat show = mat_row_1ton(eigenface, row);
		int x = i % 5;
		int y = i / 5;
		show.copyTo(total(Range(y*row, y*row + row), Range(x*col, x*col + col)));
		string name = int_to_string(i);
		name = "eigenface" + name;
		name += ".jpg";
		//imshow(name, show);
		imwrite(path + name, show);
	}
	//imshow("total", total);
	imwrite(path+"total.jpg",total );
}
void Train::save_model(int n)
{
	string vectorpath = "resource/train_data/eigen_vectors/";
	string modelpath = "resource/train_data/model/";
	string txtname = "vectors.txt";
	string modelname = "model.txt";
	ofstream vout, mout;
	vout.open(vectorpath + txtname);
	mout.open(modelpath + modelname);

	for (int i = 0; i < vector.rows; i++)
	{
		for (int j = 0; j < vector.cols; j++)
		{
			vout << vector.at<double>(i, j) << ' ';
			if(i < n)
				mout<< vector.at<double>(i, j) << ' ';
		}
		vout << endl;
		if (i < n)
			mout << endl;
	}
	vout.close();
	mout.close();
}
void Train::load_model(int n,Mat &out)
{
	ifstream in;
	string modelpath = "resource/train_data/model/";
	string modelname = "model.txt";
	in.open(modelpath + modelname);
	if (in.fail())
	{
		cout << "error ! failed to load the model";
		in.close();
		return;
	}
	Mat load(n, row*col, CV_64FC1);
	//Mat load(n, 4, CV_64FC1);
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < load.cols; j++)
		{
			if (in.peek() == '\n')
				break;
			else {
				in >>load.at<double>(i, j);
			}
		}
	}
	load.copyTo(out);
}
void Train::mytest()
{
	int no = 1;
	int num =50;
	int testmode = 1;
	string fix = "resource/face/yale/16/";
	string name = int_to_string(no);
	string path = fix  +'s'+name + ".bmp";
	if (testmode) {
		Mat src = imread(path, 0);
		Mat tmp;
		resize(src, tmp, Size(0, 0), size, size);
		imshow("tmps1", tmp);
		Mat test = mat_row_nto1(tmp);
		test.convertTo(test, CV_64FC1);
		Mat a = vector(Range(0, num), Range(0, col*row));
		Mat at = a.t();
		Mat tmp1 = test*at;
		Mat show = tmp1*a;
		show = map_to_0_255(show);

		show.convertTo(show, CV_8UC1);
		show = mat_row_1ton(show, row);
		imshow(name, show);
	}
	else
	for (int i = 0; i < 10; i++)
	{
		string name = int_to_string(i);
		Mat test = mat_row_nto1(vector.row(i));
		test.convertTo(test, CV_64FC1);
		Mat a = vector(Range(0, num), Range(0, col*row));
		Mat at = a.t();
		Mat tmp1 = test*at;
		Mat show = tmp1*a;
		show = map_to_0_255(show);
		show.convertTo(show, CV_8UC1);
		show = mat_row_1ton(show, row);
		imshow(name, show);
	}
}
