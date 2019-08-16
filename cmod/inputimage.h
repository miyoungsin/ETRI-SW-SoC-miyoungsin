#include <opencv2/opencv.hpp>
#include <iostream>
#include <time.h>
#include <cstdio>
#include <cstdlib>
#include <fstream>

using namespace cv;
using namespace std;

double ***NEW(int p,int s, Mat image, int channel) //padding, Mat 이미지, 채널, double***&a
{
    double *** a;
    a = (double***)malloc(sizeof(double**)*channel);
    for(int cha = 0 ; cha < channel ; cha++){
        *(a+cha) = (double**)malloc(sizeof(double*)*image.rows);
        for(int row = 0 ; row < image.rows ; row++){
            *(*(a+cha)+row) = (double*)malloc(sizeof(double)*image.rows);
            for(int col = 0 ; col < image.cols ; col++){
                a[cha][row][col] = image.at<uchar>(row,col);
            }
        }
    }
    return a;
}