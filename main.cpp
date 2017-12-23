#include<opencv2\opencv.hpp>
#include<iostream>
#include<stdlib.h>
#include<fstream>
#include"src\mytrain\mytrain.h"
#include"src\mytest\mytest.h"
#include"src\myreconstruct\myreconstruct.h"
#include"src\get_faces\getfaces.h"
#include"src/util/lib.h"
using namespace cv;
using  namespace std;


int main()
{
	int number_of_PCs = 100;
	Train mytrain(16);
	mytrain.load_face("resource/face/yale/");
	mytrain.get_meanface();
	mytrain.get_eigen();
	mytrain.save_model(number_of_PCs);
	mytrain.get_eigenface(10);


	Test mytest;
	mytest.set_raw_mat(mytrain.get_raw_mat());
	mytrain.load_model(number_of_PCs, mytest.model);
	//mytest.do_test1();
	mytest.do_test2();
	
	Reconstruct myconstruct;
	mytrain.load_model(number_of_PCs, myconstruct.model);
	myconstruct.do_reconstruct("resource/face/yale/16/s1.bmp");


	waitKey(0);
	system("pause");


}

