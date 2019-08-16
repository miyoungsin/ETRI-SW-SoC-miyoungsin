#include <opencv2/opencv.hpp>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <fstream>

using namespace cv;
using namespace std;

double ***MaxPooling(double ***conv, int p_rowsize, int p_colsize, int f_row,int f_col, int s, int channel)
{
    double ***result;
    
    result = (double***)malloc(sizeof(double**)*channel);
    for(int cha = 0 ; cha < channel ; cha++){
        *(result + cha) = (double**)malloc(sizeof(double*)*p_rowsize);
        for(int row = 0; row<p_rowsize; row++){
            *(*(result +cha)+row) =(double*)malloc(sizeof(double)*p_colsize);
            }
    }

    for(int g=0; g<channel; g++)
    {
        for(int h=0; h<p_rowsize; h++)
        {
            for(int i=0; i<p_colsize; i++)
            {
                result[g][h][i] = INT_MIN;
                for(int j=0; j<f_row; j++)
                {            
                    for(int k=0; k<f_col; k++)
                    {
                        if(conv[g][h+j*s][i+k*s] > result[g][h][i]) 
						{ 
                            result[g][h][i] = conv[g][h+j*s][i+k*s]; 
                        }
                    }             
                }
            }
        }
    }
    return result;
}